//
//  TrackerAdvance.h
//  DOT
//
//  Created by Woncheol Heo on 2019. 3. 28..
//  Copyright © 2019년 wisetracker. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DOTSession/DOTSession.h>
#import <DOTSession/Tracker.h>
#import "Conversion.h"
#import "RevenueJson.h"
#import "Purchase.h"
#import "Click.h"
#import "Page.h"
#import "ClickJson.h"
#import "RevenueJson.h"
#import "GoalJson.h"
#import "PagesJson.h"
#import "Push.h"
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000
#define IOS10PLUS 1
#import <UserNotifications/UserNotifications.h>
#endif
NS_ASSUME_NONNULL_BEGIN
@interface TrackerAdvance : NSObject

@property (nonatomic) GoalJson *goalJson;
@property (nonatomic) RevenueJson *revenueJson;
@property (nonatomic) ClickJson *clickJson;
@property (nonatomic) PagesJson *pagesJson;

@property (nonatomic) NSMutableDictionary *pageDict;
@property (nonatomic) BOOL pageDictYN;
@property (nonatomic) NSInteger pageSequence;

+ (TrackerAdvance *)sharedInstance;
- (void)onStartPage;
- (double)onStopPage;
- (void)setGoalJosnWithConversion:(Conversion *)conversion;
- (void)setRevenueJsonWithPurchase:(Purchase *)purchase;
- (void)setClickJsonWithClick:(Click *)click;
- (void)setPagesJsonWithPage:(Page *)page;

- (BOOL)sendTransaction;
- (BOOL)sendTransactionByPage;
- (BOOL)checkPurchase;
- (void)updateBeforePurchase;
- (void)updateAfterPurchase;

- (void)enterForeground;
- (void)enterBackground;

- (void)setPushClick:(NSDictionary *)userInfo;
- (void)injectJSinWebview:(UIWebView *)webView;
- (void)injectJSInWkWebView:(WKWebView *)wkWebView;

//WebTracker 호출함수
- (BOOL)getDOTInitFlag;
- (BOOL)checkNewSession;
- (void)occurNewSessionWithType:(NSInteger)type;
- (void)createSessionJson;
- (void)createClickJson;
- (void)createGoalJson;
- (void)createRevenueJson;
- (void)createPagesJson;
- (void)createEntireJson;
- (void)createEntireJson2;
- (void)sendTransactionByNewRWWithPageYN:(BOOL)pageYN;
- (void)setUser:(User *)user;

//RW New API
- (void)logEvent:(NSMutableDictionary *)event;
- (void)logClick:(NSMutableDictionary *)click;
- (void)logPurchase:(NSMutableDictionary *)purchase;
- (void)logScreen:(NSMutableDictionary *)screen;

// iOS 10 only
// Notification Service Extension
#ifdef IOS10PLUS
- (UNMutableNotificationContent*)didReceiveNotificationExtensionRequest:(UNNotificationRequest*)request withContent:(UNMutableNotificationContent*)replacementContent;
- (UNMutableNotificationContent*)serviceExtensionTimeWillExpireRequest:(UNNotificationRequest*)request withContent:(UNMutableNotificationContent*)replacementContent;
#endif
@end


NS_ASSUME_NONNULL_END
