//
//  JL_BLEMultiple.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2020/9/1.
//  Copyright © 2020 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <UIKit/UIKit.h>

#import <JL_BLEKit/JL_EntityM.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  BLE状态通知
 */
extern NSString *kJL_BLE_M_FOUND;               //发现设备
extern NSString *kJL_BLE_M_FOUND_SINGLE;        //发现单个设备
extern NSString *kJL_BLE_M_ENTITY_CONNECTED;    //连接有更新
extern NSString *kJL_BLE_M_ENTITY_DISCONNECTED; //断开连接
extern NSString *kJL_BLE_M_ON;                  //BLE开启
extern NSString *kJL_BLE_M_OFF;                 //BLE关闭
extern NSString *kJL_BLE_M_EDR_CHANGE;          //经典蓝牙输出通道变化
extern NSString *kJL_BLE_M_SAVE_BLEADDR;        //存储EDR地址
extern NSString *kJL_BLE_M_ANCS_UPDATE;         //设备ANCS权限变更


@interface JL_BLEMultiple : NSObject
@property (strong, nonatomic) NSData   *__nullable filterKey;         //过滤码
@property (strong, nonatomic) NSData   *__nullable pairKey;           //配对码
@property (assign, nonatomic) BOOL                 BLE_IS_CONNECTING; //是否有设备正在连接
@property (assign, nonatomic) BOOL                 BLE_FILTER_ENABLE; //是否【开启过滤】
@property (assign, nonatomic) BOOL                 BLE_PAIR_ENABLE;   //是否【开启配对】
@property (assign, nonatomic) int                  BLE_TIMEOUT;       //连接超时时间

@property (strong, nonatomic) NSMutableArray<JL_EntityM *> *blePeripheralArr;   //发现的设备
@property (strong, nonatomic) NSArray<CBPeripheral *> *bleAttDevices;      //ATT发现的设备
@property (strong, nonatomic) NSMutableArray<JL_EntityM *> *bleConnectedArr;    //已连接的设备
@property (assign, nonatomic) CBManagerState                bleManagerState;    //蓝牙状态
@property (strong, nonatomic) NSArray<NSNumber *> *__nullable bleDeviceTypeArr;   //选择的设备类型<@(JL_DeviceType)>
@property (strong, nonatomic) NSArray<NSNumber *> *__nullable managerClassArr;    //实例化的业务逻辑<@(JL_CLASS)>


@property (strong, nonatomic) NSString             *JL_BLE_SERVICE;   //服务号
@property (strong, nonatomic) NSString             *JL_BLE_RCSP_W;    //命令【写】通道
@property (strong, nonatomic) NSString             *JL_BLE_RCSP_R;    //命令【读】通道

+(NSString*)versionOfSDK;

/**
 开始搜索
 */
-(void)scanStart;

/**
 继续搜索
 */
-(void)scanContinue;

/**
 停止搜索
 */
-(void)scanStop;


/// 蓝牙中心管理器
-(CBCentralManager *)getCenterManaer;

/**
 通过UUID生成Entity。
 */
-(JL_EntityM *_Nullable)makeEntityWithUUID:(NSString*)uuid;

/// 通过UUID获得一个已连接过的entity
/// @param uuid uuid
/// @param status 获取后是否继续蓝牙搜索
/// @param result 结果
-(void)getEntityWithSearchUUID:(NSString *)uuid SearchStatus:(BOOL)status Result:(void(^)(JL_EntityM *_Nullable entity))result;
/**
 连接设备
 @param entity 蓝牙设备类
 */
-(void)connectEntity:(JL_EntityM*)entity Result:(JL_EntityM_STATUS_BK)result;


/// 根据设备 ADV 广播报中的 Mac 连接设备
/// ADV 的数据格式必须满足 JL 设备的标准 TWS 系列的数据结构
/// @param advMac 广播报中的蓝牙地址
/// 一般是指 EDR 地址，当然开发者也可以跟固件端协商，采取其他的地址，但是要求数据结构不变
/// @param result 回调
-(void)connectEntityWithAdvMac:(NSString *)advMac Result:(JL_EntityM_STATUS_BK) result;

/// 根据设备Mac去回连
/// @param mac Mac地址
/// @param result 回调
-(void)connectEntityForMac:(NSString *)mac Result:(JL_EntityM_STATUS_BK)result;

/**
 断开连接
 */
-(void)disconnectEntity:(JL_EntityM*)entity Result:(JL_EntityM_STATUS_BK)result;

/**
 更新名字信息
*/
-(void)updateHistoryRename:(NSString*)name withUuid:(NSString*)uuid;

/// 清除历史记录
/// 删除后，可能会导致使用历史纪录回连时，信息为空
/// 一般是在删除了绑定设备后使用
-(void)cleanHistoryDeviceCache;

/// 获取当前正在连接的entity
-(JL_EntityM *__nullable)connectingEntity;

/**
 返回经典蓝牙信息
 @return @{@"ADDRESS":@"7c9a1da7330e",
           @"TYPE"   :@"BluetoothA2DPOutput",
           @"NAME"   :@"earphone"}
 */
+(NSDictionary*)outputEdrInfo;

/**
 返回经典蓝牙edr列表
 @return 蓝牙edr列表
 */
+(NSArray<NSString *>*)outputEdrList;


#pragma mark - ota升级
/**
 *  ota升级功能
 *  @param mBleEntityM 当前ota升级的蓝牙设备（JL_EntityM）
 *  @param otaFilePath ota升级文件路径
 *  @param result ota升级过程回调
 */
- (void)otaFuncWithEntityM:(JL_EntityM *)mBleEntityM
              withFilePath:(NSString *)otaFilePath
                    Result:(JL_OTA_RT __nullable)result;
- (void)setOtaReconnectBleAddr:(NSString* __nullable)addr;

@end

NS_ASSUME_NONNULL_END
