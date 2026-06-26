//
//  JLTranslationManager.h
//  JL_BLEKit
//
//  Created by EzioChan on 2025/1/3.
//  Copyright © 2025 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JLTranslateAudio.h"
#import "JLModel_SPEEX.h"
#import "JLTranslateSetMode.h"
#import "JLTranslateSet.h"

NS_ASSUME_NONNULL_BEGIN

@class JL_ManagerM;

/// 翻译回调
@protocol JLTranslationManagerDelegate <NSObject>

/// 初始化成功
/// @param uuid 设备UUID
-(void)onInitSuccess:(NSString *)uuid;

/// 模式改变
/// @param uuid 设备UUID
/// @param mode 翻译模式
-(void)onModeChange:(NSString *)uuid Mode:(JLTranslateSetMode *)mode;

/// 音频数据
/// @param uuid 设备UUID
/// @param data 音频数据
-(void)onReceiveAudioData:(NSString *)uuid AudioData:(JLTranslateAudio *)data;

/// 错误
/// @param uuid 设备UUID
/// @param err 错误
-(void)onError:(NSString *)uuid Error:(NSError *) err;

@optional

/// 通话状态
/// @param isCalling 是否在通话
/// @param uuid 设备UUID
-(void)isOnCalling:(BOOL)isCalling UUID:(NSString *)uuid;


/// 音频队列结束(或空闲/已结束/中间传输时短暂的播空了）
/// @param uuid 设备UUID
-(void)onSendAudioQueueOver:(NSString *)uuid;

@end

typedef void(^JLTranslationManagerGetBlock)(JLTranslateSetMode *_Nullable mode,NSError *_Nullable err);

typedef void(^JLTranslationManagerSetBlock)(JLTranslateSetResultType status,NSError *_Nullable err);

/// 翻译传输管理对象
/// Translation transmission management object
@interface JLTranslationManager : NSObject

/// 代理
@property (nonatomic, weak) id<JLTranslationManagerDelegate> delegate;

/// 命令最大超时时间
/// 默认是 10s
/// Command maximum timeout time
/// Default is 10s
@property (nonatomic, assign) NSTimeInterval cmdMaxTimeOut;



/// 设备蓝牙 UUID
/// Device Bluetooth UUID
@property (nonatomic, strong, readonly) NSString *uuid;

/// 当前的翻译模式
/// Current translation mode
@property (nonatomic, strong, readonly) JLTranslateSetMode *translateMode;

/// 录音策略，默认是手机端录音
/// Recording policy, the default is to record on the phone
@property (nonatomic, assign) JLTranslateRecordType recordtype;

/// 是否在通话中
/// Whether in a call
@property (nonatomic, assign) BOOL isCalling;

/// 设备对象
/// Device object
@property (nonatomic, strong, readonly) JL_ManagerM *manager;

/// 初始化
/// init
/// - Parameters:
///   - delegate: 代理 JLTranslationManagerDelegate
///   - manager: 设备对象 DeviceManager
///   - result: 回调
- (instancetype)initWithDelegate:(id<JLTranslationManagerDelegate>)delegate Manager:(JL_ManagerM *)manager Result:(void(^)(BOOL success, NSError *_Nullable err))result;

/// 是否支持翻译功能
/// Does it support translation function
- (BOOL)trIsSupportTranslate;

/// 是否通过 a2dp 播放
/// Is it played through a2dp
- (BOOL)trIsPlayWithA2dp;


/// 是否正在工作
/// Is it working
- (BOOL)trIsWorking;

/// 获取当前翻译模式
/// Get the current translation mode
/// 回复的内容通过 JLTranslationManagerDelegate 代理回调
/// Reply content through JLTranslationManagerDelegate delegate
/// - Parameter block: 回调
- (void)trGetCurrentTranslationMode:(JLTranslationManagerGetBlock _Nullable)block;

/// 开始翻译模式
/// Start translation mode
/// - Parameter mode: 翻译模式 translation mode
/// - Parameter block: 回调
- (void)trStartTranslateMode:(JLTranslateSetMode *)mode Block:(JLTranslationManagerSetBlock _Nullable)block;

/// 退出翻译模式
/// Exit translation mode
/// - Parameter block: 回调
- (void)trExitMode:(JLTranslationManagerSetBlock _Nullable)block;

/// 写入翻译音频,翻译完/操作完后的音频需要携带原音频的音频类型 JLTranslateAudio 进行回复
/// Write in translation audio, translation complete/operation complete audio need to carry the original audio JLTranslateAudio reply
/// - Parameters:
///   - audio: JLTranslateAudio 原返回音频类型
///   - audioData: 处理完的音频数据
- (void)trWriteAudio:(JLTranslateAudio *)audio TranslateData:(NSData *)audioData;

-(void)trWriteAudioV2:(JLTranslateAudio *)audio TranslateData:(NSData *)audioData;

-(void)trSendIsRelay;

/// 销毁
/// Destroy
/// 如果销毁，需要重新生成对象，此对象的回调将会失效
/// Destroy, if it is destroyed, the callback of this object will be invalidated
- (void)trDestory;

@end

NS_ASSUME_NONNULL_END
