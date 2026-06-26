//
//  JLChargingBoxAdv.h
//  JL_AdvParse
//
//  Created by EzioChan on 2023/12/12.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import "JLDevicesAdv.h"

NS_ASSUME_NONNULL_BEGIN

@interface JLChargingBoxAdv : JLDevicesAdv

@property(nonatomic, strong) NSString *edrAddr;

@property(nonatomic, assign) BOOL isParied;

@property(nonatomic, assign) BOOL isOpen;

@property(nonatomic, assign) uint8_t status;

@property(nonatomic, assign) uint8_t batteryLeft;

@property(nonatomic, assign) uint8_t batteryRight;

@property(nonatomic, assign) uint8_t batteryBox;

@property(nonatomic, assign) BOOL isChargingLeft;

@property(nonatomic, assign) BOOL isChargingRight;

@property(nonatomic, assign) BOOL isChargingBox;

/// seq
@property(nonatomic, assign) uint8_t seq;

@property(nonatomic, assign) uint8_t mode;

@property(nonatomic, copy) NSData *hashData;

@end

NS_ASSUME_NONNULL_END
