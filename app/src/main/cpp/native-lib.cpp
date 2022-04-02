#include <jni.h>
#include <string>
#include<android/log.h>

#define TAG "Native-Jni" // 这个是自定义的LOG的标识
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型

long long GetNowMs();

extern "C" JNIEXPORT jstring JNICALL
Java_com_gqy_jnidemo_JniLib_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

//    JNI_CreateJavaVM()
//env->NewObject();  // 创建Java中的对象
//env->NewObjectArray() // 创建对象数组；
//env->GetObjectArrayElement()  获取数组中某个位置的元素

//env->NewIntArray(1); // 新建基本数据类型数组
//env->NewShortArray(1);
//env->NewLongArray(1);
//env->NewFloatArray(1);
//env->NewDoubleArray(1);

//env->NewCharArray(1);

//env->GetArrayLength()   获取数组长度
//env->IsSameObject()

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_gqy_jnidemo_JniLib_calcSum(JNIEnv *env, jclass clazz, jint left, jint cnt) {
    LOGI("..%s..%d..left=%d,cnt=%d", __FUNCTION__, __LINE__, left, cnt);
    long long startTime = GetNowMs();
    LOGI("start..%lld", startTime); // 开始时间
    int sum = left;
    for (int i = 0; i < cnt; ++i) {
        sum += i;
    }
    long long endTime = GetNowMs();
    long long distance = endTime - startTime;
    LOGI("end..%lld ms", endTime);
    LOGI("cost time..%lld ms", distance);
    return distance;
}

long long GetNowMs() {
    struct timeval tv;
    gettimeofday(&tv, NULL);//  tv.tv_sec 很大，%36000 取得100个小时前的时间，不除也可以
    int sec = tv.tv_sec % 36000;
    long long t = sec * 1000 + tv.tv_usec / 1000;
    return t;
}

/**
 * 把一个jstring转换成一个c语言的char* 类型.
 * @param env
 * @param jstr
 * @return
 */
char *_JString2CStr(JNIEnv *env, jstring jstr) {
    char *dest = NULL;
    jclass jcaz = env->FindClass("java/lang/String");
    jstring encode = env->NewStringUTF("GB2312");
    jmethodID method = env->GetMethodID(jcaz, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray array = (jbyteArray) env->CallObjectMethod(jstr, method, encode);
    jsize len = env->GetArrayLength(array);

    jbyte *p = env->GetByteArrayElements(array, JNI_FALSE);
    if (len > 0) {
        dest = (char *) malloc(len + 1);
        memcpy(dest, p, len);
        dest[len] = '\0';
    }
    env->ReleaseByteArrayElements(array, p, 0);
    return dest;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_gqy_jnidemo_JniLib_compareStr(JNIEnv *env, jclass clazz, jstring left, jstring right) {
    char *cleft = _JString2CStr(env, left);
    char *cright = _JString2CStr(env, right);
    LOGI("jstring to cstring. cleft=%s", cleft);
    LOGI("jstring to cstring. cright=%s", cright);
    int equal = strcmp(cleft, cright);
    LOGI("compare ret=%d", equal);
    return equal;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_gqy_jnidemo_JniLib_jniMethodLx(JNIEnv *env, jobject obj, jint len, jstring flag) {
    // jstring转 char *
    const char *flagStr = env->GetStringUTFChars(flag, JNI_FALSE);
    LOGI("enter methodLx,len=%d  flag=%s \n", len, flagStr);

    LOGI("jni version= %#x \n", env->GetVersion()); //返回本地JNI方法接口的版本信息  JNI_VERSION_1_6

    env->ExceptionDescribe();

//    env->GetStringRegion()

//    env->CallIntMethod()
    /**
     * 获取class对象；
     */
    const char *className = "com/gqy/jnidemo/MainActivity";
    jclass claz = env->FindClass(className);
//    env->GetObjectClass(obj);   //  通过对象实例来获取jclass，相当于Java中的getClass()函数
    jclass superclaz = env->GetSuperclass(claz);   //获取其父类的jclass对象

    /**
     * 获取属性方法
     */
    jmethodID methodId = env->GetMethodID(claz, "onCreate", "(Landroid/os/Bundle;)V");
//    jmethodID staticMethodId = env->GetStaticMethodID(claz, "getInput", "(I)I");
//    env->GetFieldID(obj,)

/**
 * 创建对象
 */
//env->NewObject()

    // 释放资源
    env->ReleaseStringUTFChars(flag, flagStr);
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

//static int jniRegisterNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *gMethods,
//                                    int numMethods);
//
//using namespace std;
//static const char *className = "com/gqy/jnidemo/JniLib";
//
//static void sayHello(JNIEnv *env, jobject, jlong handle) {
////    LOGI("JNI", "native: say hello ###");
//}
//
////native方法的数组  如果是两个native方法，它的size就是2
//static JNINativeMethod gJni_Methods_table[] = {"sayHello", "(J)V", (void *) sayHello};
//
//static int jniRegisterNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *gMethods,
//                                    int numMethods) {
//    jclass claz = NULL;
//    claz = env->FindClass(className);
//    if (claz == NULL) {
//        return -1;
//    }
//    int result = 0;
//    if (env->RegisterNatives(claz, gMethods, numMethods) < 0) {
//        result = -1;
//    }
//    env->DeleteLocalRef(claz);
//    return result;
//}
//
//#ifdef  __cplusplus
//extern "C" {
//#endif
//
//jint JNI_OnLoad(JavaVM *vm, void *reserved) {
//    JNIEnv *env = NULL;
//    jint result = -1;
//    // 获取JNIEnv结构体指针
//    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
//        return result;
//    }
//    jniRegisterNativeMethods(env, className, gJni_Methods_table, sizeof(gJni_Methods_table));
//    return JNI_VERSION_1_4;
//}
//#ifdef  __cplusplus
//}
//#endif
