//
//  JL_SystemVolume.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/12/20.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_FunctionBaseManager.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JL_Tools.h>

NS_ASSUME_NONNULL_BEGIN

@interface JL_SystemVolume : JL_FunctionBaseManager

#pragma mark - Vendor SDK
/**
 */
-(void)cmdSetSystemVolume:(UInt8)volume;
-(void)cmdSetSystemVolume:(UInt8)volume Result:(JL_CMD_RESPOND __nullable)result;

@end

NS_ASSUME_NONNULL_END
