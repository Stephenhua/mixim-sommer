#
# OMNeT++/OMNEST Makefile for mixim-sommer
#
# This file was generated with the command:
#  opp_makemake -f --nolink -O out -d deviceTestAccts -d deviceTestMulti -d deviceTestAll -d utils -d deviceTest -d Nic80211Test -L../../out/$(CONFIGNAME) -L../../out/$(CONFIGNAME)/base -L../../out/$(CONFIGNAME)/tests/power/utils -L../../out/$(CONFIGNAME)/tests/testUtils -L../../out/$(CONFIGNAME)/modules
#

# C++ include paths (with -I)
INCLUDE_PATH = -I.

# Output directory
PROJECT_OUTPUT_DIR = ../../out
PROJECTRELATIVE_PATH = tests/power
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS =

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

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# inserted from file 'makefrag':
# preserve default target
all: $(TARGET)

deviceTest_dir deviceTestAccts_dir deviceTestAll_dir deviceTestMulti_dir Nic80211Test_dir: utils_dir

.PHONY: utils

# <<<
#------------------------------------------------------------------------------

# Main target

all: $(OBJS) submakedirs Makefile
	@# Do nothing

submakedirs:  deviceTestAccts_dir deviceTestMulti_dir deviceTestAll_dir utils_dir deviceTest_dir Nic80211Test_dir

.PHONY: deviceTestAccts deviceTestMulti deviceTestAll utils deviceTest Nic80211Test
deviceTestAccts: deviceTestAccts_dir
deviceTestMulti: deviceTestMulti_dir
deviceTestAll: deviceTestAll_dir
utils: utils_dir
deviceTest: deviceTest_dir
Nic80211Test: Nic80211Test_dir

deviceTestAccts_dir:
	cd deviceTestAccts && $(MAKE)

deviceTestMulti_dir:
	cd deviceTestMulti && $(MAKE)

deviceTestAll_dir:
	cd deviceTestAll && $(MAKE)

utils_dir:
	cd utils && $(MAKE)

deviceTest_dir:
	cd deviceTest && $(MAKE)

Nic80211Test_dir:
	cd Nic80211Test && $(MAKE)

.SUFFIXES: .cc

$O/%.o: %.cc
	@$(MKPATH) $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)
	cd deviceTestAccts && $(MAKE) msgheaders
	cd deviceTestMulti && $(MAKE) msgheaders
	cd deviceTestAll && $(MAKE) msgheaders
	cd utils && $(MAKE) msgheaders
	cd deviceTest && $(MAKE) msgheaders
	cd Nic80211Test && $(MAKE) msgheaders

clean:
	-rm -rf $O
	-rm -f mixim-sommer mixim-sommer.exe libmixim-sommer.so libmixim-sommer.a libmixim-sommer.dll libmixim-sommer.dylib
	-rm -f ./*_m.cc ./*_m.h

	-cd deviceTestAccts && $(MAKE) clean
	-cd deviceTestMulti && $(MAKE) clean
	-cd deviceTestAll && $(MAKE) clean
	-cd utils && $(MAKE) clean
	-cd deviceTest && $(MAKE) clean
	-cd Nic80211Test && $(MAKE) clean

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc
	-cd deviceTestAccts && if [ -f Makefile ]; then $(MAKE) depend; fi
	-cd deviceTestMulti && if [ -f Makefile ]; then $(MAKE) depend; fi
	-cd deviceTestAll && if [ -f Makefile ]; then $(MAKE) depend; fi
	-cd utils && if [ -f Makefile ]; then $(MAKE) depend; fi
	-cd deviceTest && if [ -f Makefile ]; then $(MAKE) depend; fi
	-cd Nic80211Test && if [ -f Makefile ]; then $(MAKE) depend; fi

# DO NOT DELETE THIS LINE -- make depend depends on it.

