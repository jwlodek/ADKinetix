#ifndef SIMCAMAPI_H
#define SIMCAMAPI_H
#include "ICamAPI.h"

class SimCamAPI : public API {
    public:
        SimCamAPI() = default;
        ~SimCamAPI() = default;

        virtual bool getVersion(uint16_t* version);
        virtual bool init();
        virtual bool uninit();
        virtual bool resetPostProcessing(int16_t cameraHandle);
        virtual bool registerNewFrameCallbackEx3(int16_t cameraHandle, int32_t callbackEvent, void* callback, void* context);
        virtual bool getCameraName(int16_t deviceIndex, char* nameBuffer);
        virtual bool getNumberOfCameras(int16_t* numCameras);
        virtual bool openCamera(char* camName, int16_t* cameraHandle, int16_t accessMode);
        virtual bool closeCamera(int16_t cameraHandle);
        virtual int16_t getErrorCode();
        virtual bool abortExposure(int16_t cameraHandle, int16_t cameraState);
        virtual bool getErrorMessage(int16_t errorCode, char* errorMsgBuffer);
        virtual bool getParameter(int16_t cameraHandle, uint32_t paramID, int16_t paramAttr, void* value);
        virtual bool setParameter(int16_t cameraHandle, uint32_t paramID, void* value);
        virtual bool getEnumStrLength(int16_t cameraHandle, uint32_t paramID, uint32_t index, uint32_t* length);
        virtual bool getEnumParameter(int16_t cameraHandle, uint32_t paramID, uint32_t index, int32_t* value, char* desc, uint32_t length);
        virtual bool setupExposureSequence(int16_t cameraHandle, uint16_t exposureTotal, uint16_t regionTotal, const ROI* rois, int16_t exposureMode, uint32_t exposureTime, uint32_t* exposureBytes);
        virtual bool startExposureSequence(int16_t cameraHandle, void* pixelStream);
        virtual bool finishExposureSequence(int16_t cameraHandle, void* pixelStream, int16_t hbuf);
        virtual bool setupContinuousExposure(int16_t cameraHandle, int16_t regionTotal, const ROI* rois, int16_t exposureMode, uint32_t exposureTime, uint32_t* exposureBytes, int16_t bufferMode);
        virtual bool startContinuousExposure(int16_t cameraHandle, void* pixelStream, uint32_t circBufferSize);


    protected:

    private:
};

#endif // SIMCAMAPI_H
