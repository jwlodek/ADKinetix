#ifndef ICAMAPI_H
#define ICAMAPI_H

#include <cstdint>
#include <string>
#include <vector>


class ROI {
    public:
        ROI(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t binX, uint16_t binY)
            : x(x), y(y), width(width), height(height), binX(binX), binY(binY) {}
        ~ROI() = default;

        std::tuple<uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t> getROI() const {
            return std::make_tuple(x, y, width, height, binX, binY);
        }

    private:
        uint16_t x;
        uint16_t y;
        uint16_t width;
        uint16_t height;
        uint16_t binX;
        uint16_t binY;
};

class API {
    public:
        API() = default;
        ~API() = default;

        virtual bool getVersion(uint16_t* version);
        virtual bool init();
        virtual bool uninit();
        virtual bool resetPostProcessing(int16_t cameraHandle);
        virtual bool registerNewFrameCallback(int16_t cameraHandle, int32_t callbackEvent, void* callback, void* context);
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
        virtual bool isParameterAvailable(int16_t cameraHandle, uint32_t paramID);
        virtual bool setupExposureSequence(int16_t cameraHandle, uint16_t exposureTotal, uint16_t regionTotal, const ROI* rois, int16_t exposureMode, uint32_t exposureTime, uint32_t* exposureBytes);
        virtual bool startExposureSequence(int16_t cameraHandle, void* pixelStream);
        virtual bool finishExposureSequence(int16_t cameraHandle, void* pixelStream, int16_t hbuf);
        virtual bool setupContinuousExposure(int16_t cameraHandle, int16_t regionTotal, const ROI* rois, int16_t exposureMode, uint32_t exposureTime, uint32_t* exposureBytes, int16_t bufferMode);
        virtual bool startContinuousExposure(int16_t cameraHandle, void* pixelStream, uint32_t circBufferSize);


    protected:

    private:
};


#endif // ICAMAPI_H
