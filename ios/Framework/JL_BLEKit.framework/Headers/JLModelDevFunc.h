//
//  JLModelDevFunc.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/11/29.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface JLModelDevFunc : NSObject

/// 当前模式
/// 0x16代表低功耗模式)
@property (nonatomic, assign) uint8_t currentModel;

/// 设备是否支持蓝牙（EDR）
@property (nonatomic, assign) BOOL isSupportEDR;

/// 设备是否支持音乐模式
@property (nonatomic, assign) BOOL isSupportDevMusic;

/// 设备是否支持 RTC
@property (nonatomic, assign) BOOL isSupportDevRTC;

/// 设备是否支持 LineIn
@property (nonatomic, assign) BOOL isSupportDevLineIn;

/// 设备是否支持 FM
@property (nonatomic, assign) BOOL isSupportDevFm;

/// 设备是否支持氛围灯
@property (nonatomic, assign) BOOL isSupportDevLight;

/// 设备是否支持 FMTX
@property (nonatomic, assign) BOOL isSupportDevFMTX;

/// 设备是否支持 EQ
@property (nonatomic, assign) BOOL isSupportDevEQ;

/// 设备是否支持 SPDIF
@property (nonatomic, assign, readonly) BOOL isSupportSPDIF;

/// 设备是否支持 PC Server
@property (nonatomic, assign, readonly) BOOL isSupportPCServer;

/// 是否显示不在线的usb 、sd、linein功能
@property (nonatomic, assign) BOOL isShowOfflineFunc;

/// 设备是否持有 USB
@property (nonatomic, assign) BOOL isSupportUSB;

/// 设备是否持有 SD0
@property (nonatomic, assign) BOOL isSupportSD0;

/// 设备是否持有 SD1
@property (nonatomic, assign) BOOL isSupportSD1;

/// 设备是否支持网络电台
@property (nonatomic, assign) BOOL isSupportNetRadio;

-(instancetype)initWithData:(NSData *)data;

@end



NS_ASSUME_NONNULL_END
