//
//  DOTInterface.m
//  SimpleGame-mobile
//
//  Created by Woncheol Heo on 2020/04/13.
//


#import "DOT.h"
#import "DOTInterface.h"
#import "User.h"
void DOTInterface::initialization() {
    [DOT initialization:nil application:nil];
}

void DOTInterface::setUser(std::string userJson) {
    NSString *userString = [NSString stringWithCString:userJson.c_str() encoding:NSUTF8StringEncoding];
    NSData *jsonData = [userString dataUsingEncoding:NSUTF8StringEncoding];
    NSError *error;
    NSMutableDictionary *userDict = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:&error];
    
    User *user = [[User alloc] init];
    user.age = [userDict objectForKey:@"ag"];
    user.gender = [userDict objectForKey:@"sx"];
    user.attribute1 = [userDict objectForKey:@"ut1"];
    user.attribute2 = [userDict objectForKey:@"ut2"];
    user.attribute3 = [userDict objectForKey:@"ut3"];
    user.attribute4 = [userDict objectForKey:@"ut4"];
    user.attribute5 = [userDict objectForKey:@"ut5"];
    user.member = [userDict objectForKey:@"mbr"];
    user.memberGrade = [userDict objectForKey:@"mbl"];
    user.memberId = [userDict objectForKey:@"mbid"];
    user.isLogin = @"true";
    
    [DOT setUser:user];
}

void DOTInterface::setUserLogout() {
    [DOT setUserLogout];
}

void DOTInterface::onStartPage() {
    [DOT onStartPage];
}

void DOTInterface::onStopPage() {
    [DOT onStopPage];
}

void DOTInterface::onPlayStart(int period) {
  
}

void DOTInterface::onPlayStop() {
}

void DOTInterface::logScreen(std::string screenJson) {
    NSString *pageString = [NSString stringWithCString:screenJson.c_str() encoding:NSUTF8StringEncoding];
    NSData *jsonData = [pageString dataUsingEncoding:NSUTF8StringEncoding];
    NSError *error;
    NSMutableDictionary *pageDict = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:&error];
    
    [DOT logScreen:pageDict];
}

void DOTInterface::logClick(std::string clickJson) {
    NSString *clickString = [NSString stringWithCString:clickJson.c_str() encoding:NSUTF8StringEncoding];
    NSData *jsonData = [clickString dataUsingEncoding:NSUTF8StringEncoding];
    NSError *error;
    NSMutableDictionary *clickDict = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:&error];
    
    [DOT logClick:clickDict];
}

void DOTInterface::logEvent(std::string eventJson) {
    NSString *eventString = [NSString stringWithCString:eventJson.c_str() encoding:NSUTF8StringEncoding];
    NSData *jsonData = [eventString dataUsingEncoding:NSUTF8StringEncoding];
    NSError *error;
    NSMutableDictionary *eventDict = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:&error];
    
    [DOT logEvent:eventDict];
}

void DOTInterface::logPurchase(std::string purchaseJson) {
    NSString *purchaseString = [NSString stringWithCString:purchaseJson.c_str() encoding:NSUTF8StringEncoding];
    NSData *jsonData = [purchaseString dataUsingEncoding:NSUTF8StringEncoding];
    NSError *error;
    NSMutableDictionary *purchaseDict = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:&error];
    
    [DOT logPurchase:purchaseDict];
}

