//
//  JLLogManager.h
//  JLLogHelper
//
//  Created by EzioChan on 2024/5/8.
//  Copyright © 2024 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 打印宏
#define kJLLog(level,fmt...) [JLLogManager logLevel:level funcName:__FUNCTION__ line:__LINE__ format:fmt]

typedef NS_ENUM(NSInteger, JLLOG_LEVEL) {
    JLLOG_COMPLETE  = 0,
    JLLOG_DEBUG     = 1,
    JLLOG_INFO      = 2,
    JLLOG_WARN      = 3,
    JLLOG_ERROR     = 4,
};

/// 日志打印
@interface JLLogManager : NSObject

/// 打印SDK版本
+(void)sdkVersion;

///清理已存储的打印
+(void)clearLog;

/**
 *    打印文本
 */
+(void)openLogTextFile;

///重定向保存日志文件路径设置
/// @param path 路径
+(void)redirectLogPath:(NSString *)path;

/// 收集日志回调接口
/// @param block 回调
+(void)collectLog:(void(^)(NSString *log))block;

/// 打印时间
/// @param isTimeStamp 是否打印 default is false
+(void)logWithTimestamp:(BOOL)isTimeStamp;

/// 把日志保存存储起来
/// @param isSave 是否保存 default is yes
+(void)saveLogAsFile:(BOOL)isSave;

///LOG使能与等级，默认开启且debug等级。
/// @param enable LOG使能
/// @param isMore 是否打印【函数名&行号】
/// @param level   LOG等级
+(void)setLog:(BOOL)enable IsMore:(BOOL)isMore Level:(JLLOG_LEVEL)level;

/// 打印函数
/// @param level     LOG等级
/// @param func       函数名
/// @param line       行号
/// @param format   内容
+(void)logLevel:(JLLOG_LEVEL)level funcName:(const char* _Nullable)func line:(const int)line format:(NSString * _Nonnull)format,...;

/// 打印
/// @param something 任意字符串内容
+(void)logSomething:(NSString *)something;

/// 打印
/// @param level    LOG等级
/// @param content   内容
+(void)logLevel:(JLLOG_LEVEL)level content:(NSString *)content;

/// 保存日志信息到文件中
/// @param logContent 日志内容
+(void)saveLog:(NSString *)logContent;

@end

NS_ASSUME_NONNULL_END
