//
//  JL_TypeEnum.h
//  JL_BLEKit
//
//  Created by DFung on 2018/11/29.
//  Copyright © 2018 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JLModel_SmallFile.h>

typedef NS_ENUM(NSInteger, JL_BLEStatus) {
    JL_BLEStatusFound,
    JL_BLEStatusPaired,
    JL_BLEStatusDisconnected,
    JL_BLEStatusOn,
    JL_BLEStatusOff,
    JL_BLEStatusUnknown,
};
typedef NS_ENUM(NSInteger, JL_DeviceBTStatus) {
    JL_DeviceBTStatusDisconnected   = 0,
    JL_DeviceBTStatusConnected      = 1,
    JL_DeviceBTStatusUnknown,
};
typedef NS_ENUM(UInt8, JL_CMDStatus) {
    JL_CMDStatusSuccess             = 0x00,
    JL_CMDStatusFail                = 0x01,
    JL_CMDStatusUnknownCmd          = 0x02,
    JL_CMDStatusBusy                = 0x03,
    JL_CMDStatusNoResponse          = 0x04,
    JL_CMDStatusCrcErr              = 0x05,
    JL_CMDStatusDataCrcErr          = 0x06,
    JL_CMDStatusParamErr            = 0x07,
    JL_CMDStatusOverLimit           = 0x08,
    JL_CMDStatusLrcError            = 0x09,
    JL_CMDStatusUnknown,
};
typedef void(^JL_CMD_RESPOND)(JL_CMDStatus status, uint8_t sn, NSData* __nullable data);

//---------------------------------------------------------//

typedef NS_ENUM(UInt8,JLDevSpecialType) {
    JLDevSpecialType_Normal = 0x00,
    JLDevSpecialType_Reconnect = 0x01,
};

typedef NS_ENUM(int64_t,JL_CLASS) {
    JL_CLASS_SmallFile      = 0,
    JL_CLASS_File           = 1,
    JL_CLASS_OTA            = 2,
    JL_CLASS_Flash          = 3,
    JL_CLASS_ChargingBin    = 4,
    JL_CLASS_AlarmClock     = 5,
    JL_CLASS_Light          = 6,
    JL_CLASS_Tws            = 7,
    JL_CLASS_SoundCard      = 8,
    JL_CLASS_Call           = 9,
    JL_CLASS_Speex          = 10,
    JL_CLASS_Lrc            = 11,
    JL_CLASS_FindDevice     = 12,
    JL_CLASS_MusicControl   = 13,
    JL_CLASS_Fm             = 14,
    JL_CLASS_SystemEQ       = 15,
    JL_CLASS_SystemTime     = 16,
    JL_CLASS_SystemVolume   = 17,
    JL_CLASS_Custom         = 18,
    JL_CLASS_Batch          = 19,
    JL_CLASS_DeviceLogs     = 20,
    JL_CLASS_BigData        = 21,
};

//---------------------------------------------------------//


typedef NS_ENUM(UInt8, JLCMDOriginator) {
    JLCMDOriginatorApp = 0x00,
    JLCMDOriginatorDevice = 0x01
};
