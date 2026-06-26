//
//  JL_SDM_HeartBeat.h
//  Test
//
//  Created by EzioChan on 2021/4/6.
//  Copyright © 2021 Zhuhai Jieli Technology Co.,Ltd. All rights reserved.
//
/*
 */
#import "JLSportDataModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface JL_SDM_HeartRate : JLSportDataModel
@property(nonatomic,assign)uint8_t realTime;
@property(nonatomic,assign)uint8_t resting;
@property(nonatomic,assign)uint8_t max;

@property(nonatomic,assign)uint8_t singleRate;

@property(nonatomic,assign)BOOL isSingle;

+(JL_SDM_HeartRate*)responseData:(NSData *)value subMask:(NSData *)submask;

+(JL_SDM_HeartRate*)requireRealTime:(BOOL)rt Resting:(BOOL)rting Max:(BOOL)max;

+(JL_SDM_HeartRate*)requireSingle;



@end

NS_ASSUME_NONNULL_END
