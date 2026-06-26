//
//  JLEarphoneAdv.h
//  JL_AdvParse
//
//  Created by EzioChan on 2023/12/12.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import "JLDevicesAdv.h"

NS_ASSUME_NONNULL_BEGIN

@interface JLEarphoneAdv : JLDevicesAdv

@property(nonatomic, assign) uint8_t batteryLeft;

@property(nonatomic, assign) uint8_t batteryRight;

@property(nonatomic, assign) BOOL isChargingLeft;

@property(nonatomic, assign) BOOL isChargingRight;

@property(nonatomic, assign) BOOL isParied;

@property(nonatomic, assign) BOOL isMaster;

@property(nonatomic, assign) BOOL enableConnect;

@property(nonatomic, assign) uint8_t status;


@end

NS_ASSUME_NONNULL_END
