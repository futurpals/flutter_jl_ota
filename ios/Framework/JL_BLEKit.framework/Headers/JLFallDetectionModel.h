//
//  JLFallDetectionModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface JLFallDetectionModel : JLwSettingModel
@property(nonatomic,assign)BOOL status;
@property(nonatomic,assign)WatchRemindType rType;
@property(nonatomic,strong,readonly)NSString *phoneNumber;

-(instancetype)initWithData:(NSData *)data;

- (instancetype)initWithModel:(WatchRemindType)type Status:(BOOL)status phoneNumber:(NSString * _Nullable)pn;

@end

NS_ASSUME_NONNULL_END
