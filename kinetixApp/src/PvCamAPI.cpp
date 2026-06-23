#include "PvCamAPI.h"
#include <stdexcept>
#include <pvcam.h>

bool PvCamAPI::getVersion(uint16_t* version) {
    return pl_pvcam_get_ver(version) == PV_OK;
}

bool PvCamAPI::init() {
    return pl_pvcam_init() == PV_OK;
}

bool PvCamAPI::uninit() {
    return pl_pvcam_uninit() == PV_OK;
}

bool PvCamAPI::resetPostProcessing(int16_t cameraHandle) {
    return pl_pp_reset(cameraHandle) == PV_OK;
}

bool PvCamAPI::registerNewFrameCallbackEx3(int16_t cameraHandle, int32_t callbackEvent, void* callback, void* context) {
    return pl_cam_register_callback_ex3(cameraHandle, callbackEvent, callback, context) == PV_OK;
}

bool PvCamAPI::getCameraName(int16_t deviceIndex, char* nameBuffer) {
    return pl_cam_get_name(deviceIndex, nameBuffer) == PV_OK;
}

bool PvCamAPI::getNumberOfCameras(int16_t* numCameras) {
    return pl_cam_get_total(numCameras) == PV_OK;
}

bool PvCamAPI::openCamera(char* camName, int16_t* cameraHandle, int16_t accessMode) {
    return pl_cam_open(camName, cameraHandle, accessMode) == PV_OK;
}

bool PvCamAPI::closeCamera(int16_t cameraHandle) {
    return pl_cam_close(cameraHandle) == PV_OK;
}

int16_t PvCamAPI::getErrorCode() {
    return pl_error_code();
}

bool PvCamAPI::getErrorMessage(int16_t errorCode, char* errorMsgBuffer) {
    return pl_error_message(errorCode, errorMsgBuffer) == PV_OK;
}

bool PvCamAPI::getParameter(int16_t cameraHandle, uint32_t paramID, int16_t paramAttr, void* value) {
    return pl_get_param(cameraHandle, paramID, paramAttr, value) == PV_OK;
}

bool PvCamAPI::setParameter(int16_t cameraHandle, uint32_t paramID, void* value) {
    return pl_set_param(cameraHandle, paramID, value) == PV_OK;
}

bool PvCamAPI::getEnumStrLength(int16_t cameraHandle, uint32_t paramID, uint32_t index, uint32_t* length) {
    return pl_enum_str_length(cameraHandle, paramID, index, length) == PV_OK;
}

bool PvCamAPI::getEnumParameter(int16_t cameraHandle, uint32_t paramID, uint32_t index, int32_t* value, char* desc, uint32_t length) {
    return pl_get_enum_param(cameraHandle, paramID, index, value, desc, length) == PV_OK;
}

bool PvCamAPI::setupExposureSequence(int16_t cameraHandle, uint16_t exposureTotal, uint16_t regionTotal, const ROI* rois, int16_t exposureMode, uint32_t exposureTime, uint32_t* exposureBytes) {
    return pl_exp_setup_seq(cameraHandle, exposureTotal, regionTotal, (rgn_type*) rois, exposureMode, exposureTime, exposureBytes) == PV_OK;
}

bool PvCamAPI::startExposureSequence(int16_t cameraHandle, void* pixelStream) {
    return pl_exp_start_seq(cameraHandle, pixelStream) == PV_OK;
}

bool PvCamAPI::finishExposureSequence(int16_t cameraHandle, void* pixelStream, int16_t hbuf) {
    return pl_exp_finish_seq(cameraHandle, pixelStream, hbuf) == PV_OK;
}

bool PvCamAPI::setupContinuousExposure(int16_t cameraHandle, int16_t regionTotal, const ROI* rois, int16_t exposureMode, uint32_t exposureTime, uint32_t* exposureBytes, int16_t bufferMode) {
    return pl_exp_setup_cont(cameraHandle, regionTotal, (rgn_type*) rois, exposureMode, exposureTime, exposureBytes, bufferMode) == PV_OK;
}

bool PvCamAPI::startContinuousExposure(int16_t cameraHandle, void* pixelStream, uint32_t circBufferSize) {
    return pl_exp_start_cont(cameraHandle, pixelStream, circBufferSize) == PV_OK;
}

bool PvCamAPI::abortExposure(int16_t cameraHandle, int16_t cameraState) {
    return pl_exp_abort(cameraHandle, cameraState) == PV_OK;
}
