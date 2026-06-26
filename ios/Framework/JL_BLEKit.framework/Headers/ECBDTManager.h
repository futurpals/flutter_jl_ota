//
//  ECBDTManager.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/11/20.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <JL_BLEKit/JL_BLEKit.h>

NS_ASSUME_NONNULL_BEGIN

@class JL_ManagerM;

@protocol ECBDTManagerProtocol <NSObject>

/// - Parameters:
-(void)ecBDTManagerError:(JL_ManagerM *)manager Type:(uint8_t) type  Error:(NSError *)error;

/// - Parameters:
-(void)ecBDTManager:(JL_ManagerM *)manager Type:(uint8_t) type GetBigData:(NSData *)data Progress:(float) progress;

/// - Parameters:
-(void)ecBDTManager:(JL_ManagerM *)manager Type:(uint8_t) type  FinishBigData:(NSString *)saveFilePath;


@optional

/// - Parameters:
-(void)ecBDTManager:(JL_ManagerM *)manager SendBigDataPresent:(float )progress Finish:(BOOL)finish;

/// - Parameters:
-(void)ecBDTManager:(JL_ManagerM *)manager StartBigData:(ECBDTWriteReq *)req Type:(uint8_t) type;


/// -(void)responseDev:(JL_ManagerM *)manager resp:(ECBDTReadReq *)req Data:(NSData *)data
/// - Parameters:
-(void)ecBDTManager:(JL_ManagerM *)manager ReadBigData:(ECBDTReadReq *)req Type:(uint8_t) type;

-(void)ecBDTManagerSendFinish:(JL_ManagerM *)manager  Type:(uint8_t) type;

@end

@interface ECBDTManager : ECOneToMorePtl

+(instancetype)share;

/// - Parameters:
-(void)readData:(JL_ManagerM *)manager Type:(uint8_t)type;

/// - Parameters:
-(void)writeData:(JL_ManagerM *)manager Type:(uint8_t) type Data:(NSData*)data;

/// -(void)ecBDTManager:(JL_ManagerM *)manager ReadBigData:(ECBDTReadReq *)req
/// - Parameters:
-(void)responseDev:(JL_ManagerM *)manager resp:(ECBDTReadReq *)req Data:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
