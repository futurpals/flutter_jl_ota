//
//  JLSleepMonitorModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface JLSleepMonitorModel : JLwSettingModel
@property(nonatomic,assign)WatchSwitchType status;
@property(nonatomic,strong)WatchTimer *start;
@property(nonatomic,strong)WatchTimer *end;

-(instancetype)initWithData:(NSData *)data;

-(instancetype)initWithSwitchStatus:(WatchSwitchType)status Begin:(WatchTimer *)begin End:(WatchTimer *)end;


@end

NS_ASSUME_NONNULL_END
