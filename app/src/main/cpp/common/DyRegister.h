//
// Created by chen_zi_rui on 2024/4/5.
//

#ifndef JNILEARN_DYREGISTER_H
#define JNILEARN_DYREGISTER_H

#include <jni.h>
#include "Log.h"
#include <string>

void dynamicNative1(JNIEnv *env, jobject jobj);

jstring dynamicNative2(JNIEnv *env, jobject jobj, jint i);

/**
 * @brief 动态注册的方法
 * */
static const JNINativeMethod nativeMethods[] = {
        {"dynamicNative", "()V",                   (void *) dynamicNative1},
        {"dynamicNative", "(I)Ljava/lang/String;", (void *) dynamicNative2},
};

static const char *mClassName = "com/example/jnilearn/MainActivity";

/**
 * @brief Java层调用System.load后执行
 * 此时作为动态注册的时机
 * */
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;
    int ret = vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (ret != JNI_OK) {
        LOGE("Get Java Env Fail");
        return -1;
    }
    jclass mActivityCls = env->FindClass(mClassName);
    //将mActivityCls中native方法与nativeMethods进行绑定，其实就是
    //遍历mActivityCls中的声明的native方法与nativeMethods中的name字段进行匹配
    ret = env->RegisterNatives(mActivityCls, nativeMethods, 2);
    if (ret != JNI_OK) {
        return -1;
    }
    return JNI_VERSION_1_6;
}


#endif //JNILEARN_DYREGISTER_H
