//
//  JL_SpeexManager.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/12/17.
//  Modify By EzioChan on 2023/03/27.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JL_Tools.h>
#import <JL_BLEKit/JLModel_SPEEX.h>

NS_ASSUME_NONNULL_BEGIN

@class JL_ManagerM;
@class JL_SpeexManager;

@protocol JL_SpeexManagerDelegate <NSObject>
/// - Parameters:
-(void)speexManager:(JL_SpeexManager *)manager Audio:(NSData *)data;

/// - Parameters:
-(void)speexManager:(JL_SpeexManager *) manager StartByDeviceWithParam:(JLRecordParams *)param;

/// - Parameters:
-(void)speexManager:(JL_SpeexManager *) manager StopByDeviceWithParam:(JLSpeechRecognition *)param;

/// - Parameters:
-(void)speexManager:(JL_SpeexManager *)manager Status:(JL_SpeakType)status;

@optional
/// - Parameters:
-(void)speexManager:(JL_SpeexManager *)manager Status:(JL_SpeakType)status By:(JLCMDOriginator)originator With:(JLRecordParams *_Nullable) params __attribute__((deprecated("Use several other callbacks to implement callback methods")));
@end

@interface JL_SpeexManager : NSObject

//MARK: - Sync Android Interface

@property(nonatomic,weak)id<JL_SpeexManagerDelegate> delegate;

-(instancetype)init __attribute__((unavailable("Use +shareSpeexManager:WithManager: instead.")));


/// - Parameters:
+(JL_SpeexManager *)shareSpeexManager:(id<JL_SpeexManagerDelegate>) delegate WithManager:(JL_ManagerM *)manager;


-(JL_SpeakType)cmdCheckRecordStatus;



/// - Parameters:
-(void)cmdStartRecord:(JL_ManagerM *)manager Params:(JLRecordParams *)params Result:(JL_CMD_RESPOND __nullable)result;


/// - Parameters:
-(void)cmdStopRecord:(JL_ManagerM *)manager Reason:(JLSpeakDownReason) reason Result:(JL_CMD_RESPOND __nullable)result;

/// - Parameters:
-(void)cmdStopRecord:(JL_ManagerM *)manager Reason:(JLSpeakDownReason)reason SpeechHelper:(JLSpeechRecognition *)schr Result:(JL_CMD_RESPOND __nullable)result;


-(void)cmdAllowSpeak;


-(void)cmdRejectSpeak;

/**
 ，，
 */
-(void)cmdSpeakingDone __attribute__((deprecated ( "，cmdStopRecord:(JL_ManagerM *)manager Reason:(JLSpeakDownReason) reason")));



@end

NS_ASSUME_NONNULL_END
