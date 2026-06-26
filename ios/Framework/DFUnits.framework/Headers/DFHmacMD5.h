//
//  DFHmacMD5.h
//  DFUnits
//
//  Created by DFung on 2016/12/13.
//

#import <Foundation/Foundation.h>

@interface DFHmacMD5 : NSObject

/*
 */
+ (NSString *)HmacMD5String:(NSString *)string;

/*
 */
+ (NSString *)HmacMD5String:(NSString *)string
                        Key:(NSString *)keyStr;

@end
