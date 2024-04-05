//
// Created by chen_zi_rui on 2024/4/5.
//

#ifndef JNILEARN_DYREGISTER_H
#define JNILEARN_DYREGISTER_H

#include <jni.h>
#include "Log.h"

void dynamicNative1(JNIEnv *env, jobject jobj);

jstring dynamicNative2(JNIEnv *env, jobject jobj, jint i);

/**
 * @brief 动态注册的方法
 * */
static const JNINativeMethod nativeMethods[] = {
        {"", "()v",                  (void *) dynamicNative1},
        {"", "(I)Ljava/lang/String", (void *) dynamicNative2},
};

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

}


#endif //JNILEARN_DYREGISTER_H
