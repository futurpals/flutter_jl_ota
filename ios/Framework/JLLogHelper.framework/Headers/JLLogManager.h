//
//  JLLogManager.h
//  JLLogHelper
//
//  Created by EzioChan on 2024/5/8.
//  Copyright © 2024 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#define kJLLog(level,fmt...) [JLLogManager logLevel:level funcName:__FUNCTION__ line:__LINE__ format:fmt]

typedef NS_ENUM(NSInteger, JLLOG_LEVEL) {
    JLLOG_COMPLETE  = 0,
    JLLOG_DEBUG     = 1,
    JLLOG_INFO      = 2,
    JLLOG_WARN      = 3,
    JLLOG_ERROR     = 4,
};

@interface JLLogManager : NSObject

+(void)sdkVersion;

+(void)clearLog;

/**
 */
+(void)openLogTextFile;

+(void)redirectLogPath:(NSString *)path;

+(void)collectLog:(void(^)(NSString *log))block;

+(void)logWithTimestamp:(BOOL)isTimeStamp;

+(void)saveLogAsFile:(BOOL)isSave;

+(void)setLog:(BOOL)enable IsMore:(BOOL)isMore Level:(JLLOG_LEVEL)level;

+(void)logLevel:(JLLOG_LEVEL)level funcName:(const char* _Nullable)func line:(const int)line format:(NSString * _Nonnull)format,...;

+(void)logSomething:(NSString *)something;

+(void)logLevel:(JLLOG_LEVEL)level content:(NSString *)content;

+(void)saveLog:(NSString *)logContent;

@end

NS_ASSUME_NONNULL_END
