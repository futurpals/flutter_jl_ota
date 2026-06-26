//
//  JLSedentaryRmdModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface JLSedentaryRmdModel : JLwSettingModel

@property(nonatomic,assign)BOOL status;

@property(nonatomic,assign)WatchRemindType rType;

@property(nonatomic,assign)BOOL doNotDisturb;

@property(nonatomic,strong)WatchTimer *begin;

@property(nonatomic,strong)WatchTimer *end;

- (instancetype)initWithData:(NSData *)data;

- (instancetype)initWithModel:(WatchRemindType)type Status:(BOOL)status DoNotDisturb:(BOOL)dnd Begin:(WatchTimer *)start End:(WatchTimer *)ed;

@end

NS_ASSUME_NONNULL_END
