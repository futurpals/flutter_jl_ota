//
//  JL_LRCManager.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/12/17.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_FunctionBaseManager.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JL_Tools.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_LRCType) {
    JL_LRCTypeDone                  = 1,
    JL_LRCTypeBusy                  = 2,
    JL_LRCTypeDoneFail              = 0x0e,
};
typedef void(^JL_LRC_BK)(NSString* __nullable lrc, JL_LRCType type);
typedef void(^JL_LRC_BK_1)(NSData* __nullable lrc, JL_LRCType type);

@interface JL_LRCManager : JL_FunctionBaseManager

#pragma mark - Vendor SDK
/**
 */
-(void)cmdLrcMonitorResult:(JL_LRC_BK __nullable)result;
-(void)cmdLrcMonitorResult_1:(JL_LRC_BK_1 __nullable)result;

@end

NS_ASSUME_NONNULL_END
