//
//  ShenYun.h
//  ShenYun
//
//  15/7/6.
//  Copyright (c) 2015年 ShenYun. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void (^ShenYun_SuccessBlock)(id responseObject);
typedef void (^ShenYun_FailureBlock)(NSError *error);

///---------------------------------------------------------------------------------------
/// @name  页面事件种类
///---------------------------------------------------------------------------------------

typedef enum ShenYun_EventAction {
    ACTION_REGISTER = 0,
    ACTION_LOGIN,
    ACTION_AUTHENTICATE,
    ACTION_BIND_CARD,
    ACTION_PLACE_ORDER,
    ACTION_PAY,
    ACTION_COLLECT,
    ACTION_CANCEL_COLLECT,
    ACTION_DELETE,
    ACTION_SHARE,
    ACTION_ADS_SHOW,
    ACTION_ADS_CLICK,
    ACTION_ADS_CLOSE,
    ACTION_PAGE_SHOW,
    ACTION_SHOW_DETAIL,
    ACTION_LOGOUT,
    FORGET_PWD,
    RESET_PWD,
} ShenYun_EventAction;

typedef enum ShenYun_EventStatus {
    STATUS_CLICK = 0,
    STATUS_SUCCESS,
    STATUS_FAIL,
} ShenYun_EventStatus;

@interface ShenYun_StatisticsSDK : NSObject

///---------------------------------------------------------------------------------------
/// @name  开启统计
///---------------------------------------------------------------------------------------

/** 初始化统计模块
 @param appKey.
 @param channelId 渠道名称,为nil或@""时, 默认为@"App Store"渠道
 @param subChannel
 @return void
 */
+ (id)startWithAppKey:(NSString *)appkey channel:(NSString *)channel subChannel:(NSString *)subChannel;

/**
 使用方法:默认
 @param isEnable 设置SDK地理位置是否开启，YES为开启，NO为关闭(如无调用,默认为开启)
 @return void
 */
+ (void)lbsLocationEnable:(BOOL)isEnable;

/** 设置SDK工作模式
 @param debug 设置SDK工作模式，YES为测试模式，NO为生产模式(如无调用,默认为生产模式)
 @return void
 */
+ (void)setDevMode:(BOOL)debug;


///---------------------------------------------------------------------------------------
/// @name  页面计时
///---------------------------------------------------------------------------------------

/** 自动页面时长统计, 开始记录某个页面展示时长.
 使用方法：必须配对调用beginLogPageView:和endLogPageView:两个函数来完成自动统计，若只调用某一个函数不会生成有效数据。
 在该页面展示时调用beginLogPageView:，当退出该页面时调用endLogPageView:
 @param pageName 统计的页面名称.
 @return void.
 */
+ (void)beginLogPageView:(NSString *)pageName;

/** 自动页面时长统计, 结束记录某个页面展示时长.
 使用方法：必须配对调用beginLogPageView:和endLogPageView:两个函数来完成自动统计，若只调用某一个函数不会生成有效数据。
 在该页面展示时调用beginLogPageView:，当退出该页面时调用endLogPageView:
 @param pageName 统计的页面名称.
 @return void.
 */
+ (void)endLogPageView:(NSString *)pageName;

///---------------------------------------------------------------------------------------
/// @name
///---------------------------------------------------------------------------------------
/** 事件统计
 @param userId  用户id
 @param action  事件id
 @param status  事件状态
 @param parameter nil为不带参数
 @param success
 @return failure.
 */
+ (void)eventWithUserId:(NSString *)userId eventId:(ShenYun_EventAction)action eventStatus:(ShenYun_EventStatus)status parameter:(NSDictionary *)parameter success:(ShenYun_SuccessBlock)success failure:(ShenYun_FailureBlock)failure;

/** 事件统计--带地理位置及其他基本信息
 @param userId  用户id
 @param action  事件id
 @param status  事件状态
 @param parameter   nil为不带参数
 @param hasLocation  yes为带位置信息
 @param success
 @return failure.
 */
+ (void)eventWithUserId:(NSString *)userId eventId:(ShenYun_EventAction)action eventStatus:(ShenYun_EventStatus)status parameter:(NSDictionary *)parameter hasLocation:(BOOL)enable success:(ShenYun_SuccessBlock)success failure:(ShenYun_FailureBlock)failure;


/** 多事件接口
 @param userId  用户id
 @param events  多事件数组
 @param success
 @param failure
 */
+ (void)eventWithUserId:(NSString *)userId events:(NSArray *)events success:(ShenYun_SuccessBlock)success failure:(ShenYun_FailureBlock)failure;

/** 多事件接口--带地理位置及其他基本信息
 @param userId  用户id
 @param events  多事件数组
 @param hasLocation  yes为带位置信息
 @param success
 @param failure
 */
+ (void)eventWithUserId:(NSString *)userId events:(NSArray *)events hasLocation:(BOOL)enable success:(ShenYun_SuccessBlock)success failure:(ShenYun_FailureBlock)failure;

/** 自定义事件
 @param userId  用户id
 @param customAction   事件id
 @param status  事件状态
 @param parameter  nil为不带参数
 @param success
 @return failure.
 */
+ (void)customEventWithUserId:(NSString *)userId customEventAction:(NSString *)customAction eventStatus:(ShenYun_EventStatus)status parameter:(NSDictionary *)parameter success:(ShenYun_SuccessBlock)success failure:(ShenYun_FailureBlock)failure;

/** 自定义事件--带地理位置及其他基本信息
 @param userId  用户id
 @param customAction   事件id
 @param status  事件状态
 @param parameter  nil为不带参数
 @param hasLocation  yes为带位置信息
 @param success
 @return failure.
 */
+ (void)customEventWithUserId:(NSString *)userId customEventAction:(NSString *)customAction eventStatus:(ShenYun_EventStatus)status parameter:(NSDictionary *)parameter hasLocation:(BOOL)enable success:(ShenYun_SuccessBlock)success failure:(ShenYun_FailureBlock)failure;



@end
