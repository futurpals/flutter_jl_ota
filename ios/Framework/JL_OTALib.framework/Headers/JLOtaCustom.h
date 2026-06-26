//
//  JLOtaCustom.h
//  JL_OTALib
//
//  Created by EzioChan on 2025/4/17.
//  Copyright © 2025 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
@class JL_OTAManager;

/// 自定义命令对象
@interface JLOtaCustomData : NSObject

/// 是否需要回复
@property (nonatomic, assign) BOOL needResponse;

/// 数据
@property (nonatomic, strong) NSData *data;

/// 回复数据 SN
@property (nonatomic, assign) uint8_t sn;

@end


/// 自定义命令回调
@protocol JLOtaCustomDelegate <NSObject>

/// 自定义命令回调
/// - Parameter data: 自定义命令对象
-(void)otaCustomReceiveData:(JLOtaCustomData *)data;

@end

/// 自定义命令
@interface JLOtaCustom : NSObject

/// 自定义命令
/// - Parameters:
///   - delegate: 代理回调
///   - manager: 升级对象
-(instancetype)initWithDelegate:(id<JLOtaCustomDelegate>)delegate OtaManager:(JL_OTAManager *)manager;

/// 发送自定义命令
/// - Parameters:
///   - data: 下发的数据
///   - need: 是否需要回复内容
///   - result: 命令回复结果
- (void)cmdSendCommandData:(NSData *)data needResponse:(BOOL)need Result:(void(^)(NSData * __nullable response, NSError * __nullable error)) result;

/// 回复自定义命令
/// - Parameters:
///   - data: 回复的数据
///   - sn: 回复的SN
- (void)cmdResponseData:(NSData *)data sn:(uint8_t)sn;

@end

NS_ASSUME_NONNULL_END
