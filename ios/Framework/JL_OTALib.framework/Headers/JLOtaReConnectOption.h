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

@property (assign, nonatomic) BOOL deviceAuthorize;

@property(strong,nonatomic)NSData *__nullable authKey;

@property (strong, nonatomic) NSString *serviceUUID;

@property (strong, nonatomic) NSString *writeUUID;

@property (strong, nonatomic) NSString *readUUID;

@property (assign, nonatomic) BOOL isWriteWithResponse;



+ (JLOtaReConnectOption *)defaultOption;

@end

NS_ASSUME_NONNULL_END
