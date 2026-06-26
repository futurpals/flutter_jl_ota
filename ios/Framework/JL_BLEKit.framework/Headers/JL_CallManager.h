//
//  JL_CallManager.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/12/16.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_FunctionBaseManager.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JL_Tools.h>
NS_ASSUME_NONNULL_BEGIN

@interface JL_CallManager : JL_FunctionBaseManager

#pragma mark - Vendor SDK
/**
 */
-(void)cmdPhoneCall:(NSString*)number Result:(JL_CMD_RESPOND __nullable)result;

#pragma mark - Vendor SDK
extern NSString *kJL_MANAGER_CALL_STATUS;

#pragma mark - Vendor SDK
#pragma mark - Vendor SDK
/**
 */
-(void)cmdPhoneNumberOnWay:(uint8_t)way;

@end

NS_ASSUME_NONNULL_END
