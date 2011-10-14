#ifndef TESTDECIDER_H_
#define TESTDECIDER_H_

#include <Decider.h>
#include <TestModule.h>
#include <BasePhyLayer.h>
#include "TestGlobals.h"

class TestDecider:public Decider, public TestModule {
protected:
	int myIndex;
	int run;
	const int RECEIVING_STATE;

	bool state;
	double rssi;

	simtime_t senseStart;

protected:
	void assertMessage(std::string msg, int state, AirFrame* frame, simtime_t arrival, std::string dest = "") {
		TestModule::assertMessage(new AssertAirFrame(msg, state, arrival, frame), dest);
	}

public:
	TestDecider(DeciderToPhyInterface* phy, int index, int run, int RECEIVING_STATE):
		Decider(phy), myIndex(index), run(run), RECEIVING_STATE(RECEIVING_STATE), state(false), rssi(0.0) {

		init("decider" + toString(myIndex));
	}

	ChannelState getChannelState() {
		state = !state;
		rssi += 1.0;
		return ChannelState(state, rssi);
	}

	simtime_t handleChannelSenseRequest(ChannelSenseRequest* request) {
		announceMessage(request);

		simtime_t time = phy->getSimTime();
		if(request->getSenseTimeout() > 0.0) {
			senseStart = time;
			simtime_t next = time + request->getSenseTimeout();

			request->setSenseTimeout(0.0);
			return next;
		} else {

			DeciderToPhyInterface::AirFrameVector v;
			phy->getChannelInfo(senseStart, time, v);
			request->setResult(ChannelState(v.empty()));
			phy->sendControlMsg(request);
			return -1.0;
		}
	}

	void testRun7(int stage, cMessage* msg)
	{

		AirFrame* frame = dynamic_cast<AirFrame*>(msg);
		assertTrue("Passed message is an AirFrame.", frame != NULL, true);

		const Signal& s = frame->getSignal();

		simtime_t start = s.getSignalStart();
		simtime_t end = s.getSignalStart() + s.getSignalLength();

		AirFrameVector interf;

		if(stage == 4) {
//planTest("1.9", "Interference for Packet 1 at decider A2 contains packet 2.");
			phy->getChannelInfo(start, end, interf);

			testForEqual("1.9", (unsigned int)2, interf.size());

//planTest("1.8", "Interference for Packet 2 at decider B2 contains packet 1.");
			waitForMessage( "End of Packet 2 at decider of B2",
							BasePhyLayer::AIR_FRAME,
							simTime() + 4.0, "decider3");
		} else if(stage == 5) {
			phy->getChannelInfo(start, end, interf);

			testForEqual("1.8", (unsigned int)2, interf.size());
		}
	}

	simtime_t processSignal(AirFrame* frame) {
		announceMessage(frame);

		const Signal& s = frame->getSignal();

		simtime_t time = phy->getSimTime();
		simtime_t end;

		if(run == 7)
		{
			end = s.getSignalStart() + s.getSignalLength();
		} else {
			end = s.getSignalStart() + s.getSignalLength() * 0.1;
		}

		if(time == s.getSignalStart()) {
			assertMessage("Scheduled AirFrame to end at phy.", RECEIVING_STATE,
						  frame, end, "phy" + toString(myIndex));
			assertMessage("Scheduled AirFrame to end.", RECEIVING_STATE,
						  frame, end);
			return end;

		} else if(time == end) {
			phy->sendUp(frame, new DeciderResult(true));
			TestModule::assertMessage("MacPkt at mac layer.", TEST_MACPKT,
						  time, "mac" + toString(myIndex));
			return -1;
		}

		fail("Simtime(" + toString(time) + ") was neither signal start ("
			 + toString(s.getSignalStart()) + ") nor end(" + toString(end)
			 + ").");

		return -1;
	}

	~TestDecider() {
		finalize();
	}
};
#endif /*TESTDECIDER_H_*/
