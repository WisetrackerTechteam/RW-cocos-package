//
//  DOTInterface.h
//  SimpleGame
//
//  Created by Woncheol Heo on 2020/04/13.
//

#ifndef DOTInterface_h
#define DOTInterface_h

#include <stddef.h>

class DOTInterface
{
public:
    static void initialization();
    static void setUser(std::string userJson);
    static void setUserLogout();
    static void onStartPage();
    static void onStopPage();
    static void onPlayStart(int period);
    static void onPlayStop();
    static void logScreen(std::string screenJson);
    static void logPurchase(std::string purchaseJson);
    static void logEvent(std::string eventJson);
    static void logClick(std::string clickJson);
};
#endif /* DOTInterface_h */
