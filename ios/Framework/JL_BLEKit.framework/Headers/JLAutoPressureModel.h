//
//  JLAutoPressureModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, WatchAPLeveType) {
    WatchAPLeve_Relex = 0x00,
    WatchAPLeve_Normal = 0x01,
    WatchAPLeve_Middle = 0x02,
    WatchAPLeve_Hight = 0x03
};

@interface JLAutoPressureModel : JLwSettingModel

@property(nonatomic,assign)BOOL status;
@property(nonatomic,assign)WatchAPLeveType model;

-(instancetype)initWithData:(NSData *)data;

-(instancetype)initWithModel:(WatchAPLeveType)model switchStatus:(BOOL)status;

@end

NS_ASSUME_NONNULL_END
