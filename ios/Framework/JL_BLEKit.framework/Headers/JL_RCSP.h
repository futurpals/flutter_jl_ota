//
//  JL_RCSP.h
//  JL_BLEKit
//
//  Created by zhihui liang on 2018/11/9.
//  Copyright © 2018 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_OpCode.h>

NS_ASSUME_NONNULL_BEGIN



@class JL_PKG;
@interface JL_RCSP : NSObject

/**
 JL
 
 */
+(JL_PKG*)rcspAnalysisData:(NSData*)data;

/**
 XM
 
 */
+(NSData*)rcspMakePackage:(JL_PKG*)pkg;

/**
 JL_PKG
 
 */
+(NSArray*)rcspAnalysisParams:(JL_PKG*)pkg;

/**
 dJL_PKG

 */
+(NSArray*)rcspInfoArrFromData:(NSData*)data;

+(NSArray*)rcspInfoFromData2ByteSize:(NSData*)data;

/**
 JL_PKG
 
 */
+(NSData*)rcspMakeParams:(NSArray*)array;
@end

@interface JL_PKG : NSObject
@property(assign,nonatomic) uint16_t pkgIsCommand;       //1Bit
@property(assign,nonatomic) uint16_t pkgNeedResponse;    //1Bit
@property(assign,nonatomic) uint16_t pkgUnused;          //6Bits
@property(assign,nonatomic) uint16_t pkgOpCode;          //8Bits
@property(assign,nonatomic) uint16_t pkgLength;
@property(strong,nonatomic) NSData   *pkgData;
@end
NS_ASSUME_NONNULL_END
