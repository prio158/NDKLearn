#include <jni.h>
#include <string>
#include "common/Log.h"


extern "C" JNIEXPORT jstring

JNICALL
Java_com_example_jnilearn_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



