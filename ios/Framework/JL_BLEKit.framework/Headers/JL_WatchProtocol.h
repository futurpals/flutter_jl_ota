//
//  JL_WatchProtocolDelegate.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/8/11.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_SDM_Header.h"


NS_ASSUME_NONNULL_BEGIN

@protocol JL_WatchProtocol <NSObject>

@optional
-(void)jlWatchHeartRate:(JL_SDM_HeartRate *)heartRate;

-(void)jlWatchAirPressure:(JL_SDM_AirPressure *)airPressure;

-(void)jlWatchAltitude:(JL_SDM_Altitude *)alititude;

-(void)jlWatchMoveSteps:(JL_SDM_MoveSteps *)moveStep;

-(void)jlWatchStress:(JL_SDM_Stress *)stress;

-(void)jlWatchOxsaturation:(JL_SDM_OxSaturation*)oxStaturation;

-(void)jlWatchTrainLoad:(JL_SDM_TrainLoad *)trainLoad;

-(void)jlWatchMaxOxg:(JL_SDM_MaxOxg *)maxOxg;

-(void)jlWatchRecTime:(JL_SDM_RecTime *)rectime;

-(void)jlWatchSportMessage:(JL_SDM_SportMessage *)sportMsg;


-(void)jlWatchUnDefineData:(NSData *)value subMask:(NSData *)submask Type:(UInt8)type;

-(void)jlWatchWatchLog:(JL_WATCH_LOG_TYPE) type with:(NSData *)data;


/// @param models JLwSettingModels
-(void)jlWatchSetAllFunc:(NSArray<JLwSettingModel *> *)models;

-(void)jlWatchSetSensorFunc:(JLSensorFuncModel *)model;

-(void)jlWatchSetSedentaryRmd:(JLSedentaryRmdModel *)model;

-(void)jlWatchSetConsequentHeartRate:(JLConsequentHeartRateModel *)model;

-(void)jlWatchSetExerciseHeartRateRemind:(JLExerciseHeartRateRemindModel *)model;

-(void)jlWatchSetAutoPressure:(JLAutoPressureModel *)model;

-(void)jlWatchSetSleepMonitor:(JLSleepMonitorModel *)model;

-(void)jlWatchSetFallDetectionModel:(JLFallDetectionModel *)model;

-(void)jlWatchSetWristLiftDetectionModel:(JLWristLiftDetectionModel *)model;

-(void)jlWatchSetPersonInfoModel:(JLPersonInfoModel *)model;

-(void)jlWatchSetDisconnectRemindModel:(JLDisconnectRemindModel *)model;

-(void)jlWatchSetEmergencyContactModel:(JLEmergencyContactModel *)model;

-(void)jlWatchSetOxygenSturationRemindModel:(JLOxygenSturationRemindModel *)model;

@end

NS_ASSUME_NONNULL_END
