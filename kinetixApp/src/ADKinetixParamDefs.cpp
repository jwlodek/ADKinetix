// This file is auto-generated. Do not edit directly.
// Generated from ADKinetix.template

#include "ADKinetix.h"

void ADKinetix::createAllParams() {
    createParam(KTX_StopAcqOnTimeoutString, asynParamInt32, &KTX_StopAcqOnTimeout);
    createParam(KTX_WaitForFrameTimeoutString, asynParamInt32, &KTX_WaitForFrameTimeout);
    createParam(KTX_TemperatureString, asynParamFloat64, &KTX_Temperature);
    createParam(KTX_ReadoutPortIdxString, asynParamInt32, &KTX_ReadoutPortIdx);
    createParam(KTX_ReadoutModeString, asynParamOctet, &KTX_ReadoutMode);
    createParam(KTX_ReadoutPortDescString, asynParamOctet, &KTX_ReadoutPortDesc);
    createParam(KTX_SpeedIdxString, asynParamInt32, &KTX_SpeedIdx);
    createParam(KTX_SpeedDescString, asynParamOctet, &KTX_SpeedDesc);
    createParam(KTX_GainIdxString, asynParamInt32, &KTX_GainIdx);
    createParam(KTX_MinExpResString, asynParamInt32, &KTX_MinExpRes);
    createParam(KTX_GainDescString, asynParamOctet, &KTX_GainDesc);
    createParam(KTX_ApplyReadoutModeString, asynParamInt32, &KTX_ApplyReadoutMode);
    createParam(KTX_ModeValidString, asynParamInt32, &KTX_ModeValid);
    createParam(KTX_CommInterfaceString, asynParamInt32, &KTX_CommInterface);
    createParam(KTX_FanSpeedString, asynParamInt32, &KTX_FanSpeed);
}
