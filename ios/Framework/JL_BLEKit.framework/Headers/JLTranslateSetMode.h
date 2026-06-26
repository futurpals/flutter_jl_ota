//
//  JLTranslateSetMode.h
//  JL_BLEKit
//
//  Created by EzioChan on 2024/12/31.
//  Copyright © 2024 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JLModel_SPEEX.h"

NS_ASSUME_NONNULL_BEGIN

/// 翻译模式
typedef NS_ENUM(NSUInteger, JLTranslateSetModeType) {
    /// 空闲
    JLTranslateSetModeTypeIdle = 0x00,
    /// 仅录音
    JLTranslateSetModeTypeOnlyRecord = 0x01,
    /// 录音翻译
    JLTranslateSetModeTypeRecordTranslate = 0x02,
    /// 通话翻译
    JLTranslateSetModeTypeCallTranslate = 0x03,
    /// 音频翻译
    JLTranslateSetModeTypeAudioTranslate = 0x04,
    /// 面对面翻译
    JLTranslateSetModeTypeFaceToFaceTranslate = 0x05
};

/// 录音策略
typedef NS_ENUM(NSInteger, JLTranslateRecordType) {
    /// 手机端录音
    JLTranslateRecordByPhone = 0x00,
    /// 设备录音
    JLTranslateRecordByDevice = 0x01
};

/// 翻译模式
@interface JLTranslateSetMode : NSObject

/// 翻译模式
/// default is JLTranslateSetModeTypeIdle
@property (nonatomic, assign) JLTranslateSetModeType modeType;

/// 音频数据类型
/// default is JL_SpeakDataTypeOPUS
@property (nonatomic, assign) JL_SpeakDataType dataType;

/// 声道
/// 默认是1
@property (nonatomic, assign) NSInteger channel;

/// 采样率
/// 默认是16000
@property (nonatomic, assign) NSInteger sampleRate;

+(JLTranslateSetMode *)beObjc:(NSData *)data;

-(NSData *)toData;

@end

NS_ASSUME_NONNULL_END
