#include <jni.h>
#include <vector>
#include "image_processor.h"

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_edgeviewer_MainActivity_processFrameNV21ToRGBA(
        JNIEnv* env,
        jclass,
        jbyteArray nv21_,
        jint width,
        jint height,
        jint rotationDegrees) {

    jsize len = env->GetArrayLength(nv21_);
    std::vector<jbyte> nv21(len);
    env->GetByteArrayRegion(nv21_, 0, len, nv21.data());

    std::vector<int> argb;
    ImageProcessor::nv21ToEdgesARGB(
        reinterpret_cast<unsigned char*>(nv21.data()),
        width, height, rotationDegrees, argb
    );

    jintArray out = env->NewIntArray((jsize)argb.size());
    env->SetIntArrayRegion(out, 0, (jsize)argb.size(),
                           reinterpret_cast<const jint*>(argb.data()));
    return out;
}
