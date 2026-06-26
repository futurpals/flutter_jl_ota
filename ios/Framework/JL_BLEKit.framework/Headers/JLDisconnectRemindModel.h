//
//  JLDisconnectRemindModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface JLDisconnectRemindModel : JLwSettingModel
@property(nonatomic,assign)BOOL status;
@property(nonatomic,assign)WatchRemindType rType;

-(instancetype)initWithData:(NSData *)data;

- (instancetype)initWithModel:(WatchRemindType)type Status:(BOOL)status;

@end

NS_ASSUME_NONNULL_END
