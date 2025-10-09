#pragma once
#include <jni.h>

extern "C" JNIEXPORT void JNICALL
Java_com_example_edgeviewer_NativeBridge_processYToRgba(
    JNIEnv* env, jclass clazz,
    jobject yPlane, jint width, jint height, jint rowStride,
    jboolean doCanny, jobject outRgba);
