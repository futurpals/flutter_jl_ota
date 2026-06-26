//
//  JLWearSyncRealTimeModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/27.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JLWatchEnum.h"

NS_ASSUME_NONNULL_BEGIN


@interface JLWearSyncRealTimeData : NSObject

@property(nonatomic,strong)NSData *basicData;

@end

@interface JLWearSyncRealTimeModel : JLWearSyncRealTimeData

@property(nonatomic,assign)UInt8 type;

@property(nonatomic,assign)UInt32 sportStep;

@property(nonatomic,assign)UInt16 distance;

@property(nonatomic,assign)UInt32 exerciseTime;

@property(nonatomic,assign)UInt16 speed;

@property(nonatomic,assign)UInt16 calories;

@property(nonatomic,assign)UInt16 cadence;

@property(nonatomic,assign)UInt16 stride;

@property(nonatomic,assign)WatchExerciseIntensityType statusType;

@property(nonatomic,assign)UInt8 heartRate;

+(JLWearSyncRealTimeModel *)initWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
