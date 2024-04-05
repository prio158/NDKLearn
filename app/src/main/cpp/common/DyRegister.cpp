//
// Created by chen_zi_rui on 2024/4/5.
//
#include "DyRegister.h"

void dynamicNative1(JNIEnv *env, jobject jobj) {
    LOGE("dynamicNative1 动态注册");
}

jstring dynamicNative2(JNIEnv *env, jobject jobj, jint i) {
    return env->NewStringUTF("我是动态注册的dynamicNative2方法");
}



