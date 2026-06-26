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

typedef NS_ENUM(NSUInteger, JLTranslateSetModeType) {
    JLTranslateSetModeTypeIdle = 0x00,
    JLTranslateSetModeTypeOnlyRecord = 0x01,
    JLTranslateSetModeTypeRecordTranslate = 0x02,
    JLTranslateSetModeTypeCallTranslate = 0x03,
    JLTranslateSetModeTypeAudioTranslate = 0x04,
    JLTranslateSetModeTypeFaceToFaceTranslate = 0x05
};

typedef NS_ENUM(NSInteger, JLTranslateRecordType) {
    JLTranslateRecordByPhone = 0x00,
    JLTranslateRecordByDevice = 0x01
};

@interface JLTranslateSetMode : NSObject

/// default is JLTranslateSetModeTypeIdle
@property (nonatomic, assign) JLTranslateSetModeType modeType;

/// default is JL_SpeakDataTypeOPUS
@property (nonatomic, assign) JL_SpeakDataType dataType;

@property (nonatomic, assign) NSInteger channel;

@property (nonatomic, assign) NSInteger sampleRate;

+(JLTranslateSetMode *)beObjc:(NSData *)data;

-(NSData *)toData;

@end

NS_ASSUME_NONNULL_END
