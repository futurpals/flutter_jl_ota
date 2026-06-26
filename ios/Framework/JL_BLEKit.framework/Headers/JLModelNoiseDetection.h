//
//  JLModelNoiseDetection.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/9/13.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <JL_BLEKit/JL_BLEKit.h>

NS_ASSUME_NONNULL_BEGIN
@class JLModelNoiseDetection;

@protocol JLModelNoiseDetectionDelegate <NSObject>

-(void)noiseDetectionGetInfo:(JLModelNoiseDetection *)model;

@end

typedef void(^JLModelNoiseDetectionBlock)(JLModelNoiseDetection *model);

@interface JLModelNoiseDetection : JLCmdBasic

@property(nonatomic,assign)uint8_t version;

@property(nonatomic,assign)uint8_t status;

@property(nonatomic,weak)id<JLModelNoiseDetectionDelegate> delegate;

-(void)noiseDetectionStatusGet:(JL_ManagerM *)manager Result:(JLModelNoiseDetectionBlock)block;

/// - Parameters:
-(void)noiseDetectionStatusSet:(JL_ManagerM *)manager Status:(uint8_t)status Result:(JL_CMD_RESPOND)result;


@end

NS_ASSUME_NONNULL_END
