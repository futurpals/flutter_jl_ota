//
//  JLExerciseHeartRateRemindModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"
#import "JLWatchEnum.h"
NS_ASSUME_NONNULL_BEGIN

@interface JLExerciseHeartRateRemindModel : JLwSettingModel
@property(nonatomic,assign)BOOL status;
@property(nonatomic,assign)uint8_t maxRate;

@property(nonatomic,assign)WatchHeartRateType way;

-(instancetype)initWithWay:(WatchHeartRateType)way maxRate:(uint8_t)max switchStatus:(BOOL)status;

-(instancetype)initWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
