//
//  JL_AlarmClockManager.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/12/16.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JLModel_AlarmSetting.h>
#import <JL_BLEKit/RTC_RingInfo.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JLModel_RTC.h>
#import <JL_BLEKit/JLModel_Ring.h>
#import <JL_BLEKit/JL_FunctionBaseManager.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_RtcOperate) {
    JL_FlashOperateFlagRead             = 0x00,
    JL_FlashOperateFlagWrite            = 0x01,
};

typedef void(^JL_RTC_ALARM_BK)(NSArray <JLModel_AlarmSetting *>* __nullable array, uint8_t flag);

typedef void(^JL_RTC_GET_ALARM_BK)(NSArray <JLModel_RTC *>* __nullable alarms,NSError * __nullable error);

#pragma mark - Vendor SDK
extern NSString *kJL_MANAGER_RTC_RINGING;

extern NSString *kJL_MANAGER_RTC_RINGSTOP;

extern NSString *kJL_MANAGER_RTC_AUDITION;


@interface JL_AlarmClockManager : JL_FunctionBaseManager

@property (assign,nonatomic) uint8_t             rtcVersion;
@property (assign,nonatomic) JL_RTCAlarmType     rtcAlarmType;
@property (strong,nonatomic) JLModel_RTC         *rtcModel;
@property (strong,nonatomic) NSMutableArray<JLModel_RTC *>      *rtcAlarms;
@property (strong,nonatomic) NSMutableArray<JLModel_Ring *>      *rtcDfRings;


-(void)cmdRtcGetAlarms:(JL_RTC_GET_ALARM_BK)result;


/// - Parameters:
-(void)cmdRtcSetArray:(NSArray<JLModel_RTC *>*)array Result:(JL_CMD_RESPOND __nullable)result;


/// - Parameters:
-(void)cmdRtcDeleteIndexArray:(NSArray<NSNumber *>*)array Result:(JL_CMD_RESPOND __nullable)result;


-(void)cmdRtcStopResult:(JL_CMD_RESPOND __nullable)result;


/// - Parameters:
-(void)cmdRtcAudition:(JLModel_RTC *)rtc Option:(BOOL)option result:(JL_CMD_RESPOND __nullable)result;


-(void)cmdRtcOperate:(JL_RtcOperate)operate
               Index:(uint8_t)index
             Setting:(JLModel_AlarmSetting* __nullable)setting
              Result:(JL_RTC_ALARM_BK __nullable)result;


-(void)parseData:(NSData *)infoData WithLtyType:(uint8_t)ltvVersion;

/// - Parameters:
+(NSMutableArray<JLModel_RTC*> *)makeOutRtc:(NSData*)data RtcType:(uint8_t)rtcType;


+(NSMutableArray<JLModel_Ring*> *)makeOutRtcDefaultRing:(NSData *)data;


@end

NS_ASSUME_NONNULL_END
