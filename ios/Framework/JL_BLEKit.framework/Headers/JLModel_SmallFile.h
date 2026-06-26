//
//  JLModel_SmallFile.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/10/14.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(UInt8, JL_SmallFileType) {
    JL_SmallFileTypeContacts        = 0x01,
    JL_SmallFileTypeMotionRecord    = 0x02,
    JL_SmallFileTypeHeartRate       = 0x03,
    JL_SmallFileTypeSpoData         = 0x04,
    JL_SmallFileTypeSleepData       = 0x05,
    JL_SmallFileTypeMassage         = 0x06,
    JL_SmallFileTypeWeather         = 0x07,
    JL_SmallFileTypeCallLog         = 0x08,
    JL_SmallFileTypeStepCount       = 0x09,
    JL_SmallFileTypeWeight          = 0xFF,
};

@interface JLModel_SmallFile : NSObject
@property(nonatomic,assign)JL_SmallFileType  file_type;
@property(nonatomic,assign)uint8_t  file_ver;
@property(nonatomic,assign)uint16_t file_id;
@property(nonatomic,assign)uint16_t file_size;
@end

NS_ASSUME_NONNULL_END
