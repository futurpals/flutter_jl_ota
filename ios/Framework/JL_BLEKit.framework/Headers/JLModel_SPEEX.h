//
//  JLModel_SPEEX.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/10/15.
//  Modify By EzioChan on 2023/03/27.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_TypeEnum.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_SpeakType) {
    JL_SpeakTypeDo                  = 0,    //开始录音
    JL_SpeakTypeDone                = 1,    //结束录音
    JL_SpeakTypeDoing               = 2,    //正在录音
    JL_SpeakTypeDoneFail            = 0x0f, //结束失败
};
typedef NS_ENUM(UInt8, JL_SpeakDataType) {
    JL_SpeakDataTypePCM             = 0,    //PCM数据
    JL_SpeakDataTypeSPEEX           = 1,    //SPEEX数据
    JL_SpeakDataTypeOPUS            = 2,    //OPUS数据
    JL_SpeakDataTypeMSBC            = 3,    //MSBC数据
    JL_SpeakDataTypeJLA_V2          = 4,    //JLA_V2
};

/// 结束原因
typedef NS_ENUM(UInt8, JLSpeakDownReason) {
    ///正常
    JLSpeakDownNormal = 0x00,
    ///取消
    JLSpeakDownByDevice = 0x01
};

/// SampleRate
typedef NS_ENUM(UInt8, JLRecordSampleRate) {
    ///8000
    JLRecordSampleRate8K = 0x08,
    ///16000
    JLRecordSampleRate16K = 0x10
};






@interface JLModel_SPEEX : NSObject
@property(assign,nonatomic)JL_SpeakType     mSpeakType;
@property(assign,nonatomic)JL_SpeakDataType mDataType;
@property(assign,nonatomic)JLSpeakDownReason mDownReason;
@property(assign,nonatomic)uint8_t          mSampleRate;            //0x08=8k，0x10=16k
@property(assign,nonatomic)uint8_t          mVad;                   //断句方: 0:固件 1:APP
@end


///语音助手配置参数
@interface JLSpeechRecognition:NSObject

///是否下发识别文本，0：否 1：是
@property(assign,nonatomic)BOOL sendText;

/// 是否下发AI文本，0：否 1：是
@property(assign,nonatomic)BOOL sendAIText;

/// 是否播放AI TTS语音，0：否 1：是
@property(assign,nonatomic)BOOL needPlayTTS;

+(JLSpeechRecognition *)beObjc:(NSData *)data;

-(NSData *)beData;

@end


/// 录音参数对象
@interface JLRecordParams : NSObject

/// 音频类型
@property(nonatomic,assign)JL_SpeakDataType mDataType;

/// VAD方式
@property(assign,nonatomic)JLSpeakDownReason mVadWay;

/// 采样率
@property(assign,nonatomic)JLRecordSampleRate mSampleRate;

/// 语音助手配置参数
@property(strong,nonatomic)JLSpeechRecognition *speechRecognit;

@end


/// speech 语音：AI云数据格式
@interface JLSpeechAiCloud : NSObject

/// 版本信息
@property(nonatomic,assign)uint8_t version;

/// 文本类型
/// 0 ： 手表本地文本(语音识别)
/// 1 ： AI应答文本
/// 2 ： 错误提示文本
@property(nonatomic,assign)uint8_t type;

/// 供应商
/// 0 ： 杰理
/// 1 ： 科大讯飞
@property(nonatomic,assign)uint8_t vendorID;

/// 有效数据长度
@property(nonatomic,assign)uint16_t lenght;

/// 数据内容
@property(nonatomic,strong)NSData *playload;

+(JLSpeechAiCloud *)beObject:(NSData *)data;

-(NSData *)beData;

@end

/// TTS语音合成数据格式
@interface JLSpeechTTSSynthesis : NSObject

/// 版本信息
@property(nonatomic,assign)uint8_t version;

/// 有效数据长度
@property(nonatomic,assign)uint16_t lenght;

/// 数据内容
@property(nonatomic,strong)NSData *playload;

-(NSData *)beData;

+(JLSpeechTTSSynthesis *)beObject:(NSData *)data;
@end

NS_ASSUME_NONNULL_END
