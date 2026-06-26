//
//  JL_SystemTime.h
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

@interface JL_SystemTime : JL_FunctionBaseManager


@property(nonatomic,strong)JLModel_RTC *rtc;

#pragma mark - Vendor SDK
/**
 */
-(void)cmdSetSystemTime:(NSDate*)date __attribute__((deprecated ( "Please use the (cmdSetSystemYear: Month: Day: Hour: Minute: Second) method instead. The current method will be invalid")));


-(void)cmdSetSystemYear:(uint16_t)year
                  Month:(uint8_t)month
                    Day:(uint8_t)day
                   Hour:(uint8_t)hour
                 Minute:(uint8_t)min
                 Second:(uint8_t)sec;

@end

NS_ASSUME_NONNULL_END
