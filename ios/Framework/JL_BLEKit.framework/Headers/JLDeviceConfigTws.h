//
//  JLDeviceConfigTws.h
//  JL_BLEKit
//
//  Created by EzioChan on 2024/1/23.
//  Copyright © 2024 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JLDeviceConfigFuncModel.h>

NS_ASSUME_NONNULL_BEGIN

@interface JLDeviceConfigTws : JLDeviceConfigBasic

@property(nonatomic, assign)BOOL isSupportReplaceTipsVoice;

/// Voice translation
@property(nonatomic,assign,readonly)BOOL isSupportTranslate;

/// is use A2DP to play
@property(nonatomic,assign,readonly)BOOL isUseA2DP;

@end

NS_ASSUME_NONNULL_END
