//
//  DFFile.h
//  DVRunning
//
//  Created by Mac on 15/11/13.
//

#import <Foundation/Foundation.h>

@interface DFFile : NSObject
/**
 */
+(BOOL)createPath:(NSString*)path;

/**
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
+(NSString*)fileByte:(long long)byte;

/**
 */
+(BOOL)renameOldName:(NSString*)oldName
             NewName:(NSString*)newName;
/**
 */
+(BOOL)removePath:(NSString*)path;

/**
 */
+(BOOL)writeData:(NSData*)data fillFile:(NSString*)path;

/**
 */
+(void)writeData:(NSData*)data endFile:(NSString*)path;

/**
 */
+(NSString*)find:(NSString*)bundle File:(NSString*)file;

/**
 */
+(NSString*)find:(NSString *)file;

/**
 */
+(id)JsonPath:(NSString*)path;

/**
 */
+(id)JsonData:(NSData*)data;

/**
 */
+(NSString*)stringPath:(NSString*)path;

/**
 */
+(NSArray*)subPaths:(NSString*)path;

/**
 */
+(long long)sizeOfFile:(NSString*)path;


@end
