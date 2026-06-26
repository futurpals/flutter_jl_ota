//
//  JLModel_AlarmSetting.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/10/15.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface JLModel_AlarmSetting : NSObject
@property(assign,nonatomic)uint8_t index;
@property(assign,nonatomic)uint8_t isCount;
@property(assign,nonatomic)uint8_t count;
@property(assign,nonatomic)uint8_t isInterval;
@property(assign,nonatomic)uint8_t interval;
@property(assign,nonatomic)uint8_t isTime;
@property(assign,nonatomic)uint8_t time;
-(NSData*)dataModel;
@end

NS_ASSUME_NONNULL_END
