//
//  JLModelVocalBoost.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/9/13.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <JL_BLEKit/JL_BLEKit.h>

NS_ASSUME_NONNULL_BEGIN


@class JLModelVocalBoost;

@protocol JLModelVocalBoostDelegate <NSObject>

-(void)vocalBoostGetInfo:(JLModelVocalBoost *)model;

@end

typedef void(^JLModelVocalBoostBlock)(JLModelVocalBoost *model);


@interface JLModelVocalBoost : JLCmdBasic

@property(nonatomic,assign)uint8_t version;

@property(nonatomic,assign)uint8_t status;

@property(nonatomic,weak)id<JLModelVocalBoostDelegate> delegate;

-(void)vocalBoostStatusGet:(JL_ManagerM *)manager Result:(JLModelVocalBoostBlock)block;

/// - Parameters:
-(void)vocalBoostStatusSet:(JL_ManagerM *)manager Status:(uint8_t)status Result:(JL_CMD_RESPOND)result;


@end

NS_ASSUME_NONNULL_END
