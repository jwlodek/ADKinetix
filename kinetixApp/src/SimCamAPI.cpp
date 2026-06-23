#include "SimCamAPI.h"
#include <pvcam.h>
#include <map>
#include <cstring>

// Singleton parameter map for simulated camera
static std::map<uint32_t, uint32_t> simParameterMap;
static bool simInitialized = false;
static int16_t simOpenCameras = 0;

void initSimParameters() {
    if (simInitialized) return;
    
    // Initialize common camera parameters with simulated values
    simParameterMap[PARAM_READOUT_PORT] = 0;
    simParameterMap[PARAM_SPDTAB_INDEX] = 0;
    simParameterMap[PARAM_PIX_TIME] = 200;  // nanoseconds
    simParameterMap[PARAM_GAIN_INDEX] = 1;
    simParameterMap[PARAM_BIT_DEPTH] = 16;
    simParameterMap[PARAM_IMAGE_FORMAT] = PL_IMAGE_FORMAT_MONO16;
    simParameterMap[PARAM_CAM_FW_VERSION] = 0x0100;  // Version 1.0
    simParameterMap[PARAM_CAM_INTERFACE_TYPE] = PL_CAM_IFC_TYPE_USB_3_0;
    simParameterMap[PARAM_SER_SIZE] = 2048;  // 2048 pixels width
    simParameterMap[PARAM_PAR_SIZE] = 2048;  // 2048 pixels height
    simParameterMap[PARAM_TEMP] = 2500;  // 25.00 degrees C (in hundredths)
    simParameterMap[PARAM_COOLING_MODE] = NORMAL_COOL;
    simParameterMap[PARAM_PMODE] = PMODE_NORMAL;
    
    simInitialized = true;
}

bool SimCamAPI::getVersion(uint16_t* version) {
    if (!version) return false;
    *version = 0x0304;  // Version 3.4
    return true;
}

bool SimCamAPI::init() {
    initSimParameters();
    return true;
}

bool SimCamAPI::uninit() {
    simParameterMap.clear();
    simInitialized = false;
    simOpenCameras = 0;
    return true;
}

bool SimCamAPI::resetPostProcessing(int16_t cameraHandle) {
    return true;
}

bool SimCamAPI::registerNewFrameCallbackEx3(int16_t cameraHandle, int32_t callbackEvent, void* callback, void* context) {
    // Simulated - just accept the callback registration
    return true;
}

bool SimCamAPI::getCameraName(int16_t deviceIndex, char* nameBuffer) {
    if (!nameBuffer) return false;
    
    if (deviceIndex == 0) {
        strncpy(nameBuffer, "SimulatedCamera-0", 32);
        return true;
    } else if (deviceIndex == 1) {
        strncpy(nameBuffer, "SimulatedCamera-1", 32);
        return true;
    }
    return false;
}

bool SimCamAPI::getNumberOfCameras(int16_t* numCameras) {
    if (!numCameras) return false;
    *numCameras = 2;  // Simulate 2 cameras
    return true;
}

bool SimCamAPI::openCamera(char* camName, int16_t* cameraHandle, int16_t accessMode) {
    if (!camName || !cameraHandle) return false;
    
    // Simulate opening a camera by assigning a handle
    *cameraHandle = simOpenCameras;
    simOpenCameras++;
    return true;
}

bool SimCamAPI::closeCamera(int16_t cameraHandle) {
    if (cameraHandle >= 0) {
        return true;
    }
    return false;
}

int16_t SimCamAPI::getErrorCode() {
    return 0;  // No error
}

bool SimCamAPI::getErrorMessage(int16_t errorCode, char* errorMsgBuffer) {
    if (!errorMsgBuffer) return false;
    
    if (errorCode == 0) {
        strncpy(errorMsgBuffer, "No error", 255);
    } else {
        strncpy(errorMsgBuffer, "Unknown error", 255);
    }
    return true;
}

bool SimCamAPI::getParameter(int16_t cameraHandle, uint32_t paramID, int16_t paramAttr, void* value) {
    if (!value) return false;
    
    if (paramAttr == ATTR_CURRENT) {
        // Return current parameter value
        auto it = simParameterMap.find(paramID);
        if (it != simParameterMap.end()) {
            *(uint32_t*)value = it->second;
            return true;
        }
    } else if (paramAttr == ATTR_AVAIL) {
        // Return whether parameter is available
        *(rs_bool*)value = TRUE;
        return true;
    } else if (paramAttr == ATTR_COUNT) {
        // Return count for array/enum parameters
        switch (paramID) {
            case PARAM_READOUT_PORT:
                *(uint32_t*)value = 2;  // 2 readout ports
                return true;
            case PARAM_SPDTAB_INDEX:
                *(uint32_t*)value = 3;  // 3 speed indices
                return true;
            case PARAM_GAIN_INDEX:
                *(uint32_t*)value = 4;  // 4 gain levels
                return true;
            default:
                *(uint32_t*)value = 0;
                return true;
        }
    } else if (paramAttr == ATTR_TYPE) {
        // Return parameter type
        *(uint16_t*)value = TYPE_INT32;
        return true;
    }
    
    return false;
}

bool SimCamAPI::setParameter(int16_t cameraHandle, uint32_t paramID, void* value) {
    if (!value) return false;
    
    // Allow setting parameter values
    simParameterMap[paramID] = *(uint32_t*)value;
    return true;
}

bool SimCamAPI::getEnumStrLength(int16_t cameraHandle, uint32_t paramID, uint32_t index, uint32_t* length) {
    if (!length) return false;
    
    // Return string length for enum descriptions
    *length = 32;
    return true;
}

bool SimCamAPI::getEnumParameter(int16_t cameraHandle, uint32_t paramID, uint32_t index, int32_t* value, char* desc, uint32_t length) {
    if (!value || !desc) return false;
    
    // Simulate enum parameters
    switch (paramID) {
        case PARAM_READOUT_PORT:
            if (index == 0) {
                *value = 0;
                strncpy(desc, "Port 0", length);
            } else if (index == 1) {
                *value = 1;
                strncpy(desc, "Port 1", length);
            } else {
                return false;
            }
            return true;
        
        case PARAM_SPDTAB_INDEX:
            if (index < 3) {
                *value = index;
                snprintf(desc, length, "Speed %u", index);
                return true;
            }
            return false;
        
        case PARAM_GAIN_INDEX:
            if (index >= 1 && index <= 4) {
                *value = index;
                snprintf(desc, length, "Gain %u", index);
                return true;
            }
            return false;
        
        default:
            return false;
    }
}

bool SimCamAPI::setupExposureSequence(int16_t cameraHandle, uint16_t exposureTotal, uint16_t regionTotal, const ROI* rois, int16_t exposureMode, uint32_t exposureTime, uint32_t* exposureBytes) {
    if (!exposureBytes || !rois) return false;
    
    // Calculate frame size based on region
    uint32_t width = (rois->s2 - rois->s1 + 1) / rois->sbin;
    uint32_t height = (rois->p2 - rois->p1 + 1) / rois->pbin;
    
    // Assume 16-bit mono format
    *exposureBytes = width * height * 2;
    return true;
}

bool SimCamAPI::startExposureSequence(int16_t cameraHandle, void* pixelStream) {
    return true;
}

bool SimCamAPI::finishExposureSequence(int16_t cameraHandle, void* pixelStream, int16_t hbuf) {
    return true;
}

bool SimCamAPI::setupContinuousExposure(int16_t cameraHandle, int16_t regionTotal, const ROI* rois, int16_t exposureMode, uint32_t exposureTime, uint32_t* exposureBytes, int16_t bufferMode) {
    if (!exposureBytes || !rois) return false;
    
    // Calculate frame size based on region
    uint32_t width = (rois->s2 - rois->s1 + 1) / rois->sbin;
    uint32_t height = (rois->p2 - rois->p1 + 1) / rois->pbin;
    
    // Assume 16-bit mono format
    *exposureBytes = width * height * 2;
    return true;
}

bool SimCamAPI::startContinuousExposure(int16_t cameraHandle, void* pixelStream, uint32_t circBufferSize) {
    return true;
}

bool SimCamAPI::abortExposure(int16_t cameraHandle, int16_t cameraState) {
    return true;
}
