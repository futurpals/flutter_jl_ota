//
//  JLAdvParse.h
//  JL_AdvParse
//
//  Created by EzioChan on 2023/1/31.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JLLogHelper/JLLogHelper.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8,JL_AdvType) {
    JL_AdvTypeSoundBox              = 0,
    JL_AdvTypeChargingBin           = 1,
    JL_AdvTypeTWS                   = 2,
    JL_AdvTypeHeadset               = 3,
    JL_AdvTypeSoundCard             = 4,
    JL_AdvTypeWatch                 = 5,
    JL_AdvTypeTradition             = 6,
};


typedef NS_ENUM(NSInteger,JL_DeviceType) {
    JL_DeviceTypeSoundBox           = 0,
    JL_DeviceTypeChargingBin        = 1,
    JL_DeviceTypeTWS                = 2,
    JL_DeviceTypeHeadset            = 3,
    JL_DeviceTypeSoundCard          = 4,
    JL_DeviceTypeWatch              = 5,
    JL_DeviceTypeTradition          = -1,
};


@interface JLAdvParse : NSObject

+(void)sdkVersion;

+(NSDictionary*)bluetoothAdvParse:(NSData *_Nullable)key AdvData:(NSDictionary*_Nonnull)advertData;

+(NSDictionary *)bluetoothAdvData:(NSDictionary *)advertData RSSI:(NSNumber *)rssi;

#pragma mark - Vendor SDK
/**
 */
+ (NSString * _Nullable)otaBleMacAddressFromCBAdvDataManufacturerData:(NSData *)kCBAdvDataManufacturerData;

/**
 */
+ (Boolean)otaBleMacAddress:(NSString *)otaBleMacAddress isEqualToCBAdvDataManufacturerData:(NSData *)kCBAdvDataManufacturerData;




@end

NS_ASSUME_NONNULL_END
