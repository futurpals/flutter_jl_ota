//
//  NSData+ToUnit.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/4/7.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSData (ToUnit)


-(BOOL)beBool;

-(uint8_t)beUint8;

-(UInt16)beLittleUint16;

-(UInt16)beBigendUint16;

-(UInt32)beLittleUint32;

-(UInt32)beBigendUint32;

-(UInt64)beLittleUint64;

-(UInt64)beBigendUint64;

-(NSString *)dataToAltitude;

-(NSString *)beHexStr;

-(NSDate *)toDate;

-(NSData *)subf:(NSInteger)from t:(NSInteger)to;

-(uint16_t)crc:(uint16_t)baseCrc;

@end


@interface NSMutableData(WithUnit)

-(void)appendUint8:(uint8_t)k;

-(void)appendUint16:(uint16_t)k;

-(void)appendUint32:(uint32_t)k;
@end


@interface NSString(WithUnit)

-(NSString *)formatLog;

@end

NS_ASSUME_NONNULL_END
