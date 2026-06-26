//
//  JLWearable.h
//  Test
//
//  Created by EzioChan on 2021/4/6.
//  Copyright © 2021 Zhuhai Jieli Technology Co.,Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_RCSP.h"
#import "JL_EntityM.h"
#import "JL_SDM_Header.h"
#import "JL_WatchProtocol.h"
#import "JLWearSync.h"
#import "JLWearSyncCustom.h"

NS_ASSUME_NONNULL_BEGIN

#define JL_RECIVED_DATA     @"JL_RECIVED_DATA"


@interface JLWearable : NSObject

@property(nonatomic,assign,readonly)uint8_t version;
@property(nonatomic,strong)JL_CB_HeartRate      heartRate;
@property(nonatomic,strong)JL_CB_AirPressure    airPressure;
@property(nonatomic,strong)JL_CB_Altitude       alititude;
@property(nonatomic,strong)JL_CB_MoveSteps      moveStep;
@property(nonatomic,strong)JL_CB_Stress         stress;
@property(nonatomic,strong)JL_CB_Oxsaturation   oxStaturation;
@property(nonatomic,strong)JL_CB_TrainLoad      trainLoad;
@property(nonatomic,strong)JL_CB_MaxOxg         maxOxg;
@property(nonatomic,strong)JL_CB_RecTime        rectime;
@property(nonatomic,strong)JL_CB_SportMsg       sportMsg;
@property(nonatomic,strong)JL_CB_WatchLog       logMsg;
@property(nonatomic,strong,readonly)JL_EntityM* responseEntity;

+(instancetype)sharedInstance;

-(void)w_addDelegate:(id<JL_WatchProtocol>)delegate;

-(void)w_removeDelegate:(id<JL_WatchProtocol>)delegate;

-(void)w_removeAll;

/**
 JLWearable *w = [JLWearable sharedInstance];
 NSMutableArray *array = [NSMutableArray new];
 [array addObject:[JL_SDM_HeartRate requireRealTime:YES Resting:YES Max:YES]];
 [array addObject:[JL_SDM_Altitude requireRealTime:YES min:NO Max:NO]];
 [array addObject:[JL_SDM_MoveSteps require]];
 w.heartRate = ^(JL_SDM_HeartRate *heartRate) {
 };
 w.alititude = ^(JL_SDM_Altitude *altitude) {
 };
 JL_EntityM *entity = [[JL_EntityM alloc] init];
 [w requestSportData:array withEntity:entity];
*/
///
-(void)w_requestSportData:(NSMutableArray<JLSportDataModel *>*)reqModels withEntity:(JL_EntityM *)entity;

-(void)pr_requestSportDataMask:(NSData *)data withEntity:(JL_EntityM *)entity opCode:(uint16_t)opcode;


-(void)w_inputPKG:(JL_PKG*)pkg withEntity:(JL_EntityM *)entity;

-(void)w_syncWeather:(JL_MSG_Weather *)weather withEntity:(JL_EntityM *)entity result:(JL_CB_Status)block;


/**
 log
 [[JLWearable shareInstance] w_transportLog:Log_Acceleration | Log_HeartRate_BloodOxy withEntity:entity];
 */
-(void)w_transportLog:(JL_WATCH_LOG_MASK)model withEntity:(JL_EntityM *)entity;



/// -(void)w_addDelegate:(id<JL_WatchProtocol>)delegate;
-(void)w_InquireDeviceFuncWith:(JL_WATCH_SETTING)target withEntity:(JL_EntityM *)entity;

///   NSMutableArray <JLwSettingModel *>* models = [NSMutableArray new];
/// [models addObject:model];
/// JLSedentaryRmdModel *model1 = [[JLSedentaryRmdModel alloc] initWithModel:s_Shake Status:true];
/// [models addObject:model1];
/// JLDisconnectRemindModel *model2 = [[JLDisconnectRemindModel alloc] initWithModel:s_BrightScreen Status:true];
/// [models addObject:model2];
/// [[JLWearable sharedInstance] w_SettingDeviceFuncWith:models withEntity:requestEntity]
/// -(void)w_addDelegate:(id<JL_WatchProtocol>)delegate;
-(void)w_SettingDeviceFuncWith:(NSArray <JLwSettingModel *> *)models withEntity:(JL_EntityM *)entity result:(JL_CB_Status)block;


@end

NS_ASSUME_NONNULL_END
