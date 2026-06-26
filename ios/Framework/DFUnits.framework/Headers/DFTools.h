//
//  DFTools.h
//  DFUnits
//
//  Created by DFung on 16/1/22.
//

#import <Foundation/Foundation.h>


@interface DFTools : NSObject

/**
 *  NSString to NSMutableData
 *  
 *  @"ffff0000" => <ffff 0000>
 *
 */
+(NSMutableData*)HexToData:(NSString*)hex;

/**
 *  NSData to NSString
 *
 *  <ffff 0000> => @"ffff0000"
 *
 */
+(NSString*)dataToHex:(NSData*)data;

/**
 *  Alignment data in length you like.
 */
+(NSData*)alignment:(NSData*)data length:(NSInteger)len;

/**
 *  NSData ==> NSDictory.
 */
+(id)jsonWithData:(NSData*)data;

/**
 *  NSDictory ==> NSString.
 */
+(NSString*)dictionaryToJson:(NSDictionary *)dic;

/**
 *  NSDictory ==> NSData.
 */
+(NSData*)makeDataByDictionary:(NSDictionary *)dic;

/**
 *  NSData ==> NSDictory.
 */
+(NSDictionary*)makeDictionaryByData:(NSData *)data;

/**
 *  NSArray ==> NSString.
 */
+(NSString*)arrayToJson:(NSArray *)array;

/**
 */
+(NSData*)uInt32_data:(uint32_t)value;

/**
 */
+(NSData*)uInt32_data:(uint32_t)value Endian:(BOOL)endian;

/**
 */
+(NSData*)uInt16_data:(uint16_t)value;

/**
 */
+(NSData*)uInt16_data:(uint16_t)value Endian:(BOOL)endian;

+(NSData*)uInt8_data:(uint8_t)value;

/**
 *  <000f> => <0f00>
 *
 */
+(NSData*)changeBigOrSmall:(NSData*)data;

/**
 *
 *  <000f> => 16
 *
 */
+(NSInteger)dataToInt:(NSData*)data;

/**
 */
+(int)getNaturalNumber:(NSData*)aByte;

/**
 */
+(NSData*)data:(NSData*)data R:(NSInteger)index L:(NSInteger)length;

/**
 */
+(NSString*)string:(NSData*)data Encode:(NSStringEncoding)encoding;

/**
 */
+(NSString*)string:(NSArray*)array;


/**
 */
+(NSString*)stringUnicode:(NSData*)data;

/**
 */
+(NSString*)stringANSI:(NSData*)data;

/**
 */
+(NSString*)stringGBK:(NSData*)data;

/**
 */
+(void)setUser:(id)objc forKey:(NSString*)key;

/**
 */
+(id)getUserByKey:(NSString*)key;

/**
 */
+(void)removeUserByKey:(NSString*)key;


@end
