//
//  JLModelPCServer.h
//  JL_BLEKit
//
//  Created by EzioChan on 2024/10/15.
//  Copyright © 2024 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, JLPcServerOpType) {
    /// previous song
    /// 上一首
    JLPcServerOpTypePrevious = 0x00,
    /// next song
    /// 下一首
    JLPcServerOpTypeNext = 0x01,
};

/// PC 从机模式
@interface JLModelPCServer : NSObject

/// 是否正在播放
@property(nonatomic,assign)BOOL playStatus;

/// 操作类型
@property(nonatomic,assign)JLPcServerOpType opType;

-(instancetype)initParseData:(NSData *)data;

/// 更新
/// - Parameter data: 数据
- (void)updateParseData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
