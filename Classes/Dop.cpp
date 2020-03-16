#include "dop.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include <android/log.h>
#include "platform/android/jni/JniHelper.h"

#define  LOG_TAG    "[wisetracker]"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  DOP_CLASS_NAME "com/sdk/wisetracker/cocos/CocosHelper"

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)


#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

typedef struct JniMethodInfo_
{
    JNIEnv *    env;
    jclass      classId;
    jmethodID   methodId;
} JniMethodInfo;

extern "C"
{
	static JNIEnv* getJNIEnv(void) {
		JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
		if (NULL == jvm) {
			LOGD("Failed to get JNIEnv. JniHelper::getJavaVM() is NULL");
			return NULL;
		}

		JNIEnv *env = NULL;
		// get jni environment
		jint ret = jvm->GetEnv((void**)&env, JNI_VERSION_1_4);

		switch (ret) {
			case JNI_OK :
				// Success!
				return env;

			case JNI_EDETACHED :
				// Thread not attached
				// TODO : If calling AttachCurrentThread() on a native thread
				// must call DetachCurrentThread() in future.
				// see: http://developer.android.com/guide/practices/design/jni.html
				if (jvm->AttachCurrentThread(&env, NULL) < 0)
				{
					LOGD("Failed to get the environment using AttachCurrentThread()");
					return NULL;
				} else {
					// Success : Attached and obtained JNIEnv!
					return env;
				}

			case JNI_EVERSION :
				// Cannot recover from this error
				LOGD("JNI interface version 1.4 not supported");
			
			default :
				LOGD("Failed to get the environment using GetEnv()");
				return NULL;
		}
	}

	static bool getStaticMethodInfo(JniMethodInfo &methodinfo, const char *methodName, const char *methodSignature) {
		JNIEnv *pEnv = getJNIEnv();
	    if (!pEnv) {
	        return false;
	    }
	    jclass classId = pEnv->FindClass(DOP_CLASS_NAME);
		if (!classId) {
			LOGD("Failed to find class of %s", DOP_CLASS_NAME);
			return false;
		}
		jmethodID methodId = pEnv->GetStaticMethodID(classId, methodName, methodSignature);
		if (!methodId) {
			LOGD("Failed to find static method id of %s", methodName);
			pEnv->DeleteLocalRef(classId);
			return false;
		}
		methodinfo.env = pEnv;
		methodinfo.classId = classId;
		methodinfo.methodId = methodId;
		return true;
	}

	static void callStaticMethod(const char*methodName) {
		JniMethodInfo methodInfo;
		if (!getStaticMethodInfo(methodInfo, methodName, "()V")) {
			return;
		}
		methodInfo.env->CallStaticVoidMethod(methodInfo.classId, methodInfo.methodId);
		methodInfo.env->DeleteLocalRef(methodInfo.classId);
	}

	static void callStaticMethodWithIntParam(const char*methodName, int param) {
		JniMethodInfo methodInfo;
		if (!getStaticMethodInfo(methodInfo, methodName, "(I)V")) {
			return;
		}
		methodInfo.env->CallStaticVoidMethod(methodInfo.classId, methodInfo.methodId, param);
		methodInfo.env->DeleteLocalRef(methodInfo.classId);
	}

	static void callStaticMethodWithStringParam(const char*methodName, const char* param) {
		JniMethodInfo methodInfo;
		if (!getStaticMethodInfo(methodInfo, methodName, "(Ljava/lang/String;)V")) {
			return;
		}
		jstring paramName = methodInfo.env->NewStringUTF(param);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classId, methodInfo.methodId, paramName);
		methodInfo.env->DeleteLocalRef(paramName);
		methodInfo.env->DeleteLocalRef(methodInfo.classId);
	}

	static void callStaticMethodWithStringStringStringParam(const char*methodName, const char* param1, const char* param2, const char* param3) {
		JniMethodInfo methodInfo;
		if (!getStaticMethodInfo(methodInfo, methodName, "(Ljava/lang/String;)V")) {
			return;
		}
		jstring paramName1 = methodInfo.env->NewStringUTF(param1);
		jstring paramName2 = methodInfo.env->NewStringUTF(param2);
		jstring paramName3 = methodInfo.env->NewStringUTF(param3);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classId, methodInfo.methodId, paramName1, paramName2, paramName3);
		methodInfo.env->DeleteLocalRef(paramName1);
		methodInfo.env->DeleteLocalRef(paramName2);
		methodInfo.env->DeleteLocalRef(paramName3);
		methodInfo.env->DeleteLocalRef(methodInfo.classId);
	}

} // extern "C"

void CocosHelper::setUser(char* userString) {
	callStaticMethodWithStringParam("setUser", userString);
}

void CocosHelper::setUserLogout() {
	callStaticMethod("setUserLogout");
}

// DOT
void CocosHelper::onPlayStart() {
	callStaticMethod("onPlayStart");
}

void CocosHelper::onPlayStart(int period) {
	callStaticMethodWithIntParam("onPlayStart", period);
}

void CocosHelper::onPlayStop() {
	callStaticMethod("onPlayStop");
}

void CocosHelper::onStartPage() {
	callStaticMethod("onStartPage");
}

void CocosHelper::onStopPage() {
	callStaticMethod("onStopPage");
}

void CocosHelper::logScreen(char* userString) {
	callStaticMethodWithStringParam("logScreen", userString);
}

void CocosHelper::logPurchase(char* purchaseString) {
	callStaticMethodWithStringParam("logPurchase", purchaseString);
}

void CocosHelper::logEvent(char* eventString) {
	callStaticMethodWithStringParam("logEvent", eventString);
}

void CocosHelper::logClick(char* clickString) {
	callStaticMethodWithStringParam("logClick", clickString);
}

// DOX
void CocosHelper::groupIdentify(char* key, char* value, char* xIdentifyString) {
	callStaticMethodWithStringStringStringParam("groupIdentify", key, value, xIdentifyString);
}

void CocosHelper::userIdentify(char* xIdentifyString) {
	callStaticMethodWithStringParam("userIdentify", xIdentifyString);
}

void CocosHelper::logXEvent(char* xEventString) {
	callStaticMethodWithStringParam("logXEvent", xEventString);
}

void CocosHelper::logXConversion(char* xConversionStirng) {
	callStaticMethodWithStringParam("logXConversion", xConversionStirng);
}

void CocosHelper::logXPurchase(char* xPurchaseString) {
	callStaticMethodWithStringParam("logXPurchase", xPurchaseString);
}

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)


#else

void CocosHelper::setUser(char* userString) {}
void CocosHelper::setUserLogout() {}
// DOT
void CocosHelper::onPlayStart() {}
void CocosHelper::onPlayStart(int period) {}
void CocosHelper::onPlayStop() {}
void CocosHelper::onStartPage() {}
void CocosHelper::onStopPage() {}
void CocosHelper::logScreen(char* userString) {}
void CocosHelper::logPurchase(char* purchaseString) {}
void CocosHelper::logEvent(char* eventString) {}
void CocosHelper::logClick(char* clickString) {}
// DOX
void CocosHelper::groupIdentify(char* key, char* value, char* xIdentifyString) {}
void CocosHelper::userIdentify(char* xIdentifyString) {}
void CocosHelper::logXEvent(char* xEventString) {}
void CocosHelper::logXConversion(char* xConversionStirng) {}
void CocosHelper::logXPurchase(char* xPurchaseString) {}


#endif

