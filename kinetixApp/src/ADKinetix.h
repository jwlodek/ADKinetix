/**
 * ADKinetix.h
 *
 * ADKinetix EPICS areaDetector driver header file
 *
 * Author: Jakub Wlodek
 *
 * Created: 10-Mar-2024
 * Last Updated: 26-Jul-2024
 * Copyright (c): Brookhaven National Laboratory 2024
 */

// Include guard
#ifndef ADKINETIX_H
#define ADKINETIX_H

// Driver version numbers
#define ADKINETIX_VERSION 1
#define ADKINETIX_REVISION 4
#define ADKINETIX_MODIFICATION 0

// Standard Includes
#include <errno.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <condition_variable>
#include <mutex>

// EPICS includes
#include <cantProceed.h>
#include <epicsEvent.h>
#include <epicsExit.h>
#include <epicsExport.h>
#include <epicsMutex.h>
#include <epicsStdio.h>
#include <epicsString.h>
#include <epicsThread.h>
#include <epicsTime.h>
#include <iocsh.h>

#include "ADDriver.h"

// PvCam includes
#include "master.h"
#include "pvcam.h"

// Helper data structure definitions
#include "ADKinetixDS.h"

// Size of the continuous acquisition circular buffer
#define KTX_CIRC_BUFF_SIZE 50

// Driver name
static const char* driverName = "ADKinetix";

// Error message formatters
#define ERR(msg)                                      \
    if (this->getLogLevel() >= KTXLogLevel::ERROR) \
        fprintf(stderr, "ERROR | %s::%s: %s\n", driverName, __func__, msg);

#define ERR_ARGS(fmt, ...)                            \
    if (this->getLogLevel() >= KTXLogLevel::ERROR) \
        fprintf(stderr, "ERROR | %s::%s: " fmt "\n", driverName, __func__, __VA_ARGS__);

#define ERR_TO_STATUS(fmt, ...)                                       \
    if (this->getLogLevel() >= KTXLogLevel::ERROR) {               \
        char errMsg[256];                                             \
        snprintf(errMsg, sizeof(errMsg), fmt, __VA_ARGS__);           \
        printf("ERROR | %s::%s: %s\n", driverName, __func__, errMsg); \
        setStringParam(ADStatusMessage, errMsg);                      \
        setIntegerParam(ADStatus, ADStatusError);                     \
        callParamCallbacks();                                         \
    }

// Warning message formatters
#define WARN(msg)                                       \
    if (this->getLogLevel() >= KTXLogLevel::WARNING) \
        fprintf(stderr, "WARNING | %s::%s: %s\n", driverName, __func__, msg);

#define WARN_ARGS(fmt, ...)                             \
    if (this->getLogLevel() >= KTXLogLevel::WARNING) \
        fprintf(stderr, "WARNING | %s::%s: " fmt "\n", driverName, __func__, __VA_ARGS__);

#define WARN_TO_STATUS(fmt, ...)                                         \
    if (this->getLogLevel() >= KTXLogLevel::WARNING) {                \
        char warnMsg[256];                                               \
        snprintf(warnMsg, sizeof(warnMsg), fmt, __VA_ARGS__);            \
        printf("WARNING | %s::%s: %s\n", driverName, __func__, warnMsg); \
        setStringParam(ADStatusMessage, warnMsg);                        \
        callParamCallbacks();                                            \
    }

// Info message formatters
#define INFO(msg)                                    \
    if (this->getLogLevel() >= KTXLogLevel::INFO) \
        fprintf(stdout, "INFO | %s::%s: %s\n", driverName, __func__, msg);

#define INFO_ARGS(fmt, ...)                          \
    if (this->getLogLevel() >= KTXLogLevel::INFO) \
        fprintf(stdout, "INFO | %s::%s: " fmt "\n", driverName, __func__, __VA_ARGS__);

#define INFO_TO_STATUS(fmt, ...)                                      \
    if (this->getLogLevel() >= KTXLogLevel::INFO) {                \
        char infoMsg[256];                                            \
        snprintf(infoMsg, sizeof(infoMsg), fmt, __VA_ARGS__);         \
        printf("INFO | %s::%s: %s\n", driverName, __func__, infoMsg); \
        setStringParam(ADStatusMessage, infoMsg);                     \
        callParamCallbacks();                                         \
    }

// Debug message formatters
#define DEBUG(msg)                                    \
    if (this->getLogLevel() >= KTXLogLevel::DEBUG) \
        fprintf(stdout, "DEBUG | %s::%s: %s\n", driverName, __func__, msg);

#define DEBUG_ARGS(fmt, ...)                          \
    if (this->getLogLevel() >= KTXLogLevel::DEBUG) \
        fprintf(stdout, "DEBUG | %s::%s: " fmt "\n", driverName, __func__, __VA_ARGS__);

enum class KTXLogLevel {
    NONE = 0,      // No logging
    ERROR = 10,    // Error messages only
    WARNING = 20,  // Warnings and errors
    INFO = 30,     // Info, warnings, and errors
    DEBUG = 40     // Debugging information
};

// Three supported trigger modes
typedef enum {
    KTX_TRIG_INTERNAL = 0,
    KTX_TRIG_EDGE = 1,
    KTX_TRIG_GATE = 2,
} KTX_TRIG_MODE;

// Supported interface modes
typedef enum {
    KTX_INTF_UNKNOWN = 0,
    KTX_INTF_USB = 1,
    KTX_INTF_USB_1_1 = 2,
    KTX_INTF_USB_2_0 = 3,
    KTX_INTF_USB_3_0 = 4,
    KTX_INTF_USB_3_1 = 5,
    KTX_INTF_PCIE = 6,
    KTX_INTF_PCIE_x1 = 7,
    KTX_INTF_PCIE_x4 = 8,
    KTX_INTF_PCIE_x8 = 9,
    KTX_INTF_VIRTUAL = 10,
    KTX_INTF_ETHERNET = 11,
} KTX_COMM_INTF;

// Potential minimum exposure resolution
typedef enum {
    KTX_MIN_EXP_RES_S = 0,
    KTX_MIN_EXP_RES_MS = 1,
    KTX_MIN_EXP_RES_US = 2,
} KTX_MIN_EXP_RES;

class ADKinetix : public ADDriver {
   public:
    ADKinetix(int deviceIndex, const char* portName);

    /* These are the methods that we override from ADDriver */
    virtual asynStatus readEnum(asynUser* pasynUser, char* strings[], int values[],
                                int severities[], size_t nElements, size_t* nIn);
    virtual asynStatus writeInt32(asynUser* pasynUser, epicsInt32 value);
    virtual asynStatus writeFloat64(asynUser* pasynUser, epicsFloat64 value);
    void report(FILE* fp, int details);
    void monitorThread();
    void acquisitionThread();
    ~ADKinetix();
    bool waitForEofEvent(uns32 timeoutMs);
    KTXLogLevel getLogLevel() { return this->logLevel; }

   protected:
#include "ADKinetixParamDefs.h"

   private:
    void reportKinetixError(const char* functionName);
    void createAllParams();

    bool isParamAvailable(int16 hcam, uns32 paramID, const char* paramName);
    bool readEnumeration(int16 hcam, NVPC* pNvpc, uns32 paramID, const char* paramName);
    void printSpeedTable();
    bool getSpeedTable();
    void updateImageFormat();
    void updateReadoutPortDesc();
    void selectSpeedTableMode();

    void acquireStart();
    void acquireStop();
    void updateCameraRegion();
    void getCurrentFrameDimensions(size_t* dims);
    asynStatus setMinExpRes(KTX_MIN_EXP_RES currentExpRes, KTX_MIN_EXP_RES minExpRes);

    NDDataType_t getCurrentNDBitDepth();
    KTXLogLevel logLevel = KTXLogLevel::INFO;
    CameraContext* cameraContext;
    bool acquisitionActive = false;
    bool speedTableModeSelected = false;
    bool pollingTemperature = false;
    bool monitoringActive = false;
    int deviceIndex;
    void* frameBuffer = nullptr;
    epicsThreadId monitorThreadId, acquisitionThreadId;
};

#endif
