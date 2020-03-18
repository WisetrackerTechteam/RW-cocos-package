#include "Dop.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)


#include <jni.h>
#include <android/log.h>
#include "platform/android/jni/JniHelper.h"



#define  LOG_TAG    "[wisetracker]"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  DOP_CLASS_NAME "com/sdk/wisetracker/cocos/CocosHelper"

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "DOTInterface.h"
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

	static bool getStaticMethodInfo(JniMethodInfo &methodInfo, const char *methodName, const char *methodSignature) {
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
        methodInfo.env = pEnv;
        methodInfo.classId = classId;
        methodInfo.methodId = methodId;
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

	static void callStaticMethodWithStringParam(const char*methodName, std::string param) {
		JniMethodInfo methodInfo;
		if (!getStaticMethodInfo(methodInfo, methodName, "(Ljava/lang/String;)V")) {
			return;
		}
		jstring paramName = methodInfo.env->NewStringUTF(param.c_str());
		methodInfo.env->CallStaticVoidMethod(methodInfo.classId, methodInfo.methodId, paramName);
		methodInfo.env->DeleteLocalRef(paramName);
		methodInfo.env->DeleteLocalRef(methodInfo.classId);
	}

	static void callStaticMethodWithStringStringStringParam(const char*methodName, const char* param1, const char* param2, std::string param3) {
		JniMethodInfo methodInfo;
		if (!getStaticMethodInfo(methodInfo, methodName, "(Ljava/lang/String;)V")) {
			return;
		}
		jstring paramName1 = methodInfo.env->NewStringUTF(param1);
		jstring paramName2 = methodInfo.env->NewStringUTF(param2);
		jstring paramName3 = methodInfo.env->NewStringUTF(param3.c_str());
		methodInfo.env->CallStaticVoidMethod(methodInfo.classId, methodInfo.methodId, paramName1, paramName2, paramName3);
		methodInfo.env->DeleteLocalRef(paramName1);
		methodInfo.env->DeleteLocalRef(paramName2);
		methodInfo.env->DeleteLocalRef(paramName3);
		methodInfo.env->DeleteLocalRef(methodInfo.classId);
	}

} // extern "C"

void DOT::setUser(std::string userJson) {
	callStaticMethodWithStringParam("setUser", userJson);
}

void DOT::setUserLogout() {
	callStaticMethod("setUserLogout");
}

// DOT
void DOT::onPlayStart() {
	callStaticMethod("onPlayStart");
}

void DOT::onPlayStart(int period) {
	callStaticMethodWithIntParam("onPlayStart", period);
}

void DOT::onPlayStop() {
	callStaticMethod("onPlayStop");
}

void DOT::onStartPage() {
	callStaticMethod("onStartPage");
}

void DOT::onStopPage() {
	callStaticMethod("onStopPage");
}

void DOT::logScreen(std::string pageJson) {
	callStaticMethodWithStringParam("logScreen", pageJson);
}

void DOT::logPurchase(std::string purchaseJson) {
	callStaticMethodWithStringParam("logPurchase", purchaseJson);
}

void DOT::logEvent(std::string eventJson) {
	callStaticMethodWithStringParam("logEvent", eventJson);
}

void DOT::logClick(std::string clickJson) {
	callStaticMethodWithStringParam("logClick", clickJson);
}

// DOX
void DOX::groupIdentify(char* key, char* value, std::string xIdentifyJson) {
	callStaticMethodWithStringStringStringParam("groupIdentify", key, value, xIdentifyJson);
}

void DOX::userIdentify(std::string xIdentifyJson) {
	callStaticMethodWithStringParam("userIdentify", xIdentifyJson);
}

void DOX::logXEvent(std::string xEventJson) {
	callStaticMethodWithStringParam("logXEvent", xEventJson);
}

void DOX::logXConversion(std::string xConversionJson) {
	callStaticMethodWithStringParam("logXConversion", xConversionJson);
}

void DOX::logXPurchase(std::string xPurchaseJson) {
	callStaticMethodWithStringParam("logXPurchase", xPurchaseJson);
}

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

extern "C" { // -- we define our external method to be in C.
    void DOTBridge::initialization() {
        DOTInterface::initialization();
    }

    void DOTBridge::setUser(std::string userJson) {
        DOTInterface::setUser(userJson.c_str());
    }

    void DOTBridge::setUserLogout() {
        DOTInterface::setUserLogout();
    }

    void DOTBridge::onPlayStart() {
        DOTInterface::onPlayStart();
    }

    void DOTBridge::onPlayStart(int period) {
        DOTInterface::onPlayStartWith(period);
    }

    void DOTBridge::onPlayStop() {
        DOTInterface::onPlayStop();
    }

    void DOTBridge::onStartPage() {
        DOTInterface::onStartPage();
    }

    void DOTBridge::onStopPage() {
        DOTInterface::onStopPage();
    }

    void DOTBridge::logScreen(std::string screenJson) {
        DOTInterface::logScreen(screenJson.c_str());
    }

    void DOTBridge::logPurchase(std::string purchaseJson) {
        DOTInterface::logPurchase(purchaseJson.c_str());
    }

    void DOTBridge::logEvent(std::string eventJson) {
        DOTInterface::logEvent(eventJson.c_str());
    }

    void DOTBridge::logClick(std::string clickJson) {
        DOTInterface::logClick(clickJson.c_str());
    }

    void DOXBridge::groupIdentify(char* key, char* value, std::string xIdentifyString) {}
    void DOXBridge::userIdentify(std::string xIdentifyString) {}
    void DOXBridge::logXEvent(std::string xEventString) {}
    void DOXBridge::logXConversion(std::string xConversionStirng) {}
    void DOXBridge::logXPurchase(std::string xPurchaseString) {}

}

#else

void DOT::setUser(std::string userJson) {}
void DOT::setUserLogout() {}
void DOT::onPlayStart() {}
void DOT::onPlayStart(int period) {}
void DOT::onPlayStop() {}
void DOT::onStartPage() {}
void DOT::onStopPage() {}
void DOT::logScreen(std::string screenJson) {}
void DOT::logPurchase(std::string purchaseJson) {}
void DOT::logEvent(std::string eventJson) {}
void DOT::logClick(std::string clickJson) {}
void DOX::groupIdentify(char* key, char* value, std::string xIdentifyString) {}
void DOX::userIdentify(std::string xIdentifyString) {}
void DOX::logXEvent(std::string xEventString) {}
void DOX::logXConversion(std::string xConversionStirng) {}
void DOX::logXPurchase(std::string xPurchaseString) {}

#endif

