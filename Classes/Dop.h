#ifndef __DOP_H__
#define __DOP_H__

#include "cocos2d.h"

class CocosHelper {
public:
static void setUser(char* userString);
static void setUserLogout();
// DOT
static void onPlayStart();
static void onPlayStart(int period);
static void onPlayStop();
static void onStartPage();
static void onStopPage();
static void logScreen(char* userString);
static void logPurchase(char* purchaseString);
static void logEvent(char* eventString);
static void logClick(char* clickString);
// DOX
static void groupIdentify(char* key, char* value, char* xIdentifyString);
static void userIdentify(char* xIdentifyString);
static void logXEvent(char* xEventString);
static void logXConversion(char* xConversionStirng);
static void logXPurchase(char* xPurchaseString);
};

#endif // __DOP_H__
