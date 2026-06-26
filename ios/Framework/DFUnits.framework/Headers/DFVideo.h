//
//  DFVideo.h
//  DFUnits
//
//  Created by DFung on 16/1/22.
//

#import <Foundation/Foundation.h>

@interface DFVideo : NSObject

/**
 */
+(NSDictionary*)previewAVI:(NSString*)path;

/**
 */
+(NSDictionary *)previewData:(NSData*)data;

/**
 */
+(NSString *)timeTyping:(long)total;

@end
