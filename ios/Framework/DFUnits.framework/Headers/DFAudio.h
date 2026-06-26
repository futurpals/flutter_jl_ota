//
//  DFAudio.h
//  DFUnits
//
//  Created by DFung on 16/1/22.
//


/**
 */

#import <Foundation/Foundation.h>
#import <AudioUnit/AudioUnit.h>
#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVFoundation.h>

#include <stdio.h>
#include <stdlib.h>

/**
 */
#define kDFAudio_ST     @"NOTE_DFAUDIO_ST"

/**
 */
#define kDFAudio_PG     @"NOTE_DFAUDIO_PG"

/**
 */
#define kDFAudio_REC    @"NOTE_DFAUDIO_REC"

typedef enum : NSUInteger {
    DFAudio_ST_STOP,
    DFAudio_ST_PLAYING,
    DFAudio_ST_PENDING,
    DFAudio_ST_RECORDING,
} DFAudio_ST;

struct DF_Data
{
    int              size;
    unsigned char    *data;
};

@class DFAudioFormat;
@interface DFAudio : NSObject

#pragma mark - Vendor SDK
/**
 */
-(void)setPlayerBufferSize:(int32_t)size
                    Format:(DFAudioFormat*)format;
/**
 */
-(void)didPlayerInputBuffer:(NSData*)data;

/**
 PCM。

 */
-(uint32_t)didRingUsable;

/**
 */
-(void)didPlayerStart;

/**
 */
-(void)didPlayerStop;

/**
 */
-(void)didPlayerRelease;


#pragma mark - Vendor SDK
/**
 */
-(void)setRecorderFormat:(DFAudioFormat*)format;

/**
 */
-(void)didRecorderStart;

/**
 */
-(void)didRecorderStop;

/**
 */
-(void)didRecorderFinished;

/**
 */
-(void)didRecorderRelease;



#pragma mark - Vendor SDK
/**
 */
+(NSString*)wavToPcm:(NSString*)wavPath;

/**
 */
+(NSString*)pcmToWav:(NSString*)pcmPath Format:(DFAudioFormat*)format;

#pragma mark - Vendor SDK
+(void)setPcmFormat:(DFAudioFormat *)format;

#pragma mark - Vendor SDK
+(double)checkPcmDB:(NSData*)pcmData;


#pragma mark super vad
/**
 *  return
 *  --> 0 : vad prepare.
 *  --> 1 : vad start.
 *  --> 2 : vad end.
 */
+(int)vadPcm:(NSData*)pcm MinDB:(float)db;

#pragma mark super vad + path
/**
 *  return
 *  --> 0 : vad prepare.
 *  --> 1 : vad start.
 */
+(int)vadPcm:(NSData*)pcm MinDB:(float)db Path:(NSString*)path;

/**
 *  clean vad cache
 */
+(void)vadClean;

@end


@interface DFAudioFormat : NSObject
@property(nonatomic,assign)Float64 mSampleRate;
@property(nonatomic,assign)UInt32  mBitsPerChannel;
@property(nonatomic,assign)UInt32  mChannelsPerFrame;
@property(nonatomic,assign)AudioFormatID mFormatID;

@end



