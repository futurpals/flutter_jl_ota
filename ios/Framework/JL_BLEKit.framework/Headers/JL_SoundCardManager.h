//
//  JL_SoundCardManager.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/12/20.
//  Modify by EzioChan on 2023/09/25.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JL_Tools.h>

NS_ASSUME_NONNULL_BEGIN


typedef NS_ENUM(uint8_t, JL_KalaoIndex) {
    JL_KalaoIndexReverberation  = 0,
    JL_KalaoIndexDelayed        = 1,
    JL_KalaoIndexVolume         = 2,
};

@class JL_ManagerM;

@interface JLSoundCardIndexValue : NSObject

@property (assign,nonatomic)uint8_t index;

@property (assign,nonatomic)uint16_t value;

@end

@protocol JLSoundCardMgrDelegate <NSObject>

/// - Parameters:
-(void)jlsoundCardMask:(uint64_t)mask values:(NSArray <JLSoundCardIndexValue *> *)items;

-(void)jlsoundCardMicFrequency:(NSArray*)frequencyArray;

-(void)jlsoundCardMicEQ:(NSArray*)eqArray;

@end


@interface JL_SoundCardManager : NSObject

@property (assign,nonatomic)long index;

@property (assign,nonatomic)long value;

@property (assign,nonatomic)uint64_t mask;

@property (strong,nonatomic)NSArray <JLSoundCardIndexValue *>* iVitems;

@property (strong,nonatomic)NSArray *micFrequencyArray;

@property (strong,nonatomic)NSArray *micEQArray;

@property (weak,nonatomic)id<JLSoundCardMgrDelegate> delegate;

/// - Parameters:
///  - value:  0-100
-(void)cmdSetKalaok:(JL_ManagerM *)manager Index:(JL_KalaoIndex)index Value:(uint16_t)value result:(JL_CMD_RESPOND)result;

/// - Parameters:
-(void)cmdSetKaraoke:(JL_ManagerM *)manager micEQ:(NSArray*)array result:(JL_CMD_RESPOND)result;

@end

NS_ASSUME_NONNULL_END
