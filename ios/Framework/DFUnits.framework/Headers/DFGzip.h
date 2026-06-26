//
//  DFGzip.h
//  DFUnits
//
//  Created by DFung on 2016/12/13.
//

#import <Foundation/Foundation.h>

@interface DFGzip : NSObject


/**
 */
+(NSData *)uncompressZippedData:(NSData *)compressedData;

/**
 */
+(NSData *)gzipData:(NSData *)pUncompressedData;


@end
