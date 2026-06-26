//
//  JL_MSG_Weather.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/5/13.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

 
typedef NS_ENUM(UInt8, JLWeatherType) {
    JLWeatherTypeSunny = 0x00,
    JLWeatherTypeCloudLess,
    JLWeatherTypePartlyCloudy,
    JLWeatherTypeCloudiness,
    JLWeatherTypeOvercastSky,
    JLWeatherTypeBreeze,
    JLWeatherTypeCalmWind,
    JLWeatherTypeHighWind,
    JLWeatherTypeHurricane,
    JLWeatherTypeTropicalStorm,
    JLWeatherTypeHaze,
    JLWeatherTypeShower,
    JLWeatherTypeThunderShower,
    JLWeatherTypeHallThunderShower,
    JLWeatherTypeLightRain,
    JLWeatherTypeModerateRain,
    JLWeatherTypeHeavyRain,
    JLWeatherTypeDownpour,
    JLWeatherTypeExtraordinaryRainstorm,
    JLWeatherTypeHeavyDownpour,
    JLWeatherTypeStrongRainShower,
    JLWeatherTypeStrongThunderShower,
    JLWeatherTypeExtremeRainfall,
    JLWeatherTypeRainySnowy,
    JLWeatherTypeSnowy,
    JLWeatherTypeSnowShower,
    JLWeatherTypeLightSnow,
    JLWeatherTypeModerateSnow,
    JLWeatherTypeHeavySnow,
    JLWeatherTypeSnowstorm,
    JLWeatherTypeDust,
    JLWeatherTypeblowingSand,
    JLWeatherTypedustStorm,
    JLWeatherTypeSevereSandstorm,
    JLWeatherTypeTornado,
    JLWeatherTypeFog,
    JLWeatherTypeUnknow,
    JLWeatherTypeCold,
    JLWeatherTypeUnknown1,
    
};

typedef NS_ENUM(UInt8, JLWindDirectionType) {
    JLWindDirectionTypeNone = 0x00,
    JLWindDirectionTypeEast,
    JLWindDirectionTypeSouth,
    JLWindDirectionTypeWest,
    JLWindDirectionTypeNorth,
    JLWindDirectionTypeEastSouth,
    JLWindDirectionTypeEastNorth,
    JLWindDirectionTypeWestNorth,
    JLWindDirectionTypeWestSouth,
    JLWindDirectionTypeUnknow
};

@interface JL_MSG_Weather : NSObject

@property(nonatomic,strong)NSString *province;
@property(nonatomic,strong)NSString *city;
@property(nonatomic,assign)JLWeatherType code;
@property(nonatomic,assign)NSInteger temperature;
@property(nonatomic,assign)NSInteger humidity;
@property(nonatomic,assign)JLWindDirectionType direction;
@property(nonatomic,assign)NSInteger wind;
@property(nonatomic,strong)NSDate *date;


-(NSData *)beData;

@end

NS_ASSUME_NONNULL_END
