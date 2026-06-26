//
//  JL_CustomManager.h
//  JL_BLEKit
//  Created by Jieli Technology on 2021/12/21.
//  Modify by EzioChan on 2023/03/16.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_FunctionBaseManager.h"
#import "JL_TypeEnum.h"
#import "JL_Tools.h"

NS_ASSUME_NONNULL_BEGIN

extern NSString *kJL_MANAGER_CUSTOM_DATA;
extern NSString *kJL_MANAGER_CUSTOM_DATA_RSP;


@protocol JLCustomCmdPtl <NSObject>

/// - Parameters:
-(void)customCmdResponse:(JL_ManagerM *)manager Status:(uint8_t)status WithData:(NSData *)data;

/// - Parameters:
-(void)customCmdRequire:(JL_ManagerM *)manager WithData:(NSData *)data isNeedResponse:(BOOL)isNeedResponse SN:(uint8_t)sn;


@end

@interface JL_CustomManager : JL_FunctionBaseManager

@property(nonatomic,weak)id<JLCustomCmdPtl> delegate;

/// timeout max
/// default 3s
@property(nonatomic,assign)NSInteger maxTime;

#pragma mark - Vendor SDK

-(void)cmdCustomData:(NSData* __nullable)data
              Result:(JL_CMD_RESPOND __nullable)result __attribute__((deprecated("use cmdCustomData:isNeedResponse:Result:")));

-(void)cmdCustomData:(NSData *)data isNeedResponse:(BOOL)isNeedResponse Result:(JL_CMD_RESPOND __nullable)result;

-(void)cmdCustomResponse:(uint8_t)sn
                    Data:(NSData* __nullable)data;

@end

NS_ASSUME_NONNULL_END
