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

@property(nonatomic,assign)BOOL isSupportAnc;

@property(nonatomic,assign)BOOL isSupportGameMode;

@property(nonatomic,assign)BOOL isSupportAutoAnc;

@property(nonatomic,assign)BOOL isSupportSmartPickFree;

/// scene noise reduction
@property(nonatomic,assign)BOOL isSupportSceneNoiseReduction;

/// Noise detection
@property(nonatomic,assign)BOOL isSupportNoiseDetection;

/// Vocal Boost Mode
@property(nonatomic,assign)BOOL isSupportVocalBoostMode;

/// Does the firmware support the "one drag two" switch function
@property(nonatomic,assign)BOOL isSupportDragWithMore;



-(void)configWithTargetFeature:(NSData *)data;



@end

NS_ASSUME_NONNULL_END
