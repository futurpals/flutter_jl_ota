//
//  ECBDTObjc.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/11/21.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ECBDTObjc : NSObject

@end

@interface ECBDTBasic : NSObject
@property (nonatomic, assign) uint8_t op;

@property (nonatomic, assign) uint8_t way;

@property (nonatomic, assign) uint8_t type;

@property (nonatomic, assign) uint8_t version;

@property (nonatomic, copy)NSData *paramData;

-(instancetype)initData:(NSData *)data;

@end



@interface ECBDTReadResp : ECBDTBasic
@property (nonatomic, assign) uint8_t result;

@property (nonatomic, assign) uint32_t dtLen;

@property (nonatomic, assign) uint16_t crc;

@property (nonatomic, assign) uint16_t sendMtu;

@property (nonatomic, assign) uint16_t receiveMtu;

@end

@interface ECBDTWriteResp : ECBDTBasic
@property (nonatomic, assign) uint8_t result;

@property (nonatomic, assign) uint16_t sendMtu;

@property (nonatomic, assign) uint16_t receiveMtu;

@end


@interface ECBDTReadReq: ECBDTBasic

@property (nonatomic, assign) uint16_t sendMtu;

@property (nonatomic, assign) uint16_t receiveMtu;

@end


@interface ECBDTWriteReq : ECBDTBasic

@property (nonatomic, assign) uint32_t dtLen;

@property (nonatomic, assign) uint16_t crc;

@property (nonatomic, assign) uint16_t sendMtu;

@property (nonatomic, assign) uint16_t receiveMtu;

@end


@interface ECBDTCmdData : NSObject<NSCopying>
@property (nonatomic, assign) uint8_t type;


@property (nonatomic, assign) BOOL isEnd;

@property (nonatomic, assign) uint32_t seq;

/// crc
@property (nonatomic, assign) uint16_t crc;

@property (nonatomic, assign) uint32_t offset;

@property (nonatomic, assign) uint16_t len;

@property (nonatomic, copy)NSData *data;


-(instancetype)initData:(NSData *)data;

-(NSData *)beData;

/// - Parameters:
+(NSArray<ECBDTCmdData *>*)makeWithMtu:(uint16_t)mtu Type:(uint8_t) type Data:(NSData *)dt;

@end


NS_ASSUME_NONNULL_END
