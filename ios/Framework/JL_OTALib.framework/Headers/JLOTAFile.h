//
//  JLOTAFile.h
//  JL_OTALib
//
//  Created by EzioChan on 2024/7/26.
//  Copyright © 2024 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_OTAUrlResult) {
    JL_OTAUrlResultSuccess          = 0x00,
    JL_OTAUrlResultFail             = 0x01,
    JL_OTAUrlResultDownloadFail     = 0x02,
};

typedef void(^JL_OTA_URL)(JL_OTAUrlResult result,
                          NSString* __nullable version,
                          NSString* __nullable url,
                          NSString* __nullable explain);

@interface JLOTAFile : NSObject


#pragma mark - Vendor SDK
/**
 */
-(void)cmdGetOtaFileKey:(NSString*)key
                   Code:(NSString*)code
                 Result:(JL_OTA_URL __nullable)result;

/**
 OTA【MD5】
*/
-(void)cmdGetOtaFileKey:(NSString*)key
                   Code:(NSString*)code
                   hash:(NSString*)hash
                 Result:(JL_OTA_URL __nullable)result;

@end

NS_ASSUME_NONNULL_END
