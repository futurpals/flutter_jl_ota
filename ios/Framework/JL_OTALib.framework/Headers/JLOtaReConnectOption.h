//
//  JLOtaReConnectOption.h
//  JL_OTALib
//
//  Created by EzioChan on 2025/3/27.
//  Copyright © 2025 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface JLOtaReConnectOption : NSObject

/// 是否需要使用设备认证
@property (assign, nonatomic) BOOL deviceAuthorize;

/// 握手(配对)秘钥
@property(strong,nonatomic)NSData *__nullable authKey;

/// 设备服务UUID
/// 默认是 AE00
@property (strong, nonatomic) NSString *serviceUUID;

///写特征 UUID
/// 默认是 AE01
@property (strong, nonatomic) NSString *writeUUID;

/// 读特征 UUID
/// 默认是 AE02
@property (strong, nonatomic) NSString *readUUID;

/// 是否需要响应的回应方式
/// 默认是NO
@property (assign, nonatomic) BOOL isWriteWithResponse;



+ (JLOtaReConnectOption *)defaultOption;

@end

NS_ASSUME_NONNULL_END
