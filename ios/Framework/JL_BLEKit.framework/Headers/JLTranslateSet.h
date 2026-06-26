//
//  JLTranslateSet.h
//  JL_BLEKit
//
//  Created by EzioChan on 2024/12/31.
//  Copyright © 2024 www.zh-jieli.com. All rights reserved.
//

#import <JL_BLEKit/ECOneToMorePtl.h>
#import <JL_BLEKit/JLTranslateAudio.h>

NS_ASSUME_NONNULL_BEGIN
@class JLTranslateSetMode;

/// 翻译设置结果
typedef NS_ENUM(NSUInteger, JLTranslateSetResultType) {
    /// 成功
    JLTranslateSetResultTypeSuccess = 0x00,
    /// 模式相同
    JLTranslateSetResultTypeSameMode = 0x01,
    /// 参数错误
    JLTranslateSetResultTypeParamErr = 0x02,
    /// 通话中
    JLTranslateSetResultTypeCall = 0x03,
    /// 音频播放中
    JLTranslateSetResultTypeAudioPlaying = 0x04,
    /// 系统繁忙
    JLTranslateSetResultTypeBusy = 0x05,
    /// 操作失败
    JLTranslateSetResultTypeFail = 0x06
};

@protocol JLTranslateSetDelegate <NSObject>

/// 翻译模式通知
/// - Parameter mode: 翻译模式
-(void)translateNotifyMode:(JLTranslateSetMode *)mode;

/// 翻译音频通知
/// - Parameter mode: 翻译音频
-(void)translateReceiveAudioMode:(JLTranslateAudio *)mode;

/// 翻译缓存
/// - Parameters:
///   - sourceType: 来源类型
///   - cacheSize: 剩余缓存大小
-(void)translateNoteCacheInfo:(JLTranslateAudioSourceType)sourceType cacheSize:(uint32_t)cacheSize;

@end



typedef void(^JLTranslateGetModeInfoBlock)(JLTranslateSetMode *_Nullable mode,JL_CMDStatus status);

typedef void(^JLTranslateSetModeBlock)(JLTranslateSetResultType type,JL_CMDStatus status);

typedef void(^JLTranslateGetCacheInfoBlock)(JL_CMDStatus status,JLTranslateAudioSourceType sourceType,uint32_t cacheSize);

/// 翻译交互 API
@interface JLTranslateSet : ECOneToMorePtl

@property(nonatomic, assign)NSTimeInterval cmdMaxTime;

/// 获取翻译模式
/// - Parameters:
///   - manager: 设备对象
///   - result: 结果回调
-(void)cmdGetModeInfo:(JL_ManagerM *)manager
               Result:(JLTranslateGetModeInfoBlock)result;

/// 设置翻译模式
/// - Parameters:
///   - mode: 模式
///   - manager: 设备
///   - result: 结果
-(void)cmdSetMode:(JLTranslateSetMode *)mode
          Manager:(JL_ManagerM *)manager
           Result:(JLTranslateSetModeBlock)result;


/// 获取设备可用缓存
/// - Parameters:
///   - manager: 设备
///   - type: 来源类型
///   - result: 结果
-(void)cmdCheckCache:(JL_ManagerM *)manager SourceType:(JLTranslateAudioSourceType) type Result:(JLTranslateGetCacheInfoBlock)result;

/// 通知翻译模式
/// - Parameters:
///   - mode: 模式
///   - manager: 设备
-(void)cmdNoteMode:(JLTranslateSetMode *)mode
           Manager:(JL_ManagerM *)manager;

/// 推送翻译音频
/// - Parameters:
///   - audio: 音频
///   - manager: 设备
-(void)cmdPushAudioMode:(JLTranslateAudio *)audio
                Manager:(JL_ManagerM *)manager;


@end

NS_ASSUME_NONNULL_END
