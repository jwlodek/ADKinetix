TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

USR_CPPFLAGS_Linux += -std=c++11 -I$(PVCAM_INCLUDE)
USR_LDFLAGS_Linux += -L$(PVCAM_LIB) -Wl,-rpath,$(PVCAM_LIB)
USR_CPPFLAGS_WIN32 += /I$(PVCAM_INCLUDE)
USR_LDFLAGS_WIN32 += /LIBPATH$(PVCAM_LIB)

PROD_NAME = kinetixApp

PROD_IOC += $(PROD_NAME)

# <name>.dbd will be created from <name>Include.dbd
DBD += $(PROD_NAME).dbd
$(PROD_NAME)_DBD += kinetixSupport.dbd

# <name>_registerRecordDeviceDriver.cpp will be created from <name>.dbd
$(PROD_NAME)_SRCS += $(PROD_NAME)_registerRecordDeviceDriver.cpp $(PROD_NAME)Main.cpp

# Add locally compiled object code
$(PROD_NAME)_LIBS += ADKinetix

# 64 bit windows support
$(PROD_NAME)_LIBS_WIN32 += pvcam64
$(PROD_NAME)_SYS_LIBS_Linux += pvcam

include $(ADCORE)/ADApp/commonDriverMakefile

#=============================


include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
