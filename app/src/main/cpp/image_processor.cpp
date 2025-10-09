#include "image_processor.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <android/log.h>
#include <cstring>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,  "IMGPROC", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "IMGPROC", __VA_ARGS__)
using namespace cv;

static inline uint8_t* ptr(JNIEnv* env, jobject buf) {
  return reinterpret_cast<uint8_t*>(env->GetDirectBufferAddress(buf));
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_edgeviewer_NativeBridge_processYToRgba(
    JNIEnv* env, jclass,
    jobject yPlane, jint width, jint height, jint rowStride,
    jboolean doCanny, jobject outRgba) {

  if (!yPlane || !outRgba) return;
  auto* yPtr   = ptr(env, yPlane);
  auto* outPtr = ptr(env, outRgba);
  if (!yPtr || !outPtr) return;

  // Wrap Y as a stride-aware Mat then compact to width
  Mat yStrided(height, rowStride, CV_8UC1, yPtr);
  Mat gray(height, width,   CV_8UC1);
  for (int r = 0; r < height; ++r) {
    memcpy(gray.ptr(r), yStrided.ptr(r), width);
  }

  Mat processed;
  if (doCanny) {
    Mat blurred;
    GaussianBlur(gray, blurred, Size(5,5), 1.2);
    Canny(blurred, processed, 80, 160);
  } else {
    processed = gray;
  }

  Mat rgba;
  cvtColor(processed, rgba, COLOR_GRAY2RGBA);
  memcpy(outPtr, rgba.data, static_cast<size_t>(width) * height * 4);
}
