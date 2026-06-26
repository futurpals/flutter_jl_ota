//
//  JL_SpeechAIttsHandler.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/7/22.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JLModel_SPEEX.h>
#import <JL_BLEKit/JL_BigDataManager.h>

NS_ASSUME_NONNULL_BEGIN

@class JL_ManagerM;
@protocol JL_SpeechAIttsHandlerDelegate <NSObject>

/// - Parameters:
-(void)receiveDataFrom:(JL_ManagerM *)manager WithAiCloud:(JLSpeechAiCloud *)aicloud;

/// - Parameters:
-(void)receiveDataFrom:(JL_ManagerM *)manager WithTTS:(JLSpeechTTSSynthesis *)tts;

@end

@interface JL_SpeechAIttsHandler : NSObject

@property(nonatomic,weak)id<JL_SpeechAIttsHandlerDelegate> delegate;


/// - Parameter mgr: JL_ManagerM
- (instancetype)initWithMgr:(JL_ManagerM *)mgr;

/// - Parameters:
-(void)speechSendTTs:(JLSpeechTTSSynthesis *)tts manager:(JL_ManagerM *)manager result:(JL_BIGDATA_RT)result;

/// - Parameters:
-(void)speechSendAiCloud:(JLSpeechAiCloud *)cloud manager:(JL_ManagerM *)manager result:(JL_BIGDATA_RT)result;

@end

NS_ASSUME_NONNULL_END
