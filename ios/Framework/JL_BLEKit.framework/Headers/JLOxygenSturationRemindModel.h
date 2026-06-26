//
//  JLOxygenSturationRemindModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2022/2/17.
//  Copyright © 2022 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface JLOxygenSturationRemindModel : JLwSettingModel
@property(nonatomic,assign)BOOL status;
@property(nonatomic,assign)WatchOxygenMsmType rType;


-(instancetype)initWithData:(NSData *)data;

- (instancetype)initWithModel:(WatchOxygenMsmType)type Status:(BOOL)status;
@end

NS_ASSUME_NONNULL_END
