//
//  JL_OTAManager.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/11/16.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JLLogHelper/JLLogHelper.h>

NS_ASSUME_NONNULL_BEGIN
@class JLOtaReConnectOption;

typedef NS_ENUM(UInt16, JL_OTAResult) {
    /// OTA升级成功
    JL_OTAResultSuccess = 0x00,
    /// OTA升级失败
    JL_OTAResultFail = 0x01,
    /// OTA升级数据为空
    JL_OTAResultDataIsNull = 0x02,
    /// OTA指令失败
    JL_OTAResultCommandFail = 0x03,
    /// OTA标示偏移查找失败
    JL_OTAResultSeekFail = 0x04,
    /// OTA升级固件信息错误
    JL_OTAResultInfoFail = 0x05,
    /// OTA升级设备电压低
    JL_OTAResultLowPower = 0x06,
    /// 未能进入OTA升级模式
    JL_OTAResultEnterFail = 0x07,
    /// OTA升级中
    JL_OTAResultUpgrading = 0x08,
    /// OTA需重连设备(uuid方式)
    JL_OTAResultReconnect = 0x09,
    /// OTA需设备重启
    JL_OTAResultReboot = 0x0a,
    /// OTA准备中
    JL_OTAResultPreparing = 0x0b,
    /// OTA准备完成
    JL_OTAResultPrepared = 0x0f,
    /// 设备已在升级中
    JL_OTAResultStatusIsUpdating = 0x10,
    /// 当前固件多台设备连接，请手动断开另一个设备连接
    JL_OTAResultFailedConnectMore = 0x11,
    /// 升级数据校验失败，SN 多次重复
    JL_OTAResultFailSameSN = 0xe0,
    /// 升级取消
    JL_OTAResultCancel = 0xe1,
    /// 升级数据校验失败
    JL_OTAResultFailVerification = 0xf1,
    /// 升级失败
    JL_OTAResultFailCompletely = 0xf2,
    /// 升级数据校验失败，加密Key不对
    JL_OTAResultFailKey = 0xf3,
    /// 升级文件出错
    JL_OTAResultFailErrorFile = 0xf4,
    /// uboot不匹配
    JL_OTAResultFailUboot = 0xf5,
    /// 升级过程长度出错
    JL_OTAResultFailLenght = 0xf6,
    /// 升级过程flash读写失败
    JL_OTAResultFailFlash = 0xf7,
    /// 升级过程指令超时
    JL_OTAResultFailCmdTimeout = 0xf8,
    /// 相同版本
    JL_OTAResultFailSameVersion = 0xf9,
    /// TWS耳机未连接
    JL_OTAResultFailTWSDisconnect = 0xfa,
    /// 耳机未在充电仓
    JL_OTAResultFailNotInBin = 0xfb,
    /// OTA需重连设备(mac方式)
    JL_OTAResultReconnectWithMacAddr = 0xfc,
    /// OTA设备断开
    JL_OTAResultDisconnect = 0xfd,
    /// OTA需重连设备(更新资源)
    JL_OTAResultReconnectUpdateSource = 0xfe,
    /// OTA未知错误
    JL_OTAResultUnknown
};

typedef NS_ENUM(UInt8, JL_OTAReconnectType) {
    JL_OTAReconnectTypeUUID = 0x00,    // OTA升级回连使用uuid
    JL_OTAReconnectTypeMACAddr = 0x01, // OTA升级回连使用mac地址
};

typedef NS_ENUM(UInt8, JL_OtaStatus) {
    JL_OtaStatusNormal = 0, // 正常升级
    JL_OtaStatusForce = 1,  // 强制升级
};
typedef NS_ENUM(UInt8, JL_OtaHeadset) {
    JL_OtaHeadsetNO = 0,  // 耳机单备份 正常升级
    JL_OtaHeadsetYES = 1, // 耳机单备份 强制升级
};

typedef NS_ENUM(UInt8, JL_OtaWatch) {
    JL_OtaWatchNO = 0,  // 手表资源 正常升级
    JL_OtaWatchYES = 1, // 手表资源 强制升级
}__attribute__((deprecated("This enum is deprecated. Use JLOtaSourcesExtendMode instead.")));

/// OTA资源升级模式
typedef NS_ENUM(UInt8, JLOtaSourcesExtendMode) {
    /// 不启用
    JLSourcesExtendModeDisable = 0,
    /// 启用普通资源升级模式
    JLSourcesExtendModeNormal = 1,
    /// 启用只升级资源的模式
    JLSourcesExtendModeSourceOnly = 2,
    /// 启用只升级固件程序的模式
    JLSourcesExtendModeFirmwareOnly = 3,
};

typedef NS_ENUM(UInt8, JL_BootLoader) {
    JL_BootLoaderNO = 0,  // 不需要下载Bootloader
    JL_BootLoaderYES = 1, // 需要下载BootLoader
};
typedef NS_ENUM(UInt8, JL_Partition) {
    JL_PartitionSingle = 0, // 固件单备份
    JL_PartitionDouble = 1, // 固件双备份
};

typedef void (^JL_OTA_RT)(JL_OTAResult result, float progress);

typedef void (^JL_OTA_RESULT)(uint8_t status, uint8_t sn, NSData *__nullable data);

@class JL_OTAManager;

/// OTA 升级管理对象回调
@protocol JL_OTAManagerDelegate <NSObject>

/// 即将被发送的数据
/// @param data 数据内容
- (void)otaDataSend:(NSData *_Nonnull)data;

@optional
/// 回调设备状态信息
/// @param manager 对象状态
- (void)otaFeatureResult:(JL_OTAManager *_Nonnull)manager;

/// 回调升级状态以及进度等
/// @param result 状态以及进度信息
/// @param progress 进度信息
- (void)otaUpgradeResult:(JL_OTAResult)result Progress:(float)progress;

/// 取消OTA升级
- (void)otaCancel;

@end

/// OTA升级管理对象
@interface JL_OTAManager : NSObject

/// 设备UUID（需要开发者填入）
@property(strong, nonatomic) NSString *mBLE_UUID;

/// 设备名称（需要开发者填入）
@property(strong, nonatomic) NSString *mBLE_NAME;

/// 是否仅仅支持BLE
@property(assign, nonatomic) BOOL bleOnly;

/// ble蓝牙地址
@property(strong, nonatomic) NSString *bleAddr;

/// SN值
@property(assign, nonatomic) uint8_t mCmdSN;

/// 设备版本号
@property(assign, nonatomic) uint16_t version;

/// 设备版本信息
@property(strong, nonatomic) NSString *versionFirmware;

/// 设备OTA状态
@property(assign, nonatomic) JL_OtaStatus otaStatus;

/// 耳机单备份 是否需要强制升级
@property(assign, nonatomic) JL_OtaHeadset otaHeadset;

/// 手表资源 是否需要强制升级
@property(assign, nonatomic) JL_OtaWatch otaWatch __attribute__((deprecated("This property is deprecated. Use otaSourceMode instead.")));

/// 是否支持复用空间进行 OTA
@property(assign, nonatomic) BOOL isSupportReuseSpaceOTA;

/// 资源升级模式类型
@property(assign, nonatomic) JLOtaSourcesExtendMode otaSourceMode;

/// 设备OTA时支持单/双备份
@property(assign, nonatomic) JL_Partition otaPartition;

/// 设备是否需要下载Loader
@property(assign, nonatomic) JL_BootLoader bootloaderType;

/// OTA升级回连方式
@property(assign, nonatomic) JL_OTAReconnectType otaReconnectType;

/// OTA升级内容大小（设备通知的）
@property(assign, nonatomic, readonly) int64_t otaLength;

/// 已传输的数据大小
@property(assign, nonatomic, readonly) uint32_t otaSent;

/// 设备交互回调代理
@property(weak, nonatomic) id<JL_OTAManagerDelegate> delegate;

/// 获取 OTA 升级对象
+ (JL_OTAManager *)getOTAManager;

/// 不建议使用自行初始化
/// 推荐获取 getOTAManager
- (instancetype)init __attribute__((deprecated("Please use getOTAManager instead.")));

/// 打印OTA发送的数据内容
/// - Parameter status: 开关
- (void)logSendData:(BOOL)status;

/// 当BLE连接上时告知SDK
- (void)noteEntityConnected;

/// 当BLE断开时告知SDK
- (void)noteEntityDisconnected;

/// 设置最大丢包次数
/// - Parameter count: 次数
/// default: 10
- (void)maxLostCount:(int)count;

/// 设置超时时间
/// - Parameter timeOut: 时间
/// default: 5
- (void)cmdTimeOut:(int)timeOut;

/// 设置是否需要回连
/// 一般不允许外部干扰状态机，外部不适用此方法
/// - Parameter isReLink: 回连
- (void)setOTARelink:(BOOL)isReLink __attribute__((deprecated("Can't be used externally.")));

/// Receive data from rcsp
/// 设备端过来的数据
/// - Parameter data: data
- (void)cmdOtaDataReceive:(NSData *)data;

/// 查询设备OTA信息
/// 所有情况下都需要执行，而且是在连上后（认证完成）第一步执行
- (void)cmdTargetFeature;

/// 查询设备系统状态
/// 当设备需要挂载外置flash才能正常升级时需要执行，其他情况则无需执行
- (void)cmdSystemFunction;

/// OTA单备份，是否正在回连
- (BOOL)cmdOtaIsRelinking;

#pragma mark---> OTA升级
/**
 开始OTA升级
 @param data 升级数据
 @param result 升级结果
 */
- (void)cmdOTAData:(NSData *)data
            Result:(JL_OTA_RT __nullable)result;

/// OTA升级II
/// 单备份升级特有！！！！
/// 此接口可用于 OTA 回连成功后，再次发起升级使用
/// @param result 升级结果回调
- (void)cmdOtaDataIIResult:(JL_OTA_RT __nullable)result;

/// OTA升级III
/// 单备份升级特有！！！
/// 此接口免去了公版 OTA 的外边回连策略，内部实现回连
/// ⚠️使用此方法时不可使用 delegate 的回调信息，要使用 Result 的回调信息
/// @param data OTA数据
/// @param option 回连选项
/// @param result 回复
-(void)cmdUpgrade:(NSData *)data Option:(JLOtaReConnectOption *_Nullable)option Result:(JL_OTA_RT _Nonnull)result;

/**
 OTA升级取消
 @param result 回复
 */
- (void)cmdOTACancelResult:(JL_OTA_RESULT __nullable)result;

/// 重启设备
- (void)cmdRebootDevice;

/// 强制重启设备
- (void)cmdRebootForceDevice;

/// 重置OTA manager
- (void)resetOTAManager;

/// 打印OTA SDK版本
+ (NSString *)logSDKVersion;

@end

NS_ASSUME_NONNULL_END
