/*
 * Decider802154Narrow.cc
 *
 *  Created on: 11.02.2009
 *      Author: karl wessel
 */

#include "Decider802154Narrow.h"
#include "DeciderResult802154Narrow.h"
#include "Consts802154.h"
#include <MacPkt_m.h>
#include <PhyToMacControlInfo.h>
#include <cmath>

bool Decider802154Narrow::syncOnSFD(AirFrame* frame) {
	double BER;
	double sfdErrorProbability;

	BER = evalBER(frame);
	sfdErrorProbability = 1.0 - pow((1.0 - BER), sfdLength);

	return sfdErrorProbability < uniform(0, 1, 0);
}

double Decider802154Narrow::evalBER(AirFrame* frame) {
	Signal& signal = frame->getSignal();

	simtime_t time = MappingUtils::post(phy->getSimTime());
	double rcvPower = signal.getReceivingPower()->getValue(Argument(time));

	ConstMapping* noise = calculateRSSIMapping(time, time, frame);

	Argument argStart(time);
	argStart.setArgValue(Dimension::frequency, 2.4E+9);
	double noiseLevel = noise->getValue(argStart);

	delete noise;

	return getBERFromSNR(rcvPower/noiseLevel); //std::max(0.5 * exp(-rcvPower / (2 * noiseLevel)), DEFAULT_BER_LOWER_BOUND);
}

simtime_t Decider802154Narrow::processNewSignal(AirFrame* frame) {
	//if we are already receiving another signal this is noise
	if(currentSignal.first != 0) {
		return notAgain;
	}

	if (!syncOnSFD(frame)) {
		return notAgain;
	}

	// store this frame as signal to receive and set state
	currentSignal.first = frame;
	currentSignal.second = EXPECT_END;

	//channel is busy now
	setChannelIdleStatus(false);

	//TODO: publish rssi and channel state

	Signal& s = frame->getSignal();
	return s.getSignalStart() + s.getSignalLength();
}

simtime_t Decider802154Narrow::processSignalEnd(AirFrame* frame)
{
	ConstMapping* snrMapping = calculateSnrMapping(frame);

	Signal& s = frame->getSignal();
	simtime_t start = s.getSignalStart();
	simtime_t end = start + s.getSignalLength();

	AirFrameVector channel;
	phy->getChannelInfo(start, end, channel);
	bool hasInterference = channel.size() > 1;

	if(hasInterference) {
		nbFramesWithInterference++;
	} else {
		nbFramesWithoutInterference++;
	}

	double bitrate = s.getBitrate()->getValue(Argument(start));

	double avgBER = 0;
	double bestBER = 0.5;
	double snirAvg = 0;
	bool noErrors = true;
	double ber;
	double errorProbability;

	simtime_t receivingStart = MappingUtils::post(start);
	Argument argStart(receivingStart);
	argStart.setArgValue(Dimension::frequency, 2.4E+9);
	ConstMappingIterator* iter = snrMapping->createConstIterator(argStart);
	double snirMin = iter->getValue();
	// Evaluate bit errors for each snr value
	// and stops as soon as we have an error.
	// TODO: add error correction code.

	simtime_t curTime = iter->getPosition().getTime();
	simtime_t snrDuration;
	while(curTime < end) {
		//get SNR for this interval
		double snr = iter->getValue();

		//determine end of this interval
		simtime_t nextTime = end;	//either the end of the signal...
		if(iter->hasNext()) {		//or the position of the next entry
			const Argument& argNext = iter->getNextPosition();
			if(	!argNext.hasArgVal(Dimension::frequency)
				|| argNext.getArgValue(Dimension::frequency) == 2.4e+9)
			{
				nextTime = std::min(argNext.getTime(), nextTime);
				iter->next();	//the iterator will already point to the next entry
			} else {
				nextTime = end;
			}
		}

		if (noErrors) {
			snrDuration = nextTime - curTime;

			int nbBits = int (snrDuration.dbl() * bitrate);

			// non-coherent detection of m-ary orthogonal signals in an AWGN
			// Channel
			// Digital Communications, John G. Proakis, section 4.3.2
			// p. 212, (4.3.32)
			//  Pm = sum(n=1,n=M-1){(-1)^(n+1)choose(M-1,n) 1/(n+1) exp(-nkgamma/(n+1))}
			// Pb = 2^(k-1)/(2^k - 1) Pm


			ber = std::max(getBERFromSNR(snr), BER_LOWER_BOUND);
			avgBER = ber*nbBits;
			snirAvg = snirAvg + snr*snrDuration.dbl();

			if(ber < bestBER) {
				bestBER = ber;
			}
			errorProbability = 1.0 - pow((1.0 - ber), nbBits);
			noErrors = errorProbability < uniform(0, 1);
		}
		if (snr < snirMin)
			snirMin = snr;

		curTime = nextTime;
	}
	delete iter;
	delete snrMapping;

	avgBER = avgBER / frame->getBitLength();
	snirAvg = snirAvg / (end - start);
	double rssi = 10*log10(snirAvg);
	if (noErrors)
	{
		phy->sendUp(frame,
					new DeciderResult802154Narrow(true, bitrate, snirMin, avgBER, rssi));
		snirReceived.record(10*log10(snirMin));  // in dB
	} else {
		MacPkt* mac = static_cast<MacPkt*> (frame->decapsulate());
		mac->setName("BIT_ERRORS");
		mac->setKind(PACKET_DROPPED);

		DeciderResult802154Narrow* result =
			new DeciderResult802154Narrow(false, bitrate, snirMin, avgBER, rssi);
		PhyToMacControlInfo* cInfo = new PhyToMacControlInfo(result);
		mac->setControlInfo(cInfo);
		phy->sendControlMsg(mac);
		snirDropped.record(10*log10(snirMin));  // in dB
		if(hasInterference) {
			nbFramesWithInterferenceDropped++;
		} else {
			nbFramesWithoutInterferenceDropped++;
		}
	}

	//decoding is done
	currentSignal.first = 0;

	//channel is back idle
	setChannelIdleStatus(true);

	//TODO: publish rssi and channel state
	return notAgain;
}

double Decider802154Narrow::n_choose_k(int n, int k) {
  double res = 1;
  for(int i = 1; i <= k; i++) {
    res = res * (n-k+i) / i;
  }
  return res;
}

double Decider802154Narrow::getBERFromSNR(double snr) {
	double ber = BER_LOWER_BOUND;
	double sum_k = 0;
	if(modulation == "msk") {
		// valid for IEEE 802.15.4 868 MHz BPSK modulation
		ber = 0.5 *  erfc(sqrt(snr));
	} else if (modulation == "oqpsk16") {
		// valid for IEEE 802.15.4 2.45 GHz OQPSK modulation
		for (int k = 2; k <= 16; k++) {
			sum_k = sum_k + pow(-1, k) * n_choose_k(16, k) * exp(20 * snr * (1.0 / k - 1.0));
		}
		ber = (8.0 / 15) * (1.0 / 16) * sum_k;
	} else if(modulation == "gfsk") {
		// valid for Bluetooth 4.0 PHY mandatory base rate 1 Mbps
		// Please note that this is not the correct expression for
		// the enhanced data rates (EDR), which uses another modulation.
		ber = 0.5 * erfc(sqrt(0.5 * snr));
	} else {
		opp_error("The selected modulation is not supported.");
	}
	berlog.record(ber);
	snrlog.record(10*log10(snr));
	return std::max(ber, BER_LOWER_BOUND);
}

void Decider802154Narrow::finish() {

	// record scalars through the interface to the PHY-Layer
	phy->recordScalar("nbFramesWithInterference", nbFramesWithInterference);
	phy->recordScalar("nbFramesWithoutInterference", nbFramesWithoutInterference);
	phy->recordScalar("nbFramesWithInterferenceDropped", nbFramesWithInterferenceDropped);
	phy->recordScalar("nbFramesWithoutInterferenceDropped", nbFramesWithoutInterferenceDropped);
}
