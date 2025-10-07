TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================
LIBRARY_NAME = ADKinetix

USR_CPPFLAGS_Linux += -std=c++11 -I$(PVCAM_INCLUDE)
USR_LDFLAGS_Linux += -L$(PVCAM_LIB)

USR_CPPFLAGS_WIN32 += /I$(PVCAM_INCLUDE)
USR_LDFLAGS_WIN32 += /LIBPATH$(PVCAM_LIB)

LIBRARY_IOC = $(LIBRARY_NAME)

#Include driver code
LIB_SRCS += ADKinetix.cpp

LIB_LIBS_WIN32 += pvcam64
LIB_SYS_LIBS_LINUX += pvcam

DBD += kinetixSupport.dbd

include $(ADCORE)/ADApp/commonLibraryMakefile

#=============================


include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
