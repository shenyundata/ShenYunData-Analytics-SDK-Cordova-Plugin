//
//  ShenYunCordova
//  Created by Summer on 16/05/19.
//
//

#import "ShenYunDataPlugin.h"
#import "ShenYun_StatisticsSDK.h"


@implementation ShenYunDataPlugin


- (void)setDevMode:(CDVInvokedUrlCommand*)command {
    
    NSNumber * isDev = [command.arguments objectAtIndex:0];
    if (isDev == [NSNumber numberWithBool:YES]) {
        [ShenYun_StatisticsSDK setDevMode:YES];
    } else {
        [ShenYun_StatisticsSDK setDevMode:NO];
    }
    
}
- (void)init:(CDVInvokedUrlCommand*)command {
    NSString *appKey = [command.arguments objectAtIndex:0];
    if (appKey == nil || [appKey isKindOfClass:[NSNull class]]) {
        return;
    }
    NSString *channelId = [command.arguments objectAtIndex:1];
    if ([channelId isKindOfClass:[NSNull class]]) {
        channelId = nil;
    }
    NSString *subChannelId = [command.arguments objectAtIndex:2];
    [ShenYun_StatisticsSDK startWithAppKey:appKey channel:channelId subChannel:subChannelId];

}
- (void)onPageStart:(CDVInvokedUrlCommand *)command {
    NSString *pageName = [command.arguments objectAtIndex:0];
    if (pageName == nil || [pageName isKindOfClass:[NSNull class]]) {
        return;
    }
    
    [ShenYun_StatisticsSDK beginLogPageView:pageName];
}

- (void)onPageEnd:(CDVInvokedUrlCommand *)command {
    
    NSString *pageName = [command.arguments objectAtIndex:0];
    if (pageName == nil || [pageName isKindOfClass:[NSNull class]]) {
        return;
    }
    [ShenYun_StatisticsSDK endLogPageView:pageName];
}

- (void)onEvent:(CDVInvokedUrlCommand *)command {
    [self.commandDelegate runInBackground:^{
        NSString *userId = [command.arguments objectAtIndex:0];
        if ([userId isKindOfClass:[NSNull class]]) {
            userId = nil;
        }
        NSString *eventAction = [command.arguments objectAtIndex:1];
        if (eventAction == nil||[eventAction isKindOfClass:[NSNull class]]) {
            return;
        }
        ShenYun_EventStatus eventStatus = (ShenYun_EventStatus)[self toEventActionStatus:[command.arguments objectAtIndex:2]];
        NSDictionary *parameters = nil;
        NSString *parametersJson = [command.arguments objectAtIndex:3];
        if (![parametersJson isKindOfClass:[NSNull class]]) {
            parameters = [self jsonToDictionary:parametersJson];
        }
        [ShenYun_StatisticsSDK customEventWithUserId:userId customEventAction:eventAction eventStatus:eventStatus parameter:parameters success:^(id responseObject) {
            
        } failure:^(NSError *error) {
            
        }];
   
    }];
}

// helper
- (NSDictionary *)jsonToDictionary:(NSString *)jsonStr {
    if (jsonStr) {
        NSError* error = nil;
        id object = [NSJSONSerialization JSONObjectWithData:[jsonStr dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:&error];
        if (error == nil && [object isKindOfClass:[NSDictionary class]]) {
            return object;
        }
    }
    
    return nil;
}

- (ShenYun_EventAction) toEventActionId:(NSString *)key {
    
    NSDictionary *actionDict = @{
                                @"ACTION_REGISTER":@(ACTION_REGISTER),
                                @"ACTION_LOGIN":@(ACTION_LOGIN),
                                @"ACTION_AUTHENTICATE":@(ACTION_AUTHENTICATE),
                                @"ACTION_BIND_CARD":@(ACTION_BIND_CARD),
                                @"ACTION_PLACE_ORDER":@(ACTION_PLACE_ORDER),
                                @"ACTION_PAY":@(ACTION_PAY),
                                @"ACTION_COLLECT":@(ACTION_COLLECT),
                                @"ACTION_CANCEL_COLLECT":@(ACTION_CANCEL_COLLECT),
                                @"ACTION_DELETE":@(ACTION_DELETE),
                                @"ACTION_SHARE":@(ACTION_SHARE),
                                @"ACTION_ADS_SHOW":@(ACTION_ADS_SHOW),
                                @"ACTION_ADS_CLICK":@(ACTION_ADS_CLICK),
                                @"ACTION_ADS_CLOSE":@(ACTION_ADS_CLOSE),
                                @"ACTION_PAGE_SHOW":@(ACTION_PAGE_SHOW),
                                @"ACTION_SHOW_DETAIL":@(ACTION_SHOW_DETAIL),
                                @"ACTION_LOGOUT":@(ACTION_LOGOUT),
                                @"FORGET_PWD":@(FORGET_PWD),
                                @"RESET_PWD":@(RESET_PWD)
                                };
    
    return (ShenYun_EventAction)[[actionDict objectForKey:key] integerValue];;
}

- (ShenYun_EventStatus) toEventActionStatus:(NSString *)key {

    NSDictionary *statusDict = @{
                                @"click":@(STATUS_CLICK),
                                @"success":@(STATUS_SUCCESS),
                                @"fail":@(STATUS_FAIL)
                                };
    if ([statusDict objectForKey:key]) {
        return (ShenYun_EventStatus)[[statusDict objectForKey:key] integerValue];
    }
    return STATUS_SUCCESS;
}

@end
