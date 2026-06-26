//
//  JLWatchEnum.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/8/2.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *_Nonnull const  JL_Watch_HeartRate;
extern NSString *_Nonnull const  JL_Watch_AirPressure;
extern NSString *_Nonnull const  JL_Watch_Altitude;
extern NSString *_Nonnull const  JL_Watch_MoveSteps;
extern NSString *_Nonnull const  JL_Watch_Stress;
extern NSString *_Nonnull const  JL_Watch_Oxsaturation;
extern NSString *_Nonnull const  JL_Watch_MaxOxg;
extern NSString *_Nonnull const  JL_Watch_RecTime;
extern NSString *_Nonnull const  JL_Watch_SportMsg;
extern NSString *_Nonnull const  JL_Watch_WatchLog;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_WATCH_LOG_MASK) {
    JL_WATCH_LOG_MASK_Acceleration = 0x80000000 >> 31,
    JL_WATCH_LOG_MASK_HeartRate_BloodOxy = 0x80000000 >> 30,
};

typedef NS_ENUM(UInt8, JL_WATCH_LOG_TYPE) {
    JL_WATCH_LOG_TYPE_Res_Acceleration = 0x00,
    JL_WATCH_LOG_TYPE_Res_HeartRate_BloodOxy = 0x01,
};

typedef NS_ENUM(UInt8, JL_SRMDataType) {
    JL_SRM_Start = 0x00,
    JL_SRM_Basic = 0x01,
    JL_SRM_Pause = 0x02,
    JL_SRM_Pace = 0x03,
    JL_SRM_End = 0xff,
};

typedef NS_ENUM(UInt8, JL_SportDataType) {
    JL_SportDataTypeHeartRate           = 0,
    JL_SportDataTypeAirPressure         = 1,
    JL_SportDataTypeAltitude            = 2,
    JL_SportDataTypeMovementSteps       = 3,
    JL_SportDataTypeStress              = 4,
    JL_SportDataTypeOxygenSaturation    = 5,
    JL_SportDataTypeTrainingLoad        = 6,
    JL_SportDataTypeMaxOxygenUptake     = 7,
    JL_SportDataTypeRecoveryTime        = 8,
    JL_SportDataTypeSportMessage        = 9,
};

typedef NS_ENUM(UInt8, JL_SportPattern) {
    JL_SportPatternRun          = 0,
    JL_SportPatternClimb        = 1,
    JL_SportPatternSwim         = 2,
};

typedef NS_ENUM(UInt8, JL_SportDataFormat) {
    JL_SportDataFormatBeUint8                 = 1,
    JL_SportDataFormatBeBigendUint16          = 2,
    JL_SportDataFormatBeBigendUint32          = 4,
};

typedef NS_ENUM(UInt8, JL_WATCH_SETTING_MASK) {
    JL_WATCH_SETTING_MASK_READ_INFO         = 0x00,
    JL_WATCH_SETTING_MASK_SET_INFO          = 0x01,
    JL_WATCH_SETTING_MASK_RECIVE_INFO       = 0x02,
};

typedef NS_ENUM(uint32_t, JL_WATCH_SETTING) {
    JL_WATCH_SETTING_SENSOR_FUNC                        = 0x0002,
    JL_WATCH_SETTING_SEDENTARY_REMIND                   = 0x0004,
    JL_WATCH_SETTING_CONTINUOUS_HEARTRATE_MEASUREMENT   = 0x0008,
    JL_WATCH_SETTING_EXERCISE_HEARTRATE_REMINDER        = 0x0010,
    JL_WATCH_SETTING_AUTOMATIC_PRESSURE_DETECTION       = 0x0020,
    JL_WATCH_SETTING_SLEEP_DETECTION                    = 0x0040,
    JL_WATCH_SETTING_FALL_DETECTION                     = 0x0080,
    JL_WATCH_SETTING_LIFTWRIST_DETECTION                = 0x0100,
    JL_WATCH_SETTING_PERSONAL_INFO                      = 0x0200,
    JL_WATCH_SETTING_BLUETOOTH_DISCONECTED_REMINDER     = 0x0400,
    JL_WATCH_SETTING_OXIMETRY                           = 0x0800,
    JL_WATCH_SETTING_EMERGENCY_CONTACT                  = 0x1000,
};

typedef NS_ENUM(uint16_t, JL_SENSOR_FUNC_SWITCH) {
    JL_SENSOR_FUNC_SWITCH_PEDOMETER                     = 0x01,
    JL_SENSOR_FUNC_SWITCH_PEDOMETER_RECORD              = 0x02,
    JL_SENSOR_FUNC_SWITCH_HEARTRATE                     = 0x04,
    JL_SENSOR_FUNC_SWITCH_HEARTRATE_RECORD              = 0x08,
    JL_SENSOR_FUNC_SWITCH_BLOODOXYGEN                   = 0x10,
    JL_SENSOR_FUNC_SWITCH_BLOODOXYGEN_RECORD            = 0x20,
    JL_SENSOR_FUNC_SWITCH_ALTITUDE_AIRPRESSURE          = 0x40,
    JL_SENSOR_FUNC_SWITCH_ALTITUDE_AIRPRESSURE_RECORD   = 0x80,
};

typedef NS_ENUM(UInt8, JL_WearSyncStatus) {
    JL_WearSyncStatus_ReadInfo              = 0x00,
    JL_WearSyncStatus_Start                 = 0x01,
    JL_WearSyncStatus_EndByApp              = 0x02,
    JL_WearSyncStatus_EndByDevice           = 0x03,
    JL_WearSyncStatus_Pause                 = 0x04,
    JL_WearSyncStatus_Continue              = 0x05,
    JL_WearSyncStatus_RealTimeInfoRequire   = 0x06,
};


typedef NS_ENUM(UInt8, WatchSportStatus) {
    WatchSportStatus_Pause  = 0x00,
    WatchSportStatus_Motion = 0x01
};

typedef NS_ENUM(UInt8, WatchHeartRateType) {
    WatchHeartRate_Max  = 0x00,
    WatchHeartRate_Save = 0x01
};
typedef NS_ENUM(UInt8, WatchExerciseIntensityType) {
    WatchExercise_Not    = 0x00,
    WatchExercise_Level1 = 0x01,
    WatchExercise_Level2 = 0x02,
    WatchExercise_Level3 = 0x03,
    WatchExercise_Level4 = 0x04,
    WatchExercise_Level5 = 0x05
};
typedef NS_ENUM(UInt8, WatchSleepType) {
    WatchSleep_WideAwake         = 0xFF,
    WatchSleep_Light             = 0x01,
    WatchSleep_Deep              = 0x02,
    WatchSleep_RapidEyeMovement  = 0x03,
    WatchSleep_SporadicNaps      = 0x04
};


@interface JLWatchEnum : NSObject

/**
 */
+ (JL_SportDataFormat)sportDataFormatFromSportDataType:(JL_SportDataType)sportDataType;

@end

NS_ASSUME_NONNULL_END
