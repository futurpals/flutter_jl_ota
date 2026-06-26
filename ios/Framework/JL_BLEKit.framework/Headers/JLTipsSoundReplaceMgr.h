//
//  JLTipsSoundReplay.h
//  JL_BLEKit
//
//  Created by EzioChan on 2025/5/14.
//  Copyright © 2025 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_BLEKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef void(^JLTipsVoiceBlock)(JL_CMDStatus,NSData *_Nullable info);

/// 提示音替换
@interface JLTipsSoundReplaceMgr : NSObject

/// 单例
+(instancetype)share;

/// 是否处于替换中
-(BOOL)isReplacing;

/// 是否支持提示音替换查询
/// - Parameters:
///   - manager: 设备
///   - result: 回调结果
-(void)isSupportTipsVoiceReplace:(JL_ManagerM *)manager result:(JLConfigTwsRsp)result;

/// 获取设备端提示音的信息
/// - Parameters:
///   - manager: 设备
///   - result: 回调
-(void)voicesReplaceGetVoiceInfo:(JL_ManagerM *)manager Result:(JLTipsVoiceBlock)result;

/// 推送提示音数据到设备
/// - Parameters:
///   - mgr: 设备
///   - devhandle: 设备句柄，当前句柄需要通过获取设备存储信息获得，可参考 JLModel_Device 类的 cardInfo 属性，当设备不作要求时，此值填 0xffffffff
///   - path: 提示音本地存放路径
///   - isReborn: 完成后是否重启设备
///   - result: 回调结果
-(void)voicesReplacePushDataRequest:(JL_ManagerM *)mgr DevHandle:(NSData *)devhandle TonePath:(NSString *)path IsReborn:(BOOL)isReborn Result:(JL_BIGFILE_RT __nullable)result;

@end

NS_ASSUME_NONNULL_END
