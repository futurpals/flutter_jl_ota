//
//  JL_SDM_OxSaturation.h
//  Test
//
//  Created by EzioChan on 2021/4/7.
//  Copyright © 2021 Zhuhai Jieli Technology Co.,Ltd. All rights reserved.
//

#import "JLSportDataModel.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JLOxSaturationType) {
    JLOxSaturation_nowSta = 0x01,
    JLOxSaturation_max = 0x01 << 1,
    JLOxSaturation_min = 0x01 << 2,
    JLOxSaturation_single = 0x01 << 3
};

@interface JL_SDM_OxSaturation : JLSportDataModel

@property(nonatomic,assign)int staturation;
@property(nonatomic,assign)uint8_t max;
@property(nonatomic,assign)uint8_t min;

@property(nonatomic,assign)uint8_t singleStaturation;

@property(nonatomic,assign)BOOL isSingle;


+(JL_SDM_OxSaturation*)responseData:(NSData *)value subMask:(NSData *)submask;

+(JL_SDM_OxSaturation*)require;


+(JL_SDM_OxSaturation*)requireByBit:(JLOxSaturationType)type;


@end

NS_ASSUME_NONNULL_END
