//
//  JLTranslateAudio.h
//  JL_BLEKit
//
//  Created by EzioChan on 2024/12/31.
//  Copyright © 2024 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JLModel_SPEEX.h"

NS_ASSUME_NONNULL_BEGIN

/// 音频类型
typedef NS_ENUM(NSUInteger, JLTranslateAudioSourceType) {
    /// 音频文件
    JLTranslateAudioTypeFile = 0,
    /// 设备麦克风
    JLTranslateAudioTypeDeviceMic = 1,
    /// 手机麦克风
    JLTranslateAudioTypePhoneMic = 2,
    /// eSCO上行
    JLTranslateAudioTypeESCOUp = 3,
    /// eSCO下行
    JLTranslateAudioTypeESCODown = 4,
    /// A2DP
    JLTranslateAudioTypeA2DP = 5
};

/// 翻译音频
@interface JLTranslateAudio : NSObject <NSCopying>

/// 来源类型
@property (assign, nonatomic) JLTranslateAudioSourceType sourceType;

/// 音频数据类型
@property (assign, nonatomic) JL_SpeakDataType audioType;

/// 包计数,倒序，0 为结束包
@property (assign, nonatomic) int count;

/// 音频数据的CRC
@property (assign, nonatomic) uint16_t crc;

/// 数据长度
@property (assign, nonatomic) int len;

/// 音频数据
@property (strong, nonatomic) NSData *data;

+(JLTranslateAudio *)beObjc:(NSData *)data;

-(NSData *)toData;



@end

NS_ASSUME_NONNULL_END
