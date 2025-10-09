#include "image_processor.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <android/log.h>
#include <cstring>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,  "IMGPROC", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "IMGPROC", __VA_ARGS__)

using namespace cv;

// Helper to get the raw pointer from a direct ByteBuffer
static inline uint8_t* directPtr(JNIEnv* env, jobject buf) {
    return reinterpret_cast<uint8_t*>(env->GetDirectBufferAddress(buf));
}

JNIEXPORT void JNICALL
Java_com_example_edgeviewer_NativeBridge_processYToRgba(
    JNIEnv* env, jclass /*clazz*/,
    jobject yPlane, jint width, jint height, jint rowStride,
    jboolean doCanny, jobject outRgba) {

    if (!yPlane || !outRgba) {
        LOGE("Null buffers passed to native process");
        return;
    }

    auto* yPtr   = directPtr(env, yPlane);
    auto* outPtr = directPtr(env, outRgba);
    if (!yPtr || !outPtr) {
        LOGE("Non-direct ByteBuffer passed to native");
        return;
    }

    // Wrap the Y plane (with stride) and compact into a width-aligned gray Mat
    Mat yStrided(height, rowStride, CV_8UC1, yPtr);
    Mat gray(height, width, CV_8UC1);
    for (int r = 0; r < height; ++r) {
        std::memcpy(gray.ptr(r), yStrided.ptr(r), static_cast<size_t>(width));
    }

    Mat processed;
    if (doCanny) {
        Mat blurred;
        GaussianBlur(gray, blurred, Size(5, 5), 1.2);
        Canny(blurred, processed, 80, 160);
    } else {
        processed = gray; // raw luminance
    }

    // Convert to RGBA and copy into the output ByteBuffer (capacity >= w*h*4)
    Mat rgba;
    cvtColor(processed, rgba, COLOR_GRAY2RGBA);
    const size_t bytes = static_cast<size_t>(width) * static_cast<size_t>(height) * 4;
    std::memcpy(outPtr, rgba.data, bytes);
}

