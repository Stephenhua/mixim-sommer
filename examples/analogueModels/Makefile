#
# OMNeT++/OMNEST Makefile for analogueModels
#
# This file was generated with the command:
#  opp_makemake -f -o analogueModels -O out -I../../modules/analogueModel -I../../modules/phy -I../../base/modules -I../../modules/mac -I../../modules/obstacle -I../../base/connectionManager -I../../modules/messages -I../../modules -I../../modules/utility -I../../base/utils -I../../base -I../../base/messages -I../../base/phyLayer -L../../out/$(CONFIGNAME) -L../../out/$(CONFIGNAME)/base -L../../out/$(CONFIGNAME)/tests/power/utils -L../../out/$(CONFIGNAME)/tests/testUtils -L../../out/$(CONFIGNAME)/modules -lmiximbase -lmiximmodules
#

# Name of target to be created (-o option)
TARGET = analogueModels$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../../modules/analogueModel \
    -I../../modules/phy \
    -I../../base/modules \
    -I../../modules/mac \
    -I../../modules/obstacle \
    -I../../base/connectionManager \
    -I../../modules/messages \
    -I../../modules \
    -I../../modules/utility \
    -I../../base/utils \
    -I../../base \
    -I../../base/messages \
    -I../../base/phyLayer \
    -I.

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../../out/$(CONFIGNAME) -L../../out/$(CONFIGNAME)/base -L../../out/$(CONFIGNAME)/tests/power/utils -L../../out/$(CONFIGNAME)/tests/testUtils -L../../out/$(CONFIGNAME)/modules  -lmiximbase -lmiximmodules
LIBS += -Wl,-rpath,`abspath ../../out/$(CONFIGNAME)` -Wl,-rpath,`abspath ../../out/$(CONFIGNAME)/base` -Wl,-rpath,`abspath ../../out/$(CONFIGNAME)/tests/power/utils` -Wl,-rpath,`abspath ../../out/$(CONFIGNAME)/tests/testUtils` -Wl,-rpath,`abspath ../../out/$(CONFIGNAME)/modules`

# Output directory
PROJECT_OUTPUT_DIR = ../../out
PROJECTRELATIVE_PATH = examples/analogueModels
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = $O/RandomFreqTimeModel.o $O/RandomFrequencyOnlyModel.o $O/SamplePhyLayer.o $O/SimpleMacLayer.o

# Message files
MSGFILES =

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $(TARGET)

$(TARGET) : $O/$(TARGET)
	$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY:

.SUFFIXES: .cc

$O/%.o: %.cc
	@$(MKPATH) $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f analogueModels analogueModels.exe libanalogueModels.so libanalogueModels.a libanalogueModels.dll libanalogueModels.dylib
	-rm -f ./*_m.cc ./*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/RandomFrequencyOnlyModel.o: RandomFrequencyOnlyModel.cc \
	../../base/utils/FWMath.h \
	../../base/utils/HostState.h \
	../../base/modules/BaseUtility.h \
	../../base/utils/Coord.h \
	../../base/utils/ImNotifiable.h \
	../../base/modules/Blackboard.h \
	RandomFrequencyOnlyModel.h \
	../../base/utils/Move.h \
	../../base/phyLayer/MappingBase.h \
	../../base/phyLayer/AnalogueModel.h \
	../../base/phyLayer/MappingUtils.h \
	../../base/phyLayer/Interpolation.h \
	../../base/phyLayer/Mapping.h \
	../../base/phyLayer/Signal_.h
$O/SimpleMacLayer.o: SimpleMacLayer.cc \
	../../base/phyLayer/MacToPhyControlInfo.h \
	../../base/utils/FWMath.h \
	../../base/utils/HostState.h \
	../../base/phyLayer/PhyUtils.h \
	../../base/phyLayer/ChannelState.h \
	../../base/messages/MacPkt_m.h \
	../../base/phyLayer/MacToPhyInterface.h \
	../../base/modules/BaseUtility.h \
	../../base/utils/Coord.h \
	../../base/utils/ImNotifiable.h \
	../../base/modules/Blackboard.h \
	../../base/utils/Move.h \
	../../base/phyLayer/MappingBase.h \
	SimpleMacLayer.h \
	../../base/phyLayer/AnalogueModel.h \
	../../base/modules/BaseModule.h \
	../../base/phyLayer/Interpolation.h \
	../../base/phyLayer/MappingUtils.h \
	../../base/utils/FindModule.h \
	../../base/phyLayer/Mapping.h \
	../../base/phyLayer/Signal_.h
$O/RandomFreqTimeModel.o: RandomFreqTimeModel.cc \
	../../base/utils/FWMath.h \
	../../base/utils/HostState.h \
	../../base/modules/BaseUtility.h \
	../../base/utils/Coord.h \
	../../base/utils/ImNotifiable.h \
	../../base/modules/Blackboard.h \
	../../base/utils/Move.h \
	../../base/phyLayer/MappingBase.h \
	../../base/phyLayer/AnalogueModel.h \
	../../base/phyLayer/Interpolation.h \
	../../base/phyLayer/MappingUtils.h \
	../../base/phyLayer/Mapping.h \
	RandomFreqTimeModel.h \
	../../base/phyLayer/Signal_.h
$O/SamplePhyLayer.o: SamplePhyLayer.cc \
	SamplePhyLayer.h \
	../../base/utils/FWMath.h \
	../../base/messages/AirFrame_m.h \
	../../base/utils/HostState.h \
	../../base/messages/MacPkt_m.h \
	../../base/phyLayer/MacToPhyInterface.h \
	ThresholdDecider.h \
	../../base/utils/Coord.h \
	../../base/phyLayer/ChannelInfo.h \
	../../base/modules/Blackboard.h \
	RandomFrequencyOnlyModel.h \
	../../base/phyLayer/MappingBase.h \
	../../base/phyLayer/AnalogueModel.h \
	../../base/phyLayer/MappingUtils.h \
	../../base/utils/FindModule.h \
	../../base/phyLayer/Mapping.h \
	../../base/phyLayer/Signal_.h \
	../../base/phyLayer/DeciderToPhyInterface.h \
	../../base/phyLayer/Decider.h \
	../../base/modules/BaseBattery.h \
	../../base/connectionManager/NicEntry.h \
	../../base/modules/BaseWorldUtility.h \
	../../base/phyLayer/PhyUtils.h \
	../../base/phyLayer/ChannelState.h \
	../../base/connectionManager/BaseConnectionManager.h \
	../../base/modules/BaseUtility.h \
	../../base/modules/BatteryAccess.h \
	../../base/utils/ImNotifiable.h \
	../../base/messages/ChannelSenseRequest_m.h \
	../../base/utils/Move.h \
	../../modules/phy/PhyLayer.h \
	../../base/modules/BaseModule.h \
	../../base/phyLayer/Interpolation.h \
	../../base/phyLayer/BasePhyLayer.h \
	RandomFreqTimeModel.h \
	../../base/connectionManager/ChannelAccess.h

