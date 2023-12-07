NATIVE = $(shell uname -m)
BOARD ?= $(NATIVE)
V2XATK ?= 0
V2XLLC ?= 1
V2XQTI ?= 0

SUDO ?= sudo

APP = exampleETSI

# Comment/uncomment the following line to disable/enable debugging
DEBUG := y
ifeq ($(DEBUG),y)
  # "-O" is needed to expand inlines
  EXTRA_CFLAGS += -O -ggdb -DDEBUG -DDEBUG_PRINT_TIMES
else
  EXTRA_CFLAGS += -O2
endif

BSP_DIR  := $(realpath $(CURDIR)/../../../bsp)
STACKDIR := $(realpath $(CURDIR)/../..)
SRCDIR   := $(realpath $(CURDIR))
OUTDIR   := $(realpath $(CURDIR))/$(BOARD)

#############################################################################
# Import board configuration
#############################################################################

BOARD_MK=$(STACKDIR)/boards/$(BOARD).mk
ifneq ($(wildcard $(BOARD_MK)),)
  $(info $$BOARD_MK "$(BOARD_MK)" loading...)
  include $(BOARD_MK)
  $(eval $(call AddBoard, app))
endif

#############################################################################
# Defaults for security libraries
#############################################################################

ifneq ($(NO_VIICSEC),1)
  SEC_V2XLIBS ?= libviicsec.so libviicsec.so.1 libaerolinkPKI.so libaerolinkPKI.so.1 \
                 libssl.so libssl.so.1.1 libcrypto.so libcrypto.so.1.1
  SEC_LDLIBS  ?= -Wl,--no-as-needed -ldl -lviicsec -laerolinkPKI -lssl -lcrypto

  ifeq ($(NO_LIBC2X),0)
    SEC_V2XLIBS += libc2x.so libc2x.so.1 libc2x.so.1.0 libc2x-compat.so libc2x-compat.so.1 \
                   libNxDispatcher.so libNxDispatcher.so.1.9 libNxDispatcher.so.1.9.3
    SEC_LDLIBS  += -lc2x -lNxDispatcher
  endif
  ifeq ($(NO_LIBV2XCRYPTO),0)
    SEC_V2XLIBS += libv2xCrypto.so libv2xCrypto.so.2.7 libv2xCrypto.so.2.7.1 \
                   libv2xCryptoPal.so libv2xCryptoPal.so.2.7 libv2xCryptoPal.so.2.7.1 \
                   libNxDispatcher.so libNxDispatcher.so.1.9 libNxDispatcher.so.1.9.3
    SEC_LDLIBS  += -lv2xCrypto -lv2xCryptoPal -lNxDispatcher
  endif
else
  SEC_V2XLIBS :=
  SEC_LDLIBS  :=
endif

#############################################################################
# BOARD specific setup
# - Folder locations, CROSSCOMPILE, CCOPTS, INSTALLDIR etc.
#############################################################################
# Allow ccache to be disabled for static analysis
CCACHE ?= ccache

ifneq (,$(findstring $(BOARD),mk5))
  # MK5 etc.
  ARCH := arm
  CROSS_COMPILE ?= "$(CCACHE) arm-linux-gnueabihf-"
  INSTALLDIR ?= $(STACKDIR)/../bsp/image/rootfs

  SEC_V2XLIBS := libviicsec.so libviicsec.so.1 libaerolinkPKI.so libaerolinkPKI.so.1 \
                 libsxa1700Interface.so libnxdispatcherMars1_9Interface.so \
                 libssl.so libssl.so.1.1 libcrypto.so libcrypto.so.1.1 \
                 libc2x.so libc2x.so.1 libc2x.so.1.0 \
                 libNxDispatcher.so libNxDispatcher.so.1.9 libNxDispatcher.so.1.9.3
  SEC_LDLIBS  := -lviicsec -lsxa1700Interface -laerolinkPKI -lssl -lcrypto -lc2x -Wl,--no-as-needed -lNxDispatcher -ldl

else ifneq (,$(findstring $(BOARD),mq5))
  ARCH := arm
  QNX_BASE ?= /opt/qnx660
  CROSS_COMPILE := "$(CCACHE) arm-unknown-nto-qnx6.6.0eabi-"
  INSTALLDIR ?=

  CPPFLAGS += -DNO_SYSINFO
  CFLAGS += -fpic

  SEC_V2XLIBS :=
  SEC_LDLIBS  :=

  V2XATK     := 0
  V2XLLC     := 1
  POSIX      := 1
  NO_VIICSEC := 1

else ifneq (,$(findstring $(BOARD),mk6))

  ARCH := arm64
  CROSS_COMPILE ?= "$(CCACHE) aarch64-linux-gnu-"
  INSTALLDIR ?= $(STACKDIR)/../bsp/image/rootfs
  CCOPTS += -fPIC
  CPPFLAGS +=

  SEC_V2XLIBS := libviicsec.so libviicsec.so.1 libaerolinkPKI.so libaerolinkPKI.so.1 \
                 libsxf1800Interface.so \
                 libv2xCrypto.so libv2xCrypto.so.2.8 libv2xCrypto.so.2.8.1 \
                 libv2xCryptoPal.so libv2xCryptoPal.so.2.8 libv2xCryptoPal.so.2.8.1 \
                 libNxDispatcher.so libNxDispatcher.so.1.2 libNxDispatcher.so.1.2.0 \
                 libssl.so libssl.so.1.1 libcrypto.so libcrypto.so.1.1
  SEC_LDLIBS  := -Wl,--no-as-needed -ldl \
                 -lviicsec \
                 -lsxf1800Interface \
                 -laerolinkPKI \
                 -lv2xCrypto -lv2xCryptoPal \
                 -lNxDispatcher \
                 -lssl -lcrypto

  QTI_CFLAGS := -I $(BSP_DIR)/QTI/snaptel-sdk/include -I $(BSP_DIR)/QTI/snaptel-sdk/include/telux/cv2x/legacy
  QTI_LDLIBS := -L $(BSP_DIR)/QTI/lib64 \
                 -lv2x_radio -lcv2x-kinematics -lv2x_veh \
                 -ltelux_cv2x -ltelux_data -lcv2x_sysctrl -ltelux_qmi -ltelux_common \
                 -ltelux_loc -llocation_client_api -llocation_integration_api -lcdfwremoteapi -lgps_utils -llocation_api_msg_proto \
                 -lqcmap_client -ldsi_netctrl -lqmi_cci -ldsutils \
                 -lqmi_client_qmux -lqmiidl -lqmiservices -lqmi_common_so -lqmi_encdec -lqmi_csi -lqmi_sap -lqmi_client_helper -lqmi -lqmipowermanager \
                 -ldiag -lqcmapipc -lqdi -lnetmgr -lrmnetctl -lconfigdb -lxml -lgthread-2.0 -lglib-2.0 -lpcre -lprotobuf-nanopb -lprotobuf -lz

  V2XLLC := 1
  V2XQTI := 1

else ifneq (,$(findstring $(BOARD),mk6c))

  ARCH := arm64
  CROSS_COMPILE ?= "$(CCACHE) aarch64-linux-gnu-"
  INSTALLDIR ?= $(STACKDIR)/../bsp/image/rootfs
  CCOPTS += -fPIC
  CPPFLAGS +=

  SEC_V2XLIBS := libviicsec.so libviicsec.so.1 libaerolinkPKI.so libaerolinkPKI.so.1 \
                 libsxf1800Interface.so \
                 libv2xCrypto.so libv2xCrypto.so.2.8 libv2xCrypto.so.2.8.1 \
                 libv2xCryptoPal.so libv2xCryptoPal.so.2.8 libv2xCryptoPal.so.2.8.1 \
                 libNxDispatcher.so libNxDispatcher.so.1.2 libNxDispatcher.so.1.2.0 \
                 libssl.so libssl.so.1.1 libcrypto.so libcrypto.so.1.1
  SEC_LDLIBS  := -Wl,--no-as-needed -ldl \
                 -lviicsec \
                 -lsxf1800Interface \
                 -laerolinkPKI \
                 -lv2xCrypto -lv2xCryptoPal \
                 -lNxDispatcher \
                 -lssl -lcrypto

  QTI_CFLAGS := -I $(BSP_DIR)/QTI/snaptel-sdk/include -I $(BSP_DIR)/QTI/snaptel-sdk/include/telux/cv2x/legacy
  QTI_LDLIBS := -L $(BSP_DIR)/QTI/lib64 \
                 -lv2x_radio -lcv2x-kinematics -lv2x_veh \
                 -ltelux_cv2x -ltelux_data -ltelux_qmi -ltelux_common \
                 -ltelux_loc -llocation_client_api -lloc_socket -lqsocket -lgps_utils \
                 -ldsi_netctrl -lqmi_cci -ldsutils \
                 -lqmi_client_qmux -lqmiidl -lqmiservices -lqmi_common_so -lqmi_encdec -lqmi_csi -lqmi_sap -lqmi_client_helper -lqmi -lqmipowermanager \
                 -ldiag -lqdi -lnetmgr -lrmnetctl -lqrtr -lgthread-2.0 -lglib-2.0 -lpcre -lprotobuf-nanopb

  V2XLLC := 0
  V2XQTI := 1


else ifneq ($(BOARD),$(NATIVE))
  # Generic non-x86
  ifneq ($(SDKTARGETSYSROOT),)
    CCOPTS += -fPIC --sysroot=$(SDKTARGETSYSROOT)
    CFLAGS += -I$(SDKTARGETSYSROOT)/usr/include
    LDFLAGS += --sysroot=$(SDKTARGETSYSROOT)
  endif

else
  # Native (PC)
  ARCH ?= $(NATIVE)
  CROSS_COMPILE ?= "$(CCACHE) "
  INSTALLDIR ?=
  CFLAGS += -Wall -Wextra -Werror

  SEC_V2XLIBS := libviicsec.so libviicsec.so.1 libaerolinkPKI.so libaerolinkPKI.so.1 \
		 libcrypto.so libcrypto.so.1.1
  SEC_LDLIBS  := -lviicsec -laerolinkPKI
endif

GPS_LIB_NAME ?= gps_static
#############################################################################
# File locations
#############################################################################
# Source directories
SRCDIRS := $(SRCDIR)/src

# Add this list to VPATH, the place $(MAKE) will look for the source files
VPATH := $(SRCDIRS)

# Matching output tree
OUTDIRS := $(subst $(SRCDIR),$(OUTDIR),$(SRCDIRS))

# Include folders
INCDIRS := $(SRCDIRS) \
           $(OUTDIR)/include \
           $(OUTDIR)/include/asn1 \
           $(realpath $(STACKDIR)/../cohda/kernel/include) \
           $(realpath $(STACKDIR)/../ieee1609/kernel/include)

# Aerolink
ifneq (1,$(NO_VIICSEC))
AEROLINK_SRCDIR = $(STACKDIR)/v2x-lib/aerolink
AEROLINK_CONFIG = $(OUTDIR)/aerolink/default
AEROLINK_SCRIPT = $(OUTDIR)/aerolink/rc.aerolink
AEROLINK_TOOLS =  \
		 $(OUTDIR)/aerolink/certadm \
		 $(OUTDIR)/aerolink/crladm \
		 $(OUTDIR)/aerolink/acfGenerator \
		 $(OUTDIR)/aerolink/acfBuilder \
		 $(OUTDIR)/aerolink/acfInfo \
		 $(OUTDIR)/aerolink/extractSignerTlmFromEctl \
		 $(OUTDIR)/aerolink/createEtsiInitRequest \
		 $(OUTDIR)/aerolink/processEtsiInitResponse
ifneq (,$(findstring $(BOARD),mk5 mk6 mk6c x86_64))
AEROLINK_TOOLS +=  \
		 $(OUTDIR)/aerolink/canonicalDataReader
endif
endif

# ffasn1c location/options/etc.
FFASN1DIR    = $(STACKDIR)/../tools/ffasn1c
FFASN1C      = $(FFASN1DIR)/ffasn1c
FFASN1C_OPTS = -fdefine-int-values
FFASN1PY     = $(STACKDIR)/tools/ffasn1.py
FFASN1PREFIX = RAW_
FFASN1DEF    = $(SRCDIR)/src/RAW.asn1
FFASN1OUT    = $(SRCDIR)/src/raw-asn

# Versioning
SVNVERSION   := $(shell svnversion $(CURDIR))
SVNVERSION   := $(subst :,-,$(SVNVERSION))
SVNVERSION   := $(subst Unversioned directory,Exported,$(SVNVERSION))
ifeq (,$(SVNVERSION))
  SVNVERSION := "Exported"
endif

#############################################################################
# CPPFLAGS, CFLAGS, LDFLAGS, LDLIBS
#############################################################################
# If using yocto/poky toolchain, use CC in environment
ifeq (,$(TARGET_PREFIX))
  CC := $(shell echo $(CROSS_COMPILE)gcc)
endif
CFLAGS += -DBOARD_$(shell echo $(BOARD) | tr a-z A-Z)
CFLAGS += -DVERSION="$(SVNVERSION)"
CFLAGS += -fpic -Wall -Wextra -Werror
LDFLAGS += -L$(OUTDIR) \
           -L$(OUTDIR)/lib \
           -Wl,--disable-new-dtags -Wl,-rpath,./lib

# Generate the include folders' associated CFLAGS entry by adding '-I' before each include folder
CFLAGS += $(foreach DIR, $(INCDIRS), $(addprefix -I, $(DIR)))

ifneq ($(INSTALLDIR),)
CFLAGS += -I$(INSTALLDIR)/usr/include
LDFLAGS += -L$(INSTALLDIR)/usr/lib
endif
ifneq (,$(LIBCFG_INC_DIR))
CFLAGS += -I$(LIBCFG_INC_DIR)
endif
ifneq (,$(LIBCFG_LIB_DIR))
LDFLAGS += -L$(LIBCFG_LIB_DIR) -L$(LIBCFG_LIB_DIR)/lib/.libs
endif
ifneq (,$(GPSD_INC_DIR))
CFLAGS += -I$(GPSD_INC_DIR)
endif
ifneq (,$(GPSD_LIB_DIR))
LDFLAGS += -L$(GPSD_LIB_DIR)
endif
ifneq (,$(PCAP_LIB_DIR))
LDFLAGS += -L$(PCAP_LIB_DIR)
endif
ifneq (,$(OPENSSL_LIB_DIR))
LDFLAGS += -L$(OPENSSL_LIB_DIR)
endif
ifneq (,$(DISPATCHER_LIB_DIR))
LDFLAGS += -L$(DISPATCHER_LIB_DIR)
endif
ifneq (,$(LIBV2XCRYPTO_LIB_DIR))
  LDFLAGS += -L$(LIBV2XCRYPTO_LIB_DIR)
endif

# default Plugins
V2XLIBS += libCANUDP.so
V2XLIBS += libEEBL.so
V2XLIBS += libFCW.so
V2XLIBS += libRWW.so
# optional/licensed PLugins
#V2XLIBS += libDNPW.so
#V2XLIBS += libEVW.so
#V2XLIBS += libGLOSA.so
#V2XLIBS += libGMLAN.so
#V2XLIBS += libHLW.so
#V2XLIBS += libICW.so
#V2XLIBS += libIHW.so
#V2XLIBS += libIVS.so
#V2XLIBS += libLCW.so
#V2XLIBS += libLTA.so
#V2XLIBS += libSVA.so
#V2XLIBS += libSVW.so
#V2XLIBS += libTJA.so

# Cohda libraries (platform, network & facilities layer)
V2XLIBS += libhmi.so libtm.so
LDLIBS += -lhmi -ltm
V2XLIBS += libtc.so libta.so libJudy.a
LDLIBS += -ltc -lta -lJudy
V2XLIBS += libspatmap.so
LDLIBS += -lspatmap
V2XLIBS += libivi.so libldm.so
LDLIBS += -livi -lldm
V2XLIBS += libext.so
LDLIBS += -lext
V2XLIBS += libitsfac.so libitsasn.so libitsnet.so
LDLIBS += -litsfac -litsasn -litsnet
V2XLIBS += libpos.so libubx.so
LDLIBS += -lpos -lubx
ifneq (,$(findstring $(BOARD),ir800))
V2XLIBS += libplatsv.so libclv.so
LDLIBS += -lplatsv -lclv
else
V2XLIBS += libplat.so libclv.so
LDLIBS += -lplat -lclv
endif

V2XLIBS += libtimechange.so
V2XLIBS += libconfig.a
LDLIBS += -lconfig
V2XLIBS += lib$(GPS_LIB_NAME).a
LDLIBS += -l$(GPS_LIB_NAME)
V2XLIBS += libpcap.a
LDLIBS += -lpcap
V2XLIBS += $(SEC_V2XLIBS)
LDLIBS += $(SEC_LDLIBS)
ifeq ($(V2XLLC),1)
  CPPFLAGS += -DV2XLLC
  V2XLIBS += libLLC.so
  LDLIBS += -lLLC
endif

ifeq ($(V2XQTI),1)
  CPPFLAGS += -DV2XQTI
  V2XLIBS += libQTIVData.so

  CFLAGS += $(QTI_CFLAGS)
  LDLIBS += $(QTI_LDLIBS)
endif

ifeq ($(BOARD),mq5)
  LDLIBS += -lsocket -lmq -lc -lm
else
  LDLIBS += -lpthread -lrt -ldl -lstdc++ -lm
endif

# Append extra libs from $(BOARD).mk
V2XLIBS += $(BOARD_V2XLIBS)
LDLIBS  += $(BOARD_LDLIBS)

# v2x-libs are installed locally in $(OUTDIR)/lib
V2XLIBS := $(addprefix $(OUTDIR)/lib/, $(V2XLIBS))

#############################################################################
# SRCS, OBJS, DEPS, LIBS etc.
#############################################################################
# Create a list of *.c sources in SRCDIRS
SRCS = $(foreach DIR,$(SRCDIRS),$(wildcard $(DIR)/*.c))

# Define objects for all sources
OBJS = $(subst $(SRCDIR),$(OUTDIR),$(SRCS:.c=.o))

RLW_SRCS = $(wildcard $(SRCDIR)/src/RLW/*.c)
RLW_OBJS = $(subst $(SRCDIR),$(OUTDIR),$(RLW_SRCS:.c=.o))
RLW_LIB  = $(OUTDIR)/lib/libRLW.so

# Define dependency files for all objects
DEPS = $(OBJS:.o=.d) $(RLW_OBJS:.o=.d)

#############################################################################
# Rule generation function
#############################################################################
define GenerateRules

$(1)/%.o: %.c $(1)/%.d
	@mkdir -p $$(@D) # Create the required OUTDIR.. folder
	@# Generate dependency information as a side-effect of compilation, not instead of compilation.
	@# -MMD omits system headers from the generated dependencies: if you prefer to preserve system headers as prerequisites, use -MD.
	$$(CC) \
	 -MT $$@ -MMD -MP -MF $(1)/$$*.Td \
	 $$(CCOPTS) $$(CPPFLAGS) $$(CFLAGS) $$(EXTRA_CFLAGS) -c $$< -o $$@
	@# First rename the generated temporary dependency file to the real dependency file.
	@# We do this in a separate step so that failures during the compilation won't leave a corrupted dependency file.
	mv -f $(1)/$$*.Td $(1)/$$*.d
	@# Second touch the object file; it's been reported that some versions of GCC may leave the object file older than the dependency file, which causes unnecessary rebuilds.
	touch $$@

# Create a pattern rule with an empty recipe, so that make won't fail if the dependency file doesn't yet exist.
$(1)/%.d: ;
# Mark the dependency files precious to make, so they won't be automatically deleted as intermediate files.
.PRECIOUS: $(1)/%.d

$(1)/%.gpp: %.c src-gen $(OUTDIR)/include
	@mkdir -p $$(@D) # Create the required OUTDIR.. folder
	$$(CC) -dD -E $$(CCOPTS) $$(CPPFLAGS) $$(CFLAGS) $$(EXTRA_CFLAGS) -c $$< -o $$@

$(1)/%.lst: %.c src-gen $(OUTDIR)/include
	@mkdir -p $$(@D) # Create the required OUTDIR.. folder
	$$(CC) -S     $$(CCOPTS) $$(CPPFLAGS) $$(CFLAGS) $$(EXTRA_CFLAGS) -c $$< -o $$@

$(1)/%.lint: %.c src-gen $(OUTDIR)/include
	@mkdir -p $$(@D) # Create the required OUTDIR.. folder
	-splint -shiftimplementation -warnposix -badflag --likelybool $$(CPPFLAGS) $$(CFLAGS) $$< | tee $$@

endef

#############################################################################
# Rules
#############################################################################

all: $(BOARD)

# Generate rules
$(foreach DIR, $(OUTDIRS), $(eval $(call GenerateRules, $(DIR))))
$(eval $(call GenerateRules, $(OUTDIR)/src/RLW))

# Include dependencies
-include $(DEPS)

src-gen: asn-gen rlw-gen ## Create all generated code
.PHONY: src-gen

app: version src-gen $(OUTDIR) ## Build $(APP) binary (Append BOARD=? to specify a non-host target)
	$(MAKE) $(OUTDIR)/$(APP) aerolink tolling

cpp: $(DEPS:.d=.gpp) ## Preprocess all $(APP) sources (Append BOARD=? to specify a non-host target)

lst: $(DEPS:.d=.lst) ## Generate assembler listings for all $(APP) sources (Append BOARD=? to specify a non-host target)

lint: $(DEPS:.d=.lint) ## Generate assembler listings for all $(APP) sources (Append BOARD=? to specify a non-host target)

.PHONY: all app cpp list lint

# Aerolink rule/targets
aerolink: $(V2XLIBS) $(AEROLINK_SCRIPT) $(AEROLINK_TOOLS) $(AEROLINK_CONFIG)

$(AEROLINK_CONFIG) : $(AEROLINK_SRCDIR)/config
	@mkdir -p $@
	@rsync -q -av --exclude="*.svn" $</* $@

$(AEROLINK_SCRIPT) : $(OUTDIR)/aerolink/% : $(AEROLINK_SRCDIR)/%
	@mkdir -p $(dir $@)
	@cp $< $@

$(AEROLINK_TOOLS) : $(OUTDIR)/aerolink/% : $(AEROLINK_SRCDIR)/$(BOARD)/%
	@mkdir -p $(dir $@)
	@cp $< $@

.PHONY: aerolink

#Tolling
tolling: TollDB.bin

TollDB.bin: ./PZDB_REL_20210426112800_20210426225123.xml.gz
	@echo "Making tolling database file $@"
	@touch $@
	gunzip -kf $<
	-$(STACKDIR)/tools/eu-toll-pack.py -d $(<:.gz=) -o $@ -q

.PHONY: tolling

# ffasn1c rules
$(FFASN1DEF):
	@ls $(FFASN1DEF) # Nothing to do

$(FFASN1OUT).c: $(FFASN1DEF)
	-$(MAKE) --directory $(FFASN1DIR)
	$(FFASN1C) $(FFASN1C_OPTS) -fprefix=$(FFASN1PREFIX) -o $(FFASN1OUT).junk $(FFASN1DEF)
	$(FFASN1PY)                -fprefix=$(FFASN1PREFIX)    $(FFASN1OUT).junk $(FFASN1DEF)
	# Since we're linking against itsasn, we don't need to create a link to (and complile) the asn.1 codec files
	#@mkdir -p $(SRCDIR)/src/libffasn1
	#ln -sf $(FFASN1DIR)/src/libffasn1/*.[ch] $(SRCDIR)/libffasn1

asn-gen: $(FFASN1OUT).c ## Create all ASN.1 generated code
.PHONY: asn-gen

# v2x-lib targets
$(STACKDIR)/v2x-lib/include $(STACKDIR)/v2x-lib/lib/$(BOARD):
	# Build the v2x-libs via the $(STACKDIR)'s makefile
	if [ -e $(STACKDIR)/Makefile ]; then \
	  $(MAKE) -C $(STACKDIR) BOARD=$(BOARD) lib-package VARIANT=$(VARIANT) ; \
	fi;

$(subst $(OUTDIR)/lib,$(STACKDIR)/v2x-lib/lib/$(BOARD),$(V2XLIBS)): $(STACKDIR)/v2x-lib/lib/$(BOARD)

$(OUTDIR)/include: $(STACKDIR)/v2x-lib/include $(OUTDIR)
	@mkdir -p $@
	@cp -ar $</* $@/

$(V2XLIBS): $(OUTDIR)/lib/%: $(STACKDIR)/v2x-lib/lib/$(BOARD)/% $(OUTDIR)
	@mkdir -p $(dir $@)
	@# The referenced lib*.so library may not exist due to licensing constraints
	@if [ -e $< ]; then \
	  cp -a $< $@ ;\
	fi;

rlw: $(RLW_LIB) ## Build the 'Red Light Warning' plugin

$(SRCDIR)/src/RLW/RLW_debug.h: $(SRCDIR)/src/RLW/RLW.conf
	cd $(@D) && \
	  if [ -e $(STACKDIR)/tools/conf ] ; then  \
	    $(STACKDIR)/tools/conf    --conf $< --prefix Cust_App_RLW --compact --no-cpp; \
	  else \
	    $(STACKDIR)/tools/conf.py --conf $< --prefix Cust_App_RLW --compact --no-cpp; \
	  fi ;

rlw-gen: $(SRCDIR)/src/RLW/RLW_debug.h

.PHONY: rlw rlw-gen

$(RLW_LIB): $(OUTDIR)/include $(V2XLIBS) $(RLW_OBJS)
ifneq (,$(findstring $(BOARD),mq5))
	$(CC) -shared $(LDFLAGS) $(LDLIBS) -Wl,--no-keep-memory -o $@ $(RLW_OBJS)
else
	$(CC) -shared $(LDFLAGS)                                -o $@ $(RLW_OBJS)
endif

$(SRCDIR)/src/ExampleETSI_debug.h: $(SRCDIR)/src/ExampleETSI.conf
	cd $(@D) && \
	if [ -e $(STACKDIR)/tools/conf ] ; then  \
	  $(STACKDIR)/tools/conf    --conf $< --prefix ExampleETSI --compact --no-cpp; \
	else \
	  $(STACKDIR)/tools/conf.py --conf $< --prefix ExampleETSI --compact --no-cpp; \
	fi ;

src-gen: $(SRCDIR)/src/ExampleETSI_debug.h

# Build the application
$(OUTDIR)/$(APP): $(OUTDIR)/include $(V2XLIBS) $(RLW_LIB) $(OBJS) $(LIBS)
ifeq ($(BOARD),mq5)
	# The QNX linker assumes the presence of '-fpic' means we want a shared library rather than an executable
	$(CC) $(filter-out -fpic,$(CCOPTS) $(CPPFLAGS) $(CFLAGS) $(EXTRA_CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) $(LDLIBS)) -o $@
else
	cd $(BOARD) && $(CC) $(CCOPTS) $(CPPFLAGS) $(CFLAGS) $(EXTRA_CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) $(LDLIBS) -o $@
endif

$(OUTDIR): # Create a per-target $(OUTDIR)
	@mkdir -p $(OUTDIR)
	@ln -sf $(SRCDIR)/* $(OUTDIR)/ # Link the contents of $(SRCDIR) en-mass to $(OUTDIR)
	@rm -f $(OUTDIR)/$(BOARD) # No circular references allowed
	@rm -f $(OUTDIR)/Makefile # A makefile in $(OUTDIR) is just confusing
	@rm -f $(OUTDIR)/src && mkdir -p $(OUTDIR)/src # Remove the link to src/ and make our own (for build artefacts)
	@mkdir -p $(OUTDIR)/src/RLW

version: $(OUTDIR)
	touch $(OUTDIR)/$@
	svn info $(CURDIR) > /dev/null 2>&1 ; \
	  if [ $$? -eq 0 ]; then \
	    echo $(SVNVERSION) > $(OUTDIR)/$@; \
	  fi;
.PHONY: version

DESTDIR:=$(shell mktemp -d)

# Note the lack of folder prefixes below. TOSHIP files are sourced from $(CURDIR) *and* $(BOARD)
TOSHIP = $(APP) \
         rc.$(APP) \
         board/board.conf \
         obu.cfg obu.conf \
         rsu.cfg rsu.conf \
         raw.cfg raw.conf \
         rww*.cfg rww*.conf \
         spat_map*.cfg spat_map*.conf \
         evw.cfg evw.conf \
	 TollDB.bin \
         ui \
         lib \
         aerolink \
         post_install \
         version

BOARD_CONF = $(BOARD).conf

board/board.conf:
	rm -rf $@ && ln -s $(BOARD_CONF) $@

.PHONY: board/board.conf

tarball: all board/board.conf ## Create a $(APP) tarball. Use `BOARD`-tarball to generate for other targets (e.g. mk5-tarball)
	rm -f $(APP)-$(BOARD)-*.tgz
	rm -rf $(DESTDIR)
	mkdir -p $(DESTDIR)/$(APP)
	cd $(CURDIR) && rsync -avRL \
	 --exclude="*src*" --exclude="lib*.a" --ignore-missing-args \
	 $(TOSHIP) $(DESTDIR)/$(APP) 2>/dev/null || true
	cd $(OUTDIR) && rsync -avRL \
	 --exclude="*src*" --exclude="lib*.a" --ignore-missing-args \
	 $(TOSHIP) $(DESTDIR)/$(APP) 2>/dev/null || true
	-$(SUDO) chown -R root:root $(DESTDIR)
	tar -C $(DESTDIR) \
	 --exclude-vcs -czf $(CURDIR)/$(APP)-$(BOARD)-$(SVNVERSION).tgz ./
	-$(SUDO) chown $(USER):$(USER) $(CURDIR)/$(APP)-$(BOARD)-$(SVNVERSION).tgz
	$(SUDO) rm -rf $(DESTDIR)
	@echo "== tarball =="
	du -h $(realpath $(CURDIR))/$(APP)-$(BOARD)-$(SVNVERSION).tgz

%-tarball:
	env BOARD=$* $(MAKE) tarball

.PHONY: tarball %-tarball

install: $(BOARD)-tarball ## Install $(NATIVE) $(APP) to $(INSTALLDIR)/opt/cohda/application
	$(SUDO) install -d $(INSTALLDIR)/opt/cohda/application
ifneq (,$(findstring $(BOARD),mq5))
	# QNX's buildfile doesn't seem to support globbing so temporarily remove the version number when installing
	@mv -f $(CURDIR)/$(APP)-$(BOARD)-$(SVNVERSION).tgz $(CURDIR)/$(APP)-$(BOARD).tgz
	$(SUDO) install -c $(CURDIR)/$(APP)-$(BOARD).tgz $(INSTALLDIR)/opt/cohda/application
	@mv -f $(CURDIR)/$(APP)-$(BOARD).tgz $(CURDIR)/$(APP)-$(BOARD)-$(SVNVERSION).tgz
else
	$(SUDO) install -c $(CURDIR)/$(APP)-$(BOARD)-$(SVNVERSION).tgz $(INSTALLDIR)/opt/cohda/application
endif

.PHONY: install

# Note the 'clean's
# Use 'clean' to remove locally compiled objects (and associated executables & files)
# Use 'v2xclean' to remove the 'v2x-lib' artefacts too

v2xclean: clean
	@if [ -d "$(STACKDIR)/src" ]; then \
	  echo "Cleaning v2x-lib" ; \
	  rm -rf $(STACKDIR)/v2x-lib/include ; \
	  rm -rf $(STACKDIR)/v2x-lib/lib/$(BOARD) ; \
	fi

clean: ## Clean up. Use `BOARD`-clean to specify the target (e.g. mk5-clean)
	@# Generated source(s)
	rm -f $(FFASN1OUT)*
	rm -rf $(SRCDIR)/src/RLW/RLW_*
	rm -rf $(SRCDIR)/src/ExampleETSI_*
	@# Build tree
	$(SUDO) rm -rf $(OUTDIR)
	@# Deployment files & folders
	rm -f $(APP)-$(BOARD)-*.tgz
	rm -f board/board.conf

%-clean:
	env BOARD=$* $(MAKE) clean

.PHONY: clean %-clean

help:
	@echo -e "$$(grep -hE '^\S+:.*##' $(MAKEFILE_LIST) | sed -e 's/:.*##\s*/:/' -e 's/^\(.\+\):\(.*\)/\\x1b[36m\1\\x1b[m:\2/' | column -c2 -t -s :)"

.PHONY: help

#############################################################################
# $(BOARD) specific rules
#############################################################################

$(NATIVE) mk5 mk6 mk6c mq5:
	env BOARD=$@ $(MAKE) app

.PHONY: $(NATIVE) mk5 mk6 mk6c mq5
