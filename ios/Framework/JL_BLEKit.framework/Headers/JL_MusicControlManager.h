//
//  JL_MusicControlManager.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/12/20.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_FunctionBaseManager.h>
#import <JL_BLEKit/JL_Tools.h>


NS_ASSUME_NONNULL_BEGIN

__attribute__((deprecated(",JLDevPlayerCtrl")))

@interface JL_MusicControlManager  : JL_FunctionBaseManager


#pragma mark - Vendor SDK
/**
 0x01:; 0x02:; 0x03:; 0x04:; 0x05:
 */
-(void)cmdSetSystemPlayMode:(JL_MusicMode)mode __attribute__((deprecated("cmdSetPlayMode:")));

#pragma mark - Vendor SDK
/**
 */
-(void)cmdFastPlay:(JL_FCmdMusic)cmd
            Second:(uint16_t)sec
            Result:(JL_CMD_RESPOND __nullable)result __attribute__((deprecated("cmdFastPlay:，JLDevPlayerCtrl")));

@end

NS_ASSUME_NONNULL_END
