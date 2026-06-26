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
    JLPcServerOpTypePrevious = 0x00,
    /// next song
    JLPcServerOpTypeNext = 0x01,
};

@interface JLModelPCServer : NSObject

@property(nonatomic,assign)BOOL playStatus;

@property(nonatomic,assign)JLPcServerOpType opType;

-(instancetype)initParseData:(NSData *)data;

- (void)updateParseData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
