//
//  JLModel_SPEEX.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/10/15.
//  Modify By EzioChan on 2023/03/27.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_TypeEnum.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_SpeakType) {
    JL_SpeakTypeDo                  = 0,
    JL_SpeakTypeDone                = 1,
    JL_SpeakTypeDoing               = 2,
    JL_SpeakTypeDoneFail            = 0x0f,
};
typedef NS_ENUM(UInt8, JL_SpeakDataType) {
    JL_SpeakDataTypePCM             = 0,
    JL_SpeakDataTypeSPEEX           = 1,
    JL_SpeakDataTypeOPUS            = 2,
    JL_SpeakDataTypeMSBC            = 3,
    JL_SpeakDataTypeJLA_V2          = 4,    //JLA_V2
};

typedef NS_ENUM(UInt8, JLSpeakDownReason) {
    JLSpeakDownNormal = 0x00,
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
@property(assign,nonatomic)uint8_t          mVad;
@end


@interface JLSpeechRecognition:NSObject

@property(assign,nonatomic)BOOL sendText;

@property(assign,nonatomic)BOOL sendAIText;

@property(assign,nonatomic)BOOL needPlayTTS;

+(JLSpeechRecognition *)beObjc:(NSData *)data;

-(NSData *)beData;

@end


@interface JLRecordParams : NSObject

@property(nonatomic,assign)JL_SpeakDataType mDataType;

@property(assign,nonatomic)JLSpeakDownReason mVadWay;

@property(assign,nonatomic)JLRecordSampleRate mSampleRate;

@property(strong,nonatomic)JLSpeechRecognition *speechRecognit;

@end


@interface JLSpeechAiCloud : NSObject

@property(nonatomic,assign)uint8_t version;

@property(nonatomic,assign)uint8_t type;

@property(nonatomic,assign)uint8_t vendorID;

@property(nonatomic,assign)uint16_t lenght;

@property(nonatomic,strong)NSData *playload;

+(JLSpeechAiCloud *)beObject:(NSData *)data;

-(NSData *)beData;

@end

@interface JLSpeechTTSSynthesis : NSObject

@property(nonatomic,assign)uint8_t version;

@property(nonatomic,assign)uint16_t lenght;

@property(nonatomic,strong)NSData *playload;

-(NSData *)beData;

+(JLSpeechTTSSynthesis *)beObject:(NSData *)data;
@end

NS_ASSUME_NONNULL_END
