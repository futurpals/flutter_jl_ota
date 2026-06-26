//
//  LtvSettingModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>


typedef NS_ENUM(UInt8, WatchSettingFunc) {
    WatchSettingFunc_SensorFunction = 0x01 ,
    WatchSettingFunc_SedentaryReminder = 0x02,
    WatchSettingFunc_ContinuousHeartRateMeasurement = 0x03,
    WatchSettingFunc_ExerciseHeartRateReminder = 0x04,
    WatchSettingFunc_AutomaticPressureDetection = 0x05,
    WatchSettingFunc_SleepMonitoring = 0x06,
    WatchSettingFunc_FallDetection = 0x07,
    WatchSettingFunc_WristLiftDetection = 0x08,
    WatchSettingFunc_PersonInfo  = 0x09,
    WatchSettingFunc_DisconnectReminder = 0xA,
    WatchSettingFunc_OxygenSturation = 0x0B,
    WatchSettingFunc_EmergencyContact = 0x0C
};

typedef NS_ENUM(UInt8, WatchRemindType) {
    WatchRemind_BrightScreen = 0x00,
    WatchRemind_Shake        = 0x01,
    WatchRemind_Call         = 0x02
};

typedef NS_ENUM(UInt8, WatchConsequentType) {
    WatchConsequent_Intelligent = 0x00,
    WatchConsequent_realTime = 0x01
};

typedef NS_ENUM(UInt8,WatchOxygenMsmType){
    WatchOxygenMsm_Intelligent = 0x00,
    WatchOxygenMsm_runTime = 0x01
};

typedef NS_ENUM(UInt8, WatchSwitchType) {
    WatchSwitchType_Close    = 0x00,
    WatchSwitchType_AllDay   = 0x01,
    WatchSwitchType_Customer = 0x02,
};

@interface WatchTimer : NSObject
@property(nonatomic,assign,readonly)UInt8 hour;
@property(nonatomic,assign,readonly)UInt8 min;

-(instancetype _Nonnull)initWithData:(NSData *_Nonnull)data;

-(instancetype _Nonnull)initWith:(uint8_t)h Min:(uint8_t)m;

@end

NS_ASSUME_NONNULL_BEGIN

@interface JLwSettingModel : NSObject
@property(nonatomic,assign)uint8_t length;
@property(nonatomic,assign)WatchSettingFunc type;
@property(nonatomic,strong)NSData *value;

@property(nonatomic,strong)NSString *deviceID;


-(NSData *)beData;



@end

NS_ASSUME_NONNULL_END
