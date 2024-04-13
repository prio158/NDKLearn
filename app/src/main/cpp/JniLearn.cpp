#include <jni.h>
#include <string>
#include "common/Log.h"


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnilearn_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

/**
 * @brief 访问Java层的传入的String
 *
 * */
extern "C"
JNIEXPORT jstring  JNICALL
Java_com_example_jnilearn_MainActivity_00024Companion_stringFromJNITest(JNIEnv *env, jobject thiz,
                                                                        jstring str) {
    //String (Java UTF16) ---> jstring (JNI UTF-8) ---> GetStringUTFChars (C++ UTF-8)
    //GetStringUTFChars方法就是将Java层传过来String转为C++能使用的。
    const char *tmp = env->GetStringUTFChars(str, nullptr);
    if (tmp == nullptr) {
        return nullptr;
    }
    //字符串拼接
    char buf[128] = {0};
    sprintf(buf, "Hello %s", tmp);
    //GetStringUTFChars内部会分配一块新的内存用于存储str，所以使用完毕需要释放
    env->ReleaseStringUTFChars(str, tmp);
    return env->NewStringUTF(buf);
}

/**
 * @brief 访问Java层的属性
 *
 * */
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnilearn_MainActivity_findJavaPropertyFromJNI(JNIEnv *env, jobject thiz) {

    //先调用GetObjectClass函数获取ClassField的Class引用
    jclass clazz = env->GetObjectClass(thiz);
    //后调用GetFieldID函数从Class引用中获取字段的ID（property是字段名，I是字段的签名）
    jfieldID jfid = env->GetFieldID(clazz, "property", "I");
    //调用GetIntField函数，传入实例对象和字段ID，获取属性的值
    jint value = env->GetIntField(thiz, jfid);
    //如果要修改这个值就可以使用SetIntField函数
    env->SetIntField(thiz, jfid, 2048);
}

/**
 * @brief 访问Java层的静态属性
 *
 * */
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnilearn_MainActivity_findJavaStaticPropertyFromJNI(JNIEnv *env, jobject thiz) {

    jclass clazz = env->GetObjectClass(thiz);
    jfieldID jfieldId = env->GetStaticFieldID(clazz, "Property", "I");
    jint value = env->GetStaticIntField(clazz, jfieldId);
    env->SetStaticIntField(clazz, jfieldId, 1314);
}

/**
 * @brief 访问Java层的静态方法
 *
 * */
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnilearn_MainActivity_callJavaStaticMethod(JNIEnv *env, jobject thiz) {

    // 为什么不用jclass clazz = env->GetObjectClass(thiz);
    // 因为这样获取class是MainActivity的，我们想要调用其他Class的方法的时候，就需要使用下面的方法
    auto clazz = env->FindClass("com/example/jnilearn/MainActivity");
    if (clazz == nullptr) {
        LOGE("Find Class:[com/example/jnilearn/MainActivity] Fail");
        return;
    }
    auto jmethodId = env->GetStaticMethodID(clazz, "callVoidStaticMethod", "(Ljava/lang/String;I)V");
    if (jmethodId == nullptr) {
        LOGE("Class:[com/example/jnilearn/MainActivity] have no method [callStaticMethod]");
        return;
    }
    auto arg = env->NewStringUTF("Native XXXX");
    env->CallStaticVoidMethod(clazz, jmethodId, arg, 100);
    env->DeleteLocalRef(clazz);
    env->DeleteLocalRef(arg);
}


























