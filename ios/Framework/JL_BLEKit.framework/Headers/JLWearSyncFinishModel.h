//
//  JLWearSyncFinishModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/27.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JLWatchEnum.h"
NS_ASSUME_NONNULL_BEGIN


@interface JLWearSyncFinishDataModel:NSObject

@property(nonatomic,strong)NSData *basicData;

@end


@interface JLWatchExerciseIntens:NSObject

@property(nonatomic,assign)WatchExerciseIntensityType type;

@property(nonatomic,assign)UInt32 duration;

@end

@interface JLWearSyncFinishModel : JLWearSyncFinishDataModel

@property(nonatomic,strong)NSDate *endTime;

@property(nonatomic,strong)NSString *recyleTime;

@property(nonatomic,assign)UInt16 sportId;

@property(nonatomic,assign)UInt16 fileSize;

@property(nonatomic,strong)NSArray <JLWatchExerciseIntens *> *durationArray;


+(JLWearSyncFinishModel *)initWithData:(NSData*)data;

@end

NS_ASSUME_NONNULL_END
