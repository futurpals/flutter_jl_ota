//
//  JLDeviceConfig.h
//  JL_BLEKit
//
//  Created by EzioChan on 2022/10/31.
//  Copyright © 2022 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ECOneToMorePtl;
@class JLDeviceConfigTws;
@class JLDeviceConfigModel;

NS_ASSUME_NONNULL_BEGIN
typedef void(^JLConfigRsp)(JL_CMDStatus status, uint8_t sn, JLDeviceConfigModel* __nullable config);

typedef void(^JLConfigTwsRsp)(JL_CMDStatus status, uint8_t sn, JLDeviceConfigTws* __nullable config);


@protocol JLConfigPtl <NSObject>

@optional
-(void)deviceConfigWith:(JLDeviceConfigModel *)configModel;

-(void)deviceTwsConfigWith:(JLDeviceConfigTws *)configModel;

@end

@interface JLDeviceConfig : ECOneToMorePtl

+(instancetype)share;

/// - Parameters:
///   - manager: manager
-(void)deviceGetConfig:(JL_ManagerM *)manager result:(JLConfigRsp)result;

-(JLDeviceConfigModel *_Nullable)deviceGetConfigWithUUID:(NSString *)uuidStr;

/// - Parameters:
///   - manager: manager
-(void)deviceTwsGetConfig:(JL_ManagerM *)manager result:(JLConfigTwsRsp)result;

-(JLDeviceConfigTws *)deviceGetTwsConfigWithUUID:(NSString *)uuidStr;


-(void)pDeviceTest:(NSData *)data Status:(BOOL)st;

@end

NS_ASSUME_NONNULL_END
