//
//  JLPublicSettingBlocks.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/12/1.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_TypeEnum.h>

NS_ASSUME_NONNULL_BEGIN

#define PUBLIC_SCREEN_LIGHT             0x0001 //屏幕亮度
#define PUBLIC_FLASH_LIGHT              0x0002 //手电筒
#define PUBLIC_DEVICE_BIND_STATUS       0x0003 //设备绑定
#define PUBLIC_FUNC_SOURCE              0x0004 //功能使用资源（彩屏舱）
#define PUBLIC_FUNC_4G                  0x0005 //4G功能升级功能
#define PUBLIC_TIPS_VOICE               0x0006 //替换提示音
#define PUBLIC_SDK_INFO                 0x0008 //SDK信息

@class JLPublicBindDeviceModel;
@class JLPublicSourceInfoModel;
@class JLPublic4GModel;
@class JLPublicSDKInfoModel;

/// 屏幕亮度回调
typedef void(^JLPSScreenLightCbk)(JL_CMDStatus status,uint8_t value);

/// 手电筒开关
typedef void(^JLPSFlashLightCbk)(JL_CMDStatus status,BOOL isOn);

/// 绑定状态
typedef void(^JLPSBindStatusCbk)(JL_CMDStatus status,JLPublicBindDeviceModel *_Nullable model);
/// 彩屏舱资源
typedef void (^JLPSSourceInfoCbk)(JL_CMDStatus status,JLPublicSourceInfoModel *_Nullable model);

/// 4G模块升级回调
typedef void (^JLPSSource4GCbk)(JL_CMDStatus status,JLPublic4GModel *_Nullable model);

/// 替换提示音回调
typedef void(^JLPSTipsVoiceRpCbk)(JL_CMDStatus status,uint8_t op);

/// 设备 SDK 信息回调
typedef void(^JLPSSDKInfoCbk)(JL_CMDStatus status,JLPublicSDKInfoModel *_Nullable model);

//MARK: - 绑定设备状态(彩屏舱）
/// 绑定设备状态
@interface JLPublicBindDeviceModel : NSObject

/// 设备类型
/// 1 耳机
/// 2 充电仓
@property(nonatomic,assign)uint8_t type;

/// 经典蓝牙地址
/// 若不支持经典蓝牙，此值为 0
@property(nonatomic,copy)NSString *edrAddr;

/// ble 蓝牙地址
/// 若不支持 ble 蓝牙，此值为 0
@property(nonatomic,copy)NSString *bleAddr;

/// 连接状态
/// 0 未连接
/// 1 已连接
/// 2 正在回连
/// 0xff 不可连接
@property(nonatomic,assign)uint8_t status;

/// 连接方式
/// 0 BLE
/// 1 SPP 
@property(nonatomic,assign)uint8_t way;

+(JLPublicBindDeviceModel *)initData:(NSData *)data;
@end

//MARK: -公有设置的资源信息(彩屏舱）
/// 公有设置的资源信息
@interface JLPublicSourceInfoModel:NSObject

/// 功能码
/// 0x01 屏幕保护程序
/// 0x02 开机动画
/// 0x03 墙纸
@property(nonatomic,assign)uint8_t type;

/// 存储器的句柄
@property(nonatomic,copy)NSData *fileHandle;

/// 文件簇号
/// 设置时当前字段设为 0
@property(nonatomic,assign)uint32_t cluster;

/// 文件内容 CRC
/// 设置时当前字段为 0
@property(nonatomic,assign)uint16_t crc;

/// 文件路径数据
@property(nonatomic,strong)NSString *filePath;

-(NSData *)beData;

+(JLPublicSourceInfoModel *)initData:(NSData *)data;

@end

//MARK: - 4G 模块基本信息

/// 4G 模块基本信息
@interface JLPublic4GModel:NSObject

/// 供应商信息
/// 0x01:紫光展锐
/// 0x02:归芯科技
@property(nonatomic,assign)uint8_t vendor;

/// 强制升级标识位
/// 0x00:不强制
/// 0x01:强制升级
@property(nonatomic,assign)uint8_t updateStatus;

/// 版本
@property(nonatomic,copy)NSString *version;

/// 开始 OTA 等待时间
@property(nonatomic,assign)NSTimeInterval startOtaMaxTimeout;

/// 结束 OTA 等待时间
@property(nonatomic,assign)NSTimeInterval endOtaMaxTimeout;


+(JLPublic4GModel *)initData:(NSData *)data;

@end

//MARK: - 替换提示音参数
@interface JLPublicTipsVoiceRpInfo : NSObject

/// 目标存储器句柄
/// 这个要从 JLModel_Device 中获得
/// JLModelCardInfo    *cardInfo;
@property(nonatomic,copy)NSData *devHandle;

/// 下发的文件名
@property(nonatomic,strong)NSString *fileName;

/// 下发的文件内容
@property(nonatomic,copy)NSData *sendData;

-(NSData *)createData;

@end

// MARK: - 设备 SDK 信息

/// 设备 SDK 信息
@interface JLPublicSDKInfoModel : NSObject

/// 项目对应 ID
/// 0x0001 充电仓
@property(nonatomic,assign)uint16_t projectId;

/// 产品对应 ID
/// 0x0001 彩屏舱
@property(nonatomic,assign)uint16_t productId;

/// 芯片 ID
/// 0x0001 AC701N
/// 0x0002 AC707N
@property(nonatomic,assign)uint16_t chipId;

/// 是否支持 gif
@property(nonatomic,assign)BOOL isSupportGif;

/// 初始化
/// - Parameter data: 数据
+ (JLPublicSDKInfoModel *)initData:(NSData *)data;

@end
NS_ASSUME_NONNULL_END
