//
//  JL_SpeexManager.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/12/17.
//  Modify By EzioChan on 2023/03/27.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JL_Tools.h>
#import <JL_BLEKit/JLModel_SPEEX.h>

NS_ASSUME_NONNULL_BEGIN

@class JL_ManagerM;
@class JL_SpeexManager;

/// 录音状态代理处理
@protocol JL_SpeexManagerDelegate <NSObject>
/// 录音数据回调
/// - Parameters:
///   - manager: 操作设备
///   - data: 数据
-(void)speexManager:(JL_SpeexManager *)manager Audio:(NSData *)data;

/// 设备端开始录音
/// - Parameters:
///   - manager: 操作设备
///   - param: 录音参数
-(void)speexManager:(JL_SpeexManager *) manager StartByDeviceWithParam:(JLRecordParams *)param;

/// 设备端结束录音
/// - Parameters:
///   - manager: 操作设备
///   - param: 语音助手配置参数
-(void)speexManager:(JL_SpeexManager *) manager StopByDeviceWithParam:(JLSpeechRecognition *)param;

/// 录音状态回调
/// - Parameters:
///   - manager: 操作设备
///   - status: 状态
-(void)speexManager:(JL_SpeexManager *)manager Status:(JL_SpeakType)status;

@optional
/// 录音状态回调
/// - Parameters:
///   - manager: 操作设备
///   - status: 录音状态
///   - originator: 状态变更发起端
///   当发起者是Device时，才会具备params的参数，其中结束录音时，params的属性仅有mVadWay为可使用内容
///   - params: 录音参数
-(void)speexManager:(JL_SpeexManager *)manager Status:(JL_SpeakType)status By:(JLCMDOriginator)originator With:(JLRecordParams *_Nullable) params __attribute__((deprecated("Use several other callbacks to implement callback methods")));
@end

/// 设备录音管理对象
@interface JL_SpeexManager : NSObject

//MARK: - Sync Android Interface

@property(nonatomic,weak)id<JL_SpeexManagerDelegate> delegate;

-(instancetype)init __attribute__((unavailable("Use +shareSpeexManager:WithManager: instead.")));


/// 获取单例
/// - Parameters:
///   - delegate: 代理
///   - manager: 操作设备
+(JL_SpeexManager *)shareSpeexManager:(id<JL_SpeexManagerDelegate>) delegate WithManager:(JL_ManagerM *)manager;


/// 获取录音状态
-(JL_SpeakType)cmdCheckRecordStatus;



/// 开始录音
/// - Parameters:
///   - manager: 操作设备
///   - params: 录音参数
///   - result: 命令操作结果回调
-(void)cmdStartRecord:(JL_ManagerM *)manager Params:(JLRecordParams *)params Result:(JL_CMD_RESPOND __nullable)result;


/// 停止录音
/// - Parameters:
///   - manager: 操作设备
///   - reason: VAD类型
///   - result: 命令操作结果回调
-(void)cmdStopRecord:(JL_ManagerM *)manager Reason:(JLSpeakDownReason) reason Result:(JL_CMD_RESPOND __nullable)result;

/// 停止录音2
/// - Parameters:
///   - manager: 操作设备
///   - reason: vad类型
///   - schr: 语音设置助手
///   - result: 回调结果
-(void)cmdStopRecord:(JL_ManagerM *)manager Reason:(JLSpeakDownReason)reason SpeechHelper:(JLSpeechRecognition *)schr Result:(JL_CMD_RESPOND __nullable)result;


/// 发送命令给音箱，允许音箱端开始接收语音，音箱收到这个消息后会发一个提示音
/// 当前命令用于收到设备主动发起的录音时，同意开始录音。
/// 即在 speexManagerStatus:(JL_SpeakType)status By:(JLCMDOriginator)originator With:(JLRecordParams *_Nullable) params 的代理回调收到之后的回复处理
-(void)cmdAllowSpeak;


/// 拒绝录音
/// 发送命令给音箱，不允许接收语音
/// 当前命令用于收到设备主动发起的录音时，拒绝开始录音。
/// 即在 speexManagerStatus:(JL_SpeakType)status By:(JLCMDOriginator)originator With:(JLRecordParams *_Nullable) params 的代理回调收到之后的回复处理
-(void)cmdRejectSpeak;

/** 停止语音
 发发送命令给音箱，停止接收数据，即检测到断句
 */
-(void)cmdSpeakingDone __attribute__((deprecated ( "当前命令已失效，请使用cmdStopRecord:(JL_ManagerM *)manager Reason:(JLSpeakDownReason) reason")));



@end

NS_ASSUME_NONNULL_END
