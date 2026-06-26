//
//  JLSpdifPCManager.h
//  JL_BLEKit
//
//  Created by EzioChan on 2024/10/15.
//  Copyright © 2024 www.zh-jieli.com. All rights reserved.
//

#import <JL_BLEKit/ECOneToMorePtl.h>
#import <JL_BLEKit/JLModelSpdif.h>
#import <JL_BLEKit/JLModelPCServer.h>
#import <JL_BLEKit/JL_ManagerM.h>

NS_ASSUME_NONNULL_BEGIN

@protocol JLSpdifPCProtocol <NSObject>

/// 更新 SPDIF 模式
/// - Parameter spdifModel: SPDIF 模式
-(void)updateSpdifModel:(JLModelSpdif *)spdifModel;

/// 更新 PC 从者模式
/// - Parameter pcServerModel: PC Server
-(void)updatePcServerModel:(JLModelPCServer *)pcServerModel;

@end

/// SPDIF 与 PC 从者模式管理
@interface JLSpdifPCManager : ECOneToMorePtl

/// SPDIF 模式信息
@property(nonatomic,strong)JLModelSpdif *spdifModel;

/// PC 从者模式信息
@property(nonatomic,strong)JLModelPCServer *pcServerModel;


/// 获取 SPDIF 模式的状态
/// - Parameter manager: 设备对象
/// - Parameter callBack: 回调
-(void)getSpdifStatus:(JL_ManagerM *)manager callBack:(JL_CMD_RESPOND)callBack;

/// 获取 PC 从者模式的状态
/// - Parameter manager: 设备对象
/// - Parameter callBack: 回调
-(void)getPcServerStatus:(JL_ManagerM *)manager callBack: (JL_CMD_RESPOND)callBack;

/// 设置 SPDIF 模式的播放状态
/// - Parameter status: 播放状态
/// - Parameter manager: 设备对象
/// - Parameter callBack: 回调
-(void)setSpdifPlayStatus:(BOOL)status Manager:(JL_ManagerM *)manager callBack:(JL_CMD_RESPOND)callBack;

/// 设置 SPDIF 模式音源
/// - Parameter type: 音源类型
/// - Parameter manager: 设备对象
/// - Parameter callBack: 回调
-(void)setSpdifAction:(JLSpdifAudioType)type Manager:(JL_ManagerM *)manager callBack:(JL_CMD_RESPOND)callBack;

/// 设置 PC 从者模式的播放状态
/// - Parameter status: 播放状态
/// - Parameter manager: 设备对象
/// - Parameter callBack: 回调
-(void)setPcServerPlayStatus:(BOOL)status Manager:(JL_ManagerM *)manager callBack:(JL_CMD_RESPOND)callBack;

/// 设置 PC 从者模式的操作类型
/// - Parameter type: 操作类型
/// - Parameter manager: 设备对象
/// - Parameter callBack: 回调
-(void)setPcServerAction:(JLPcServerOpType)type Manager:(JL_ManagerM *)manager callBack:(JL_CMD_RESPOND)callBack;

@end

NS_ASSUME_NONNULL_END
