//
//  JLPublicSetting.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/12/1.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JLPublicSettingBlocks.h"


NS_ASSUME_NONNULL_BEGIN
@class JL_ManagerM;

@protocol JLPublicSettingProtocol <NSObject>
@optional

/// - Parameters:
-(void)publicSettingScreenLight:(JL_ManagerM *)manager Value:(uint8_t)light;

/// - Parameters:
-(void)publicSettingFlashLight:(JL_ManagerM *)manager Value:(BOOL)isOn;

/// - Parameters:
-(void)publicSettingBindStatus:(JL_ManagerM *)manager Model:(JLPublicBindDeviceModel *)model;

/// - Parameters:
-(void)publicSettingFuncSource:(JL_ManagerM *)manager Model:(JLPublicSourceInfoModel *)model;

/// - Parameters:
///   - model: 
-(void)publicSettingReplaceTipsVoiceStatus:(JL_ManagerM *)manager Model:(uint8_t )model Reason:(NSError *_Nullable)err;

///
/// - Parameters:
-(void)publicSettingDeviceSDKMessage:(JL_ManagerM *)manager Mode:(JLPublicSDKInfoModel *_Nullable)mode;

@end


@interface JLPublicSetting : NSObject

@property(nonatomic,assign)id<JLPublicSettingProtocol> delegate;

/// - Parameters:
-(void)cmdScreenLightGet:(JL_ManagerM *)manager result:(JLPSScreenLightCbk)block;

/// - Parameters:
-(void)cmdScreenLightSet:(JL_ManagerM *)manager  Value:(uint8_t)value result:(JLPSScreenLightCbk)block;

/// - Parameters:
-(void)cmdFlashLightGet:(JL_ManagerM *)manager result:(JLPSFlashLightCbk)block;

/// - Parameters:
-(void)cmdFlashLightSet:(JL_ManagerM *)manager  Status:(BOOL)isOn result:(JLPSFlashLightCbk)block;


/// - Parameters:
-(void)cmdDeviceBindStatusGet:(JL_ManagerM *)manager result:(JLPSBindStatusCbk)block;


/// - Parameters:
-(void)cmdDeviceFuncUsedSourceGet:(JL_ManagerM *)manager Type:(uint8_t)funcType result:(JLPSSourceInfoCbk)block;

/// - Parameters:
-(void)cmdDeviceFuncUseSourceSet:(JL_ManagerM *)manager Info:(JLPublicSourceInfoModel *)info result:(JLPSSourceInfoCbk)block;


/// - Parameters:
-(void)cmdDeviceReplaceTipsVoiceStart:(JL_ManagerM *)manager  Info:(JLPublicTipsVoiceRpInfo *)info result:(JLPSTipsVoiceRpCbk)block;


/// - Parameters:
-(void)cmdDeviceGetDeviceSDKInfo:(JL_ManagerM *)manager result:(JLPSSDKInfoCbk)block;

@end

NS_ASSUME_NONNULL_END
