//
//  JL_FmManager.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/12/20.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_FunctionBaseManager.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JL_Tools.h>


typedef NS_ENUM(UInt8, JL_FCmdFM) {
    JL_FCmdFMPP                     = 0x01,
    JL_FCmdFMPonitBefore            = 0x02,
    JL_FCmdFMPonitNext              = 0x03,
    JL_FCmdFMChannelBefore          = 0x04,
    JL_FCmdFMChannelNext            = 0x05,
    JL_FCmdFMSearch                 = 0x06,
    JL_FCmdFMChannelSelect          = 0x07,
    JL_FCmdFMChannelDelete          = 0x08,
    JL_FCmdFMFrequencySelect        = 0x09,
    JL_FCmdFMFrequencyDelete        = 0x0a,
};

typedef NS_ENUM(UInt8, JL_FMSearch) {
    JL_FMSearchALL                  = 0x00,
    JL_FMSearchForward              = 0x01,
    JL_FMSearchBackward             = 0x02,
    JL_FMSearchStop                 = 0x03,
};

NS_ASSUME_NONNULL_BEGIN

@interface JL_FmManager : JL_FunctionBaseManager

@property (assign,nonatomic) JL_FMStatus        fmStatus;

///76.5-108.0Mhz
///87.5-108.0Mhz
@property (assign,nonatomic) JL_FMMode          fmMode;

@property (strong,nonatomic) JLModel_FM          *currentFm;

@property (strong,nonatomic) NSArray            *fmArray;

#pragma mark - Vendor SDK
/**
 */
-(void)cmdFm:(JL_FCmdFM)cmd
      Saerch:(JL_FMSearch)search
     Channel:(uint8_t)channel
   Frequency:(uint16_t)frequency
      Result:(JL_CMD_RESPOND __nullable)result;

@end

NS_ASSUME_NONNULL_END

