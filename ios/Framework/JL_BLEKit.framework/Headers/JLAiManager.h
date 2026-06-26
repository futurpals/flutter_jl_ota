//
//  JLAiManager.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/8/9.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_TypeEnum.h>

NS_ASSUME_NONNULL_BEGIN

//MARK: - JLOpenPlatformInfo
/// 平台接口认证信息
@interface JLOpenPlatformInfo : NSObject
/// 版本号
@property(nonatomic,assign)uint8_t version;
/// 平台 ID
@property(nonatomic,copy)NSString *appID;
/// app key
@property(nonatomic,copy)NSString *appKey;
/// app 的密钥
@property(nonatomic,copy)NSString *appSecret;
/// 原始数据
@property(nonatomic,copy)NSData *basicData;

-(instancetype)initData:(NSData *)data;

@end

/// 平台接口认证信息
@interface JLOpenPlatformMessage : NSObject
/// 版本号
@property(nonatomic,assign)uint8_t version;
/// 支持平台信息
@property(nonatomic,copy)NSArray <JLOpenPlatformInfo *>* infoArray;

-(instancetype)initData:(NSData *)dt;

@end

/// 屏幕尺寸
@interface JLDialSize : NSObject

/// width
@property(nonatomic,assign) uint16_t width;

/// height
@property(nonatomic,assign) uint16_t height;

/// 初始化
/// - Parameters:
///   - width: width
///   - height: height
+(JLDialSize *)makeSize:(uint16_t)width Height:(uint16_t)height;

@end

//MARK: - JLAiManager
@class JL_ManagerM;
@class JLAiManager;

@protocol JLAIManagerDelegate <NSObject>

/// 设备回调/推送结果
/// - Parameter mgr: JLAiManager
-(void)jlaiUpdateStatus:(JLAiManager *)mgr;

@optional
///  设备主动推送JLOpenPlatformInfo信息
/// - Parameters:
///   - mgr: 设备
///   - infoArray: [JLOpenPlatformInfo]
-(void)jlaiUpdateDevAiOpenPlatforms:(JLAiManager *)mgr Info:(JLOpenPlatformMessage *)info;


@end

typedef void(^JLOpenPFBlock)(JLOpenPlatformMessage *message,JL_CMDStatus result);

/// AI状态 管理类
/// 当前接口适用于一些支持设备对讲的设备，在使用时需要先初始化当前类并接受代理：JLAIManagerDelegate
/// 在初始化后需要主动获取状态才可以获得首次的状态内容
///
@interface JLAiManager : NSObject

/// 版本号
@property(assign,nonatomic)uint8_t version;

/// 0x00:默认状态
/// 0x01:进入AI界面
/// 0x02:退出AI界面
@property(assign,nonatomic)uint8_t status;

/// 回调代理
@property(weak,nonatomic)id<JLAIManagerDelegate> delegate;

/// 获取AI 的状态
///- Parameters:
///   - manager: 设备对象
-(void)getStatus:(JL_ManagerM *)manager;

/// 设置设备的状态
/// - Parameters:
///   - manager: 设备对象
///   - result: 回调结果
-(void)setToDevice:(JL_ManagerM *)manager result:(JL_CMD_RESPOND _Nullable)result;


/// 获取平台接口认证信息，此信息需要先获取 JLDeviceConfig
/// 根据JLDeviceConfigModel 的 exportFunc 属性的
/// spOpenInfo 判断是否支持平台开放接口信息获得
/// - Parameters:
///   - manager: 设备对象
///   - result: 回调结果
-(void)getOpenPlatformInfo:(JL_ManagerM *)manager result:(JLOpenPFBlock _Nullable)result;

@end

NS_ASSUME_NONNULL_END
