//
//  JLDialInfoExtentManager.h
//  JL_BLEKit
//
//  Created by EzioChan on 2024/2/20.
//  Copyright © 2024 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_TypeEnum.h"

@class JLDialInfoExtentedModel;
@class JL_ManagerM;

NS_ASSUME_NONNULL_BEGIN

/// Dial information extended content block
typedef void(^JLDialInfoExtentedBlock)(JL_CMDStatus status,JLDialInfoExtentedModel *_Nullable op);

/// Request device dial information extended content class
@interface JLDialInfoExtentManager : NSObject

/// Single
+(instancetype)share;

/// Start request dial information extended content
/// - Parameters:
-(void)getDialInfoExtented:(JL_ManagerM *)manager result:(JLDialInfoExtentedBlock)block;

@end

NS_ASSUME_NONNULL_END
