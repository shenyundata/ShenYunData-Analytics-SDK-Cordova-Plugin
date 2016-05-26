//
//  ShenYunCordova
//  Created by Summer on 16/05/19.
//
//
#import <Foundation/Foundation.h>
#import <Cordova/CDV.h>

@interface ShenYunDataPlugin : CDVPlugin

- (void)setDevMode:(CDVInvokedUrlCommand*)command;
- (void)init:(CDVInvokedUrlCommand*)command;
- (void)onPageStart:(CDVInvokedUrlCommand*)command;
- (void)onPageEnd:(CDVInvokedUrlCommand*)command;
- (void)onEvent:(CDVInvokedUrlCommand*)command;
@end
