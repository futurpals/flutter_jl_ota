//
//  JLFlashOpMgr.h
//  JL_BLEKit
//
//  Created by EzioChan on 2025/3/14.
//  Copyright © 2025 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_BLEKit.h>

NS_ASSUME_NONNULL_BEGIN

/// 表盘操作类型
typedef NS_ENUM(NSUInteger, FlashDialOperationType) {
    ///< 读取当前表盘
    FlashDialOperationTypeReadCurrent = 0,
    ///< 设置表盘
    FlashDialOperationTypeSet,
    ///< 通知表盘
    FlashDialOperationTypeNotify,
    ///< 获取表盘额外信息
    FlashDialOperationTypeGetExtraInfo,
    ///< 激活自定义表盘（设置表盘背景）
    FlashDialOperationTypeActivateCustom,
    ///< 获取表盘背景
    FlashDialOperationTypeGetBackground,
    /// 通知表盘背景变更
    FlashDialOperationTypeNoteBackground
};

/// 设备 Flash 操作
@interface JLFlashOpMgr : NSObject

/// 超时
@property(nonatomic, assign)NSInteger timeOutMax;

/// 获取Flash信息
/// - Parameters:
///   - managerM: 蓝牙管理对象
///   - result: 回调
-(void)flashGetInfoMode:(JL_ManagerM *)managerM
                 Result:(void (^)(JLModel_Flash *_Nullable model, NSError *_Nullable error))result;
/// 写数据
/// @param managerM 蓝牙管理器
/// @param offset 偏移
/// @param data 写入数据
/// @param isLast 是否是最后一次
/// @param result 回调
- (void)flashWriteData:(JL_ManagerM *)managerM
                Offset:(uint32_t)offset
                  Data:(NSData*)data
                isLast:(BOOL)isLast
                Result:(void (^)(BOOL success, NSError *error))result;
/// 插入文件
/// @param managerM 蓝牙管理器
/// @param fileName 文件名称
/// @param fileSize 文件大小
/// @param isLast 是否是最后一次
/// @param result 回调
- (void)flashInsertFile:(JL_ManagerM *)managerM
               fileName:(NSString *)fileName
               fileSize:(uint32_t)fileSize
                 isLast:(BOOL)isLast
                 Result:(void (^)(BOOL, NSError * _Nullable error))result;
/// 操作表盘
/// @param managerM 蓝牙管理器
/// @param type 操作类型
/// @param filePath 文件路径
/// @param result 回调
- (void)flashDialOperation:(JL_ManagerM *)managerM
                      type:(FlashDialOperationType)type
                  filePath:(nullable NSString *)filePath
                    result:(void (^)(BOOL success, NSData *_Nullable response, NSError *_Nullable error))result;
/// 擦除数据
/// @param managerM 蓝牙管理器
/// @param offset 偏移
/// @param clusterSize 簇大小
/// @param result 回调
- (void)flashEraseData:(JL_ManagerM *)managerM
                Offset:(uint32_t)offset
           ClusterSize:(uint16_t)clusterSize
                Result:(void (^)(BOOL success, NSError *_Nullable error))result;

/// 删除文件
/// @param managerM 蓝牙管理器
/// @param filePath 文件路径
/// @param isStart 是否是最后一次
/// @param result 回调
- (void)flashDeleteFile:(JL_ManagerM *)managerM
               FilePath:(nullable NSString *)filePath
                isStart:(BOOL)isStart
                 Result:(void (^)(BOOL success, NSError *_Nullable error))result;
/// 写保护
/// @param managerM 蓝牙管理器
/// @param isEnable 是否启用
/// @param result 回调
- (void)flashWriteProtect:(JL_ManagerM *)managerM
                 isEnable:(BOOL)isEnable
                   Result:(void (^)(BOOL success, NSError *_Nullable error))result;
/// 更新表盘标记
/// @param managerM 蓝牙管理器
/// @param isStart 是否开启
/// @param result 回调
- (void)flashUpdateWatchFace:(JL_ManagerM *)managerM
                     isStart:(BOOL)isStart
                      Result:(void (^)(BOOL success, NSError *_Nullable error))result;
/// 查询写入是否成功 版本 0
/// @param managerM 蓝牙管理器
/// @param crc16 crc
/// @param result 回调
- (void)flashCheckWriteSuccessV0:(JL_ManagerM *)managerM
                          crc16:(uint16_t)crc16
                         Result:(void (^)(BOOL success, NSError *_Nullable error))result;

/// 查询写入是否成功 版本 1
/// @param managerM 蓝牙管理器
/// @param crc16 crc
/// @param isSplit 是否分包
/// @param result 回调
- (void)flashCheckWriteSuccessV1:(JL_ManagerM *)managerM
                           crc16:(uint16_t)crc16
                         isSplit:(BOOL)isSplit
                          Result:(void (^)(BOOL success, uint16_t leftSize, NSError *_Nullable error))result;
/// 设置升级资源标志
/// @param managerM 蓝牙管理器
/// @param flag flag 0-2
/// flag 0：结束
/// flag 1：开始
/// flag 2：特殊升级流程开启
/// @param result 回调
- (void)flashSetUpgradeFlag:(JL_ManagerM *)managerM
                       flag:(uint8_t)flag
                     result:(void (^)(BOOL success, NSError *_Nullable error))result;
/// 获取文件信息
/// @param managerM 蓝牙管理器
/// @param filePath 文件路径
/// @param result 回调
- (void)flashGetFileInfo:(JL_ManagerM *)managerM
                filePath:(NSString *)filePath
                  result:(void (^)(uint32_t size, uint16_t crc16, NSError *_Nullable error))result;

/// 获取 Flash 剩余空间
/// @param managerM 蓝牙管理器
/// @param result 回调
- (void)flashGetRemainingSpace:(JL_ManagerM *)managerM
                        result:(void (^)(uint32_t clusterLeftNum, NSError *_Nullable error))result;
/// 还原系统
/// @param managerM 蓝牙管理器
/// @param result 回调
- (void)flashRestoreSystem:(JL_ManagerM *)managerM
                    result:(void (^)(BOOL success, NSError *_Nullable error))result;

/// 获取资源存储空间
/// @param managerM 蓝牙管理器
/// @param result 回调
- (void)flashGetResourceSpace:(JL_ManagerM *)managerM
                       result:(void (^)(uint32_t resSpace, NSError *_Nullable error))result;

@end


NS_ASSUME_NONNULL_END
