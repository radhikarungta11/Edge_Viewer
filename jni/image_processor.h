#pragma once
#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_example_edgeviewer_NativeBridge_processYToRgba(
    JNIEnv* env, jclass clazz,
    jobject yPlane, jint width, jint height, jint rowStride,
    jboolean doCanny, jobject outRgba);

#ifdef __cplusplus
}
#endif

