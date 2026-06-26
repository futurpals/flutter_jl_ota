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

typedef NS_ENUM(NSUInteger, JLTranslateAudioSourceType) {
    JLTranslateAudioTypeFile = 0,
    JLTranslateAudioTypeDeviceMic = 1,
    JLTranslateAudioTypePhoneMic = 2,
    JLTranslateAudioTypeESCOUp = 3,
    JLTranslateAudioTypeESCODown = 4,
    /// A2DP
    JLTranslateAudioTypeA2DP = 5
};

@interface JLTranslateAudio : NSObject <NSCopying>

@property (assign, nonatomic) JLTranslateAudioSourceType sourceType;

@property (assign, nonatomic) JL_SpeakDataType audioType;

@property (assign, nonatomic) int count;

@property (assign, nonatomic) uint16_t crc;

@property (assign, nonatomic) int len;

@property (strong, nonatomic) NSData *data;

+(JLTranslateAudio *)beObjc:(NSData *)data;

-(NSData *)toData;



@end

NS_ASSUME_NONNULL_END
