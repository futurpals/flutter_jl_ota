//
//  JLModelSmartPickFree.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/9/12.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_TypeEnum.h>

NS_ASSUME_NONNULL_BEGIN

@class JL_ManagerM;
@class JLModelSmartPickFree;

@protocol JLModelSmartPickFreeDelegate <NSObject>

-(void)smartPickFreeGetInfo:(JLModelSmartPickFree *)model;

@end

@interface JLModelSmartPickFree : NSObject

@property(nonatomic,assign)uint8_t version;

@property(nonatomic,assign)uint8_t funcType;

@property(nonatomic,assign)BOOL funcStatus;

@property(nonatomic,assign)uint8_t senivitiy;

@property(nonatomic,assign)uint8_t autoInterval;


@property(nonatomic,weak)id<JLModelSmartPickFreeDelegate> delegate;

/// - Parameters:
-(void)smartPickFreeSetOn:(JL_ManagerM *)manager st:(BOOL)status Result:(JL_CMD_RESPOND)result;

/// - Parameters:
-(void)smartPickFreeSetSenivitiy:(JL_ManagerM *)manager Senivitiy:(uint8_t)senivitiy Result:(JL_CMD_RESPOND)result;

/// - Parameters:
-(void)smartPickFreeSetAutoInterval:(JL_ManagerM *)manager Interval:(uint8_t)interval Result:(JL_CMD_RESPOND)result;


-(void)smartPickFreeGet:(JL_ManagerM *)manager;

@end

NS_ASSUME_NONNULL_END
