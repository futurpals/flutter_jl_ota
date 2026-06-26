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

typedef NS_ENUM(NSUInteger, JLTranslateSetResultType) {
    JLTranslateSetResultTypeSuccess = 0x00,
    JLTranslateSetResultTypeSameMode = 0x01,
    JLTranslateSetResultTypeParamErr = 0x02,
    JLTranslateSetResultTypeCall = 0x03,
    JLTranslateSetResultTypeAudioPlaying = 0x04,
    JLTranslateSetResultTypeBusy = 0x05,
    JLTranslateSetResultTypeFail = 0x06
};

@protocol JLTranslateSetDelegate <NSObject>

-(void)translateNotifyMode:(JLTranslateSetMode *)mode;

-(void)translateReceiveAudioMode:(JLTranslateAudio *)mode;

/// - Parameters:
-(void)translateNoteCacheInfo:(JLTranslateAudioSourceType)sourceType cacheSize:(uint32_t)cacheSize;

@end



typedef void(^JLTranslateGetModeInfoBlock)(JLTranslateSetMode *_Nullable mode,JL_CMDStatus status);

typedef void(^JLTranslateSetModeBlock)(JLTranslateSetResultType type,JL_CMDStatus status);

typedef void(^JLTranslateGetCacheInfoBlock)(JL_CMDStatus status,JLTranslateAudioSourceType sourceType,uint32_t cacheSize);

@interface JLTranslateSet : ECOneToMorePtl

@property(nonatomic, assign)NSTimeInterval cmdMaxTime;

/// - Parameters:
-(void)cmdGetModeInfo:(JL_ManagerM *)manager
               Result:(JLTranslateGetModeInfoBlock)result;

/// - Parameters:
-(void)cmdSetMode:(JLTranslateSetMode *)mode
          Manager:(JL_ManagerM *)manager
           Result:(JLTranslateSetModeBlock)result;


/// - Parameters:
-(void)cmdCheckCache:(JL_ManagerM *)manager SourceType:(JLTranslateAudioSourceType) type Result:(JLTranslateGetCacheInfoBlock)result;

/// - Parameters:
-(void)cmdNoteMode:(JLTranslateSetMode *)mode
           Manager:(JL_ManagerM *)manager;

/// - Parameters:
-(void)cmdPushAudioMode:(JLTranslateAudio *)audio
                Manager:(JL_ManagerM *)manager;


@end

NS_ASSUME_NONNULL_END
