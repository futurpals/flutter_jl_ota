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

/// 公共 设置/通知/读取 交互类 0x33 回调协议
@protocol JLPublicSettingProtocol <NSObject>
@optional

/// 屏幕亮度设置回调/通知
/// - Parameters:
///   - manager: 设备
///   - light: 亮度
-(void)publicSettingScreenLight:(JL_ManagerM *)manager Value:(uint8_t)light;

/// 手电筒设置回调/通知
/// - Parameters:
///   - manager: 设备
///   - isOn: 是否打开
-(void)publicSettingFlashLight:(JL_ManagerM *)manager Value:(BOOL)isOn;

/// 设备绑定状态回调/通知
/// - Parameters:
///   - manager: 设备
///   - model: 绑定信息
-(void)publicSettingBindStatus:(JL_ManagerM *)manager Model:(JLPublicBindDeviceModel *)model;

/// 功能使用资源通知/回调
/// - Parameters:
///   - manager: 设备
///   - model: 资源信息
-(void)publicSettingFuncSource:(JL_ManagerM *)manager Model:(JLPublicSourceInfoModel *)model;

/// 功能使用资源通知/回调
/// - Parameters:
///   - manager: 设备
///   - model: 
///     0x00 结束
///     0x01 开始推送
-(void)publicSettingReplaceTipsVoiceStatus:(JL_ManagerM *)manager Model:(uint8_t )model Reason:(NSError *_Nullable)err;

///
/// - Parameters:
///   - manager: 设备
///   - mode: 设备 SDK 信息
-(void)publicSettingDeviceSDKMessage:(JL_ManagerM *)manager Mode:(JLPublicSDKInfoModel *_Nullable)mode;

@end


/// 公共 设置/通知/读取 交互类 0x33
@interface JLPublicSetting : NSObject

/// 代理
@property(nonatomic,assign)id<JLPublicSettingProtocol> delegate;

/// 读取设备当前屏幕亮度
/// - Parameters:
///   - manager: 设备
///   - block: 回调
-(void)cmdScreenLightGet:(JL_ManagerM *)manager result:(JLPSScreenLightCbk)block;

/// 设置设备的屏幕亮度
/// - Parameters:
///   - manager: 设备
///   - value: 亮度值 0～100
///   - block: 回调
-(void)cmdScreenLightSet:(JL_ManagerM *)manager  Value:(uint8_t)value result:(JLPSScreenLightCbk)block;

/// 读取手电筒开关
/// - Parameters:
///   - manager: 设备
///   - block: 回调
-(void)cmdFlashLightGet:(JL_ManagerM *)manager result:(JLPSFlashLightCbk)block;

/// 设置手电筒开关
/// - Parameters:
///   - manager: 设备
///   - isOn: 开关
///   - block: 回调
-(void)cmdFlashLightSet:(JL_ManagerM *)manager  Status:(BOOL)isOn result:(JLPSFlashLightCbk)block;


/// 获取绑定设备状态
/// - Parameters:
///   - manager: 设备
///   - block: 回调
-(void)cmdDeviceBindStatusGet:(JL_ManagerM *)manager result:(JLPSBindStatusCbk)block;


/// 获取功能使用资源设置（彩屏舱）
/// - Parameters:
///   - manager: 设备
///   - funcType: 功能码
///   0x01 屏幕保护程序
///   0x02 开机动画
///   0x03 墙纸
///   - block: 回调
-(void)cmdDeviceFuncUsedSourceGet:(JL_ManagerM *)manager Type:(uint8_t)funcType result:(JLPSSourceInfoCbk)block;

/// 设置功能使用资源（彩屏舱）
/// - Parameters:
///   - manager: 设备
///   - info: 设置内容对象
///   - block: 回调
-(void)cmdDeviceFuncUseSourceSet:(JL_ManagerM *)manager Info:(JLPublicSourceInfoModel *)info result:(JLPSSourceInfoCbk)block;


/// 开始发起替换提示音
/// - Parameters:
///   - manager: 设备
///   - info: 提示音包 tone.cfg 信息
///   - block: 状态回调
-(void)cmdDeviceReplaceTipsVoiceStart:(JL_ManagerM *)manager  Info:(JLPublicTipsVoiceRpInfo *)info result:(JLPSTipsVoiceRpCbk)block;


/// 获取设备 SDK 信息
/// - Parameters:
///   - manager: 设备
///   - block: 回调
-(void)cmdDeviceGetDeviceSDKInfo:(JL_ManagerM *)manager result:(JLPSSDKInfoCbk)block;

@end

NS_ASSUME_NONNULL_END
