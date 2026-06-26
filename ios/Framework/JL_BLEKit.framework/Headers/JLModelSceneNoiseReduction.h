//
//  JLModelSceneNoiseReduction.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/9/13.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <JL_BLEKit/JLCmdBasic.h>

NS_ASSUME_NONNULL_BEGIN
@class JLModelSceneNoiseReduction;

@protocol JLModelSceneNoiseReductionDelegate <NSObject>

-(void)sceneNoiseReductionGetInfo:(JLModelSceneNoiseReduction *)model;

@end

typedef void(^JLSceneNoiseReductionBlock)(JLModelSceneNoiseReduction *model);

@interface JLModelSceneNoiseReduction : JLCmdBasic

@property(nonatomic,assign)uint8_t version;

@property(nonatomic,assign)uint8_t scene;

@property(nonatomic,weak)id<JLModelSceneNoiseReductionDelegate> delegate;

-(void)sceneNoiseStatusGet:(JL_ManagerM *)manager Result:(JLSceneNoiseReductionBlock)block;

/// - Parameters:
-(void)sceneNoiseStatusSet:(JL_ManagerM *)manager Scene:(uint8_t)scene Result:(JL_CMD_RESPOND)result;


@end

NS_ASSUME_NONNULL_END
