//
// Created by chen_zi_rui on 2024/4/5.
//
#include "DyRegister.h"

void dynamicNative1(JNIEnv *env, jobject jobj) {
    LOGI("dynamicNative1 动态注册");
}

jstring dynamicNative2(JNIEnv *env, jobject jobj, jint i) {
    auto num = std::to_string(i);
    auto str = "dynamicNative2 动态注册, num:" + num;
    LOGI("%s", str.c_str());
    return env->NewStringUTF("动态注册的dynamicNative2方法");
}



