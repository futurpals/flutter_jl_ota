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

@protocol JLTranslationManagerDelegate <NSObject>

-(void)onInitSuccess:(NSString *)uuid;

-(void)onModeChange:(NSString *)uuid Mode:(JLTranslateSetMode *)mode;

-(void)onReceiveAudioData:(NSString *)uuid AudioData:(JLTranslateAudio *)data;

-(void)onError:(NSString *)uuid Error:(NSError *) err;

@optional

-(void)isOnCalling:(BOOL)isCalling UUID:(NSString *)uuid;


-(void)onSendAudioQueueOver:(NSString *)uuid;

@end

typedef void(^JLTranslationManagerGetBlock)(JLTranslateSetMode *_Nullable mode,NSError *_Nullable err);

typedef void(^JLTranslationManagerSetBlock)(JLTranslateSetResultType status,NSError *_Nullable err);

/// Translation transmission management object
@interface JLTranslationManager : NSObject

@property (nonatomic, weak) id<JLTranslationManagerDelegate> delegate;

/// Command maximum timeout time
/// Default is 10s
@property (nonatomic, assign) NSTimeInterval cmdMaxTimeOut;



/// Device Bluetooth UUID
@property (nonatomic, strong, readonly) NSString *uuid;

/// Current translation mode
@property (nonatomic, strong, readonly) JLTranslateSetMode *translateMode;

/// Recording policy, the default is to record on the phone
@property (nonatomic, assign) JLTranslateRecordType recordtype;

/// Whether in a call
@property (nonatomic, assign) BOOL isCalling;

/// Device object
@property (nonatomic, strong, readonly) JL_ManagerM *manager;

/// init
/// - Parameters:
- (instancetype)initWithDelegate:(id<JLTranslationManagerDelegate>)delegate Manager:(JL_ManagerM *)manager Result:(void(^)(BOOL success, NSError *_Nullable err))result;

/// Does it support translation function
- (BOOL)trIsSupportTranslate;

/// Is it played through a2dp
- (BOOL)trIsPlayWithA2dp;


/// Is it working
- (BOOL)trIsWorking;

/// Get the current translation mode
/// Reply content through JLTranslationManagerDelegate delegate
- (void)trGetCurrentTranslationMode:(JLTranslationManagerGetBlock _Nullable)block;

/// Start translation mode
- (void)trStartTranslateMode:(JLTranslateSetMode *)mode Block:(JLTranslationManagerSetBlock _Nullable)block;

/// Exit translation mode
- (void)trExitMode:(JLTranslationManagerSetBlock _Nullable)block;

/// Write in translation audio, translation complete/operation complete audio need to carry the original audio JLTranslateAudio reply
/// - Parameters:
- (void)trWriteAudio:(JLTranslateAudio *)audio TranslateData:(NSData *)audioData;

-(void)trWriteAudioV2:(JLTranslateAudio *)audio TranslateData:(NSData *)audioData;

-(void)trSendIsRelay;

/// Destroy
/// Destroy, if it is destroyed, the callback of this object will be invalidated
- (void)trDestory;

@end

NS_ASSUME_NONNULL_END
