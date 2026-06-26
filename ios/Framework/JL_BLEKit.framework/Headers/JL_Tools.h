//
//  JL_Tools.h
//  JL_BLEKit
//
//  Created by zhihui liang on 2018/11/9.
//  Copyright © 2018 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/NSObject+JLTools.h>
#import <JLLogHelper/JLLogHelper.h>

NS_ASSUME_NONNULL_BEGIN
typedef void(^JL_Action)(void);
typedef void(^JL_Timer_BK)(void);

@class JL_Timer;
@interface JL_Tools : NSObject


/**
 Data。
 
 */
+(NSData*)data:(NSData*)data R:(NSInteger)index L:(NSInteger)length;
+(NSDictionary*)dictionaryData:(NSData*)data R:(NSInteger)index L:(NSInteger)length;

/**
 NSData  10
 
 */
+(NSInteger)dataToInt:(NSData*)data;

/**
 NSData  NSString
 
 */
+(NSString*)dataChangeToString:(NSData*)data;

/**
 uint8_t  NSData
 
 */
+(NSData*)uInt8_data:(uint8_t)value;

/**
 uint16_t  NSData
 
 */
+(NSData*)uInt16_data:(uint16_t)value Endian:(BOOL)endian;

/**
 uint32_t  NSData
 
 */
+(NSData*)uInt32_data:(uint32_t)value Endian:(BOOL)endian;

/**
 uint64_t  NSData
 
 */
+(NSData*)uInt64_data:(uint64_t)value Endian:(BOOL)endian;

/**
 int64_t  NSData
 
 */
+(NSData*)int64_data:(int64_t)value Endian:(BOOL)endian;

/**

 */
+(NSData*)changeBigOrSmall:(NSData*)data;

/**
 @"ffff0000"  <ffff 0000>，16NSData。
 
 */
+(NSMutableData*)HexToData:(NSString*)hex;
/**
 */
+(NSData*)cleanEOF:(NSData*)data;
/**
 ：aByte ==> -2 -1 0 1 2 3...
 */
+(int)getNaturalNumber:(NSData*)aByte;
+(int)getNaturalNumber_u16:(NSData*)u16Bytes;
+(int)getNaturalNumber_u32:(NSData*)u32Bytes;

/**
 
 */
+(void)post:(NSString*)name Object:(id __nullable)object;

/**
 
 */
+(void)post:(NSString*)name Object:(id __nullable)object UserInfo:(NSDictionary* __nullable)info;
/**
 
 */
+(void)add:(NSString*__nullable)name Action:(SEL)action Own:(id)own;

/**
 
 */
+(void)remove:(NSString*__nullable)name Own:(id)own;

/**
 NSUserDefault（：）。
 
 */
+(void)setUser:(id)objc forKey:(NSString*)key;

/**
 NSUserDefault（：）。
 
 */
+(id _Nullable)getUserByKey:(NSString*)key;

/**
 NSUserDefault
 
 */
+(void)removeUserByKey:(NSString*)key;


/**
 block。
 
 */
+(void)delay:(double)sec Task:(JL_Action)block;

/**
 block。
 
 */
+(void)subTask:(JL_Action)block;

/**
 block。
 
 */
+(void)mainTask:(JL_Action)block;


/**
 
 */
+(NSTimer*)timingStart:(SEL)sel target:(id)objc Time:(NSTimeInterval)sec;


/**
 
 */
+(void)timingPause:(__weak NSTimer*)timer;

/**
 
 */
+(void)timingContinue:(__weak NSTimer*)timer;


/**
 
 */
+(void)timingStop:(__weak NSTimer*)timer;


/**
 ，。
 
 */
+(NSString*)createOn:(NSSearchPathDirectory)sPath
          MiddlePath:(NSString*)mPath
                File:(NSString*)file;

/**
 
 */
+(NSString*)listPath:(NSSearchPathDirectory)sPath
          MiddlePath:(NSString*)mPath
                File:(NSString*)file;

/**
 */
+(NSString*)findPath:(NSSearchPathDirectory)sPath
          MiddlePath:(NSString*)mPath
                File:(NSString*)file;

/**
 */
+(NSString*)find:(NSString *)file;

/**
 */
+(BOOL)isExistsPath:(NSString*)path;
/**
 */
+(BOOL)removePath:(NSString*)path;

/**
 */
+(NSArray*)subPaths:(NSString*)path;

/**
 */
+(id)JsonPath:(NSString*)path;

/**
 *  NSArray ==> NSString.
 */
+(NSString*)arrayToJson:(NSArray *)array;

/**
 
 */
+(BOOL)writeData:(NSData*)data fillFile:(NSString*)path;

/**
 
 */
+(void)writeData:(NSData*)data endFile:(NSString*)path;

/**
 
 */
+(void)writeData:(NSData*)data Seek:(unsigned long long)seek File:(NSString*)path;

/**
 */
+(NSString*)stringUnicode:(NSData*)data;

/**
 */
+(NSString*)stringUnicodeBig:(NSData*)data;

/**
 */
+(NSString*)stringANSI:(NSData*)data;

/**
 */
+(NSString*)stringGBK:(NSData*)data;

/**
 */
+(NSData*)stringBigFileWithNeedRemoveUnnecessaryPunctuationCharactersWithString:(NSString*)name withFileNameIndex:(int)fileNameIndex;


/// - Parameters:
///   - fileNameIndex: index
+(NSData *)stringBigFileUnicode:(NSString *)name withFileNameIndex:(int)fileNameIndex WithEncode:(NSStringEncoding) encodeType;
/**
 */
+(NSString *)removeUnnecessaryPunctuationCharactersWithString:(NSString *)textString;

/**
 * NSString *pattern = @"[/:*?\"<>|]";
 */
+(NSString *)removeCharacters:(NSString*)pattern WithString:(NSString *)textString;

/**
 */
+(NSData*)stringBigFile:(NSString*)name withFileNameIndex:(int)fileNameIndex;

/**
 */
+(NSString*)removeSpecialStrings:(NSString*)name;
/**
 */
+(long)dateCurrent;


+(NSData *)beLtv:(uint8_t)type Data:(NSData*)data;



@end

@interface JL_Timer : NSObject
@property(nonatomic,assign)NSInteger            subTimeout;
@property(nonatomic,assign)NSTimeInterval       subScale;
-(void)waitForTimeoutResult:(JL_Timer_BK)result;
-(void)continueTimeout;
-(void)cancelTimeout;
-(void)threadWait;
-(void)threadContinue;
@end

NS_ASSUME_NONNULL_END
