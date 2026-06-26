//
//  JLConsequentHeartRateModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface JLConsequentHeartRateModel : JLwSettingModel
@property(nonatomic,assign)BOOL status;
@property(nonatomic,assign)WatchConsequentType rType;

@property(nonatomic,assign)UInt8    maxHeartRate;

@property(nonatomic,assign)UInt8    minHeartRate;

@property(nonatomic,assign)BOOL hasRange;

-(instancetype)initWithData:(NSData *)data;

- (instancetype)initWithModel:(WatchConsequentType)type Status:(BOOL)status;

- (instancetype)initWithModel:(WatchConsequentType)type Status:(BOOL)status Min:(UInt8) min Max:(UInt8)max;
@end

NS_ASSUME_NONNULL_END
