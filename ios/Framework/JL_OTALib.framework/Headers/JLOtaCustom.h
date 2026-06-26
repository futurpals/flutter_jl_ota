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

@interface JLOtaCustomData : NSObject

@property (nonatomic, assign) BOOL needResponse;

@property (nonatomic, strong) NSData *data;

@property (nonatomic, assign) uint8_t sn;

@end


@protocol JLOtaCustomDelegate <NSObject>

-(void)otaCustomReceiveData:(JLOtaCustomData *)data;

@end

@interface JLOtaCustom : NSObject

/// - Parameters:
-(instancetype)initWithDelegate:(id<JLOtaCustomDelegate>)delegate OtaManager:(JL_OTAManager *)manager;

/// - Parameters:
- (void)cmdSendCommandData:(NSData *)data needResponse:(BOOL)need Result:(void(^)(NSData * __nullable response, NSError * __nullable error)) result;

/// - Parameters:
- (void)cmdResponseData:(NSData *)data sn:(uint8_t)sn;

@end

NS_ASSUME_NONNULL_END
