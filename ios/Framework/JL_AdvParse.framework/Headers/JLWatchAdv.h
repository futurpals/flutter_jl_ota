//
//  JLWatchAdv.h
//  JL_AdvParse
//
//  Created by EzioChan on 2023/12/12.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <JL_AdvParse/JLDevicesAdv.h>

NS_ASSUME_NONNULL_BEGIN

@interface JLWatchAdv : JLDevicesAdv

@property(nonatomic, strong) NSString *edrAddr;

/// 0x00 ble
/// 0x01 spp
@property(nonatomic, assign) int8_t connectWay;


@property(nonatomic, assign) int8_t connectState;

@property(nonatomic, assign) BOOL priorityConnection;

@end

NS_ASSUME_NONNULL_END
