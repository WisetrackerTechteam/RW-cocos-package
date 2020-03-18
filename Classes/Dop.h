#ifndef __DOP_H__
#define __DOP_H__

#include <json/json.h>
#include "cocos2d.h"

class DOT {
public:
static void initialization();
static void setUser(std::string userJson);
static void setUserLogout();
static void onPlayStart();
static void onPlayStart(int period);
static void onPlayStop();
static void onStartPage();
static void onStopPage();
static void logScreen(std::string pageJson);
static void logPurchase(std::string purchaseJson);
static void logEvent(std::string eventJson);
static void logClick(std::string clickJson);
};

class User {
private:
Json::Value user;
public:
    void SetMember(std::string member) {
        user["mbr"] = member;
    }
    void SetMemberGrade(std::string memberGrade) {
        user["mbl"] = memberGrade;
    }
    void SetMemberId(std::string memberId) {
        user["mbid"] = memberId;
    }
    void SetGender(std::string gender) {
        user["sx"] = gender;
    }
    void SetAge(std::string age) {
        user["ag"] = age;
    }
    void SetAttr1(std::string attr1) {
        user["ut1"] = attr1;
    }
    void SetAttr2(std::string attr2) {
        user["ut2"] = attr2;
    }
    void SetAttr3(std::string attr3) {
        user["ut3"] = attr3;
    }
    void SetAttr4(std::string attr4) {
        user["ut4"] = attr4;
    }
    void SetAttr5(std::string attr5) {
        user["ut5"] = attr5;
    }
    std::string GetJson() {
        user["isLogin"] = true;
        Json::StreamWriterBuilder builder;
        std::string jsonStr = Json::writeString(builder, user);
        return jsonStr;
    }
};

class DOX {
public:
    static void groupIdentify(char* key, char* value, std::string xIdentifyJson);
    static void userIdentify(std::string xIdentifyJson);
    static void logXEvent(std::string xEventJson);
    static void logXConversion(std::string xConversionJson);
    static void logXPurchase(std::string xPurchaseJson);
};

#endif // __DOP_H__
