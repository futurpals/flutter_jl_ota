//
//  JLTwsSupportFuncs.h
//  JL_BLEKit
//
//  Created by EzioChan on 2024/12/31.
//  Copyright © 2024 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface JLTwsSupportFuncs : NSObject

/// 是否支持ANC功能
@property(nonatomic,assign)BOOL isSupportAnc;

/// 是否支持游戏模式
@property(nonatomic,assign)BOOL isSupportGameMode;

/// 是否支持自适应ANC
@property(nonatomic,assign)BOOL isSupportAutoAnc;

/// 是否支持智能免摘
@property(nonatomic,assign)BOOL isSupportSmartPickFree;

/// 是否支持场景降噪
/// scene noise reduction
@property(nonatomic,assign)BOOL isSupportSceneNoiseReduction;

/// 是否支持风噪检测
/// Noise detection
@property(nonatomic,assign)BOOL isSupportNoiseDetection;

/// 是否支持人声增强模式
/// Vocal Boost Mode
@property(nonatomic,assign)BOOL isSupportVocalBoostMode;

/// 固件是否支持“一拖二”开 关功能
/// Does the firmware support the "one drag two" switch function
@property(nonatomic,assign)BOOL isSupportDragWithMore;



-(void)configWithTargetFeature:(NSData *)data;



@end

NS_ASSUME_NONNULL_END
