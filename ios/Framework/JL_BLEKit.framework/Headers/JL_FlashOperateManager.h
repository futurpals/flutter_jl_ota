//
//  JL_FlashOperateManager.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/12/13.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_FunctionBaseManager.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JL_Tools.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Vendor SDK
typedef NS_ENUM(UInt8, JL_FlashOperationOPType) {
    JL_FlashOperationOPTypeWriteData             = 0x00,
    JL_FlashOperationOPTypeReadData              = 0x01,
    JL_FlashOperationOPTypeInsertFile            = 0x02,
    JL_FlashOperationOPTypeDialOperation         = 0x03,
    JL_FlashOperationOPTypeEraseData             = 0x04,
    JL_FlashOperationOPTypeDeleteFile            = 0x05,
    JL_FlashOperationOPTypeWriteFileProtection   = 0x06,
    JL_FlashOperationOPTypeUpdateDialResource    = 0x07,
    JL_FlashOperationOPTypeCheckWriteDataSuccess = 0x08,
    JL_FlashOperationOPTypeUpdateResourceFlag    = 0x09,
    JL_FlashOperationOPTypeRestoreSystem         = 0x0A,
    JL_FlashOperationOPTypeGetFileInfo           = 0x0B,
    JL_FlashOperationOPTypeGetRemainingSpace     = 0x0C,
    JL_FlashOperationOpTypeGetSourceStorageInfo  = 0x0D,
};

typedef NS_ENUM(UInt8, JL_DialSetting) {
    JL_DialSettingReadCurrentDial               = 0x00,
    JL_DialSettingSetDial                       = 0x01,
    JL_DialSettingVersion                       = 0x03,
    JL_DialSettingActivateCustomDial            = 0x04,
    JL_DialSettingGetDialName                   = 0x05,
};
typedef NS_ENUM(UInt8, JL_FlashOperateFlag) {
    JL_FlashOperateFlagFinish           = 0x00,
    JL_FlashOperateFlagStart            = 0x01,
};

@interface JL_FlashOperateManager : JL_FunctionBaseManager

typedef void(^JL_FlashInfo_BK)(JLModel_Flash* __nullable model);
typedef void(^JL_FlashWrite_BK)(uint8_t flag);
typedef void(^JL_FlashWriteStatus_BK)(uint8_t flag,uint16_t leftSize);
typedef void(^JL_FlashWriteSize_BK)(uint8_t flag,uint32_t size);
typedef void(^JL_FlashRead_BK)(uint8_t flag,NSData *__nullable data);
typedef void(^JL_FlashAddOrDel_BK)(uint8_t flag);
typedef void(^JL_FlashWatch_BK)(uint8_t flag, uint32_t size,
                                NSString *__nullable path,
                                NSString *__nullable describe);
typedef void(^JL_FlashClean_BK)(uint8_t flag);
typedef void(^JL_FlashProtect_BK)(uint8_t flag);
typedef void(^JL_FlashUpdate_BK)(uint8_t flag);
typedef void(^JL_FlashFileInfo_BK)(uint32_t size,uint16_t crc16);
typedef void(^JL_FlashLeftSize_BK)(uint32_t leftSize);

/// Flash Info 
@property(nonatomic,strong)JLModel_Flash *flashInfo;

#pragma mark - Vendor SDK
/**
 Flash
 */
-(void)cmdGetFlashInfoResult:(JL_FlashInfo_BK __nullable)result;

#pragma mark - Vendor SDK
/**
 Flash
 */
-(void)cmdWriteToFlashAllData:(NSData*)data
                       Offset:(uint32_t)offset
                          Mtu:(uint16_t)mtu
                       Result:(JL_FlashWriteSize_BK __nullable)result;

#pragma mark - Vendor SDK
/**
 Flash
 */
-(void)cmdReadFromFlashAllDataOffset:(uint32_t)offset
                                Size:(uint16_t)size
                                 Mtu:(uint16_t)mtu
                              Result:(JL_FlashRead_BK __nullable)result;

#pragma mark - Vendor SDK
/**
 /
 */
-(void)cmdInsertFlashPath:(NSString* __nullable)path
                     Size:(uint32_t)size
                     Flag:(JL_FlashOperateFlag)flag
                   Result:(JL_FlashAddOrDel_BK __nullable)result;

#pragma mark - Vendor SDK

/**
                0x01:
                0x03:，
                0x04:
                0x05:
 */
-(void)cmdWatchFlashPath:(NSString*__nullable)path
                    Flag:(JL_DialSetting)flag
                  Result:(JL_FlashWatch_BK __nullable)result;

#pragma mark - Vendor SDK
extern NSString *kJL_MANAGER_WATCH_FACE;

#pragma mark - Vendor SDK
/**
 /
 */
-(void)cmdDeleteFlashPath:(NSString* __nullable)path
                     Flag:(JL_FlashOperateFlag)flag
                   Result:(JL_FlashAddOrDel_BK __nullable)result;

#pragma mark - Vendor SDK
/**
 /
 */
-(void)cmdWriteProtectFlashFlag:(JL_FlashOperateFlag)flag Result:(JL_FlashProtect_BK __nullable)result;

#pragma mark - Vendor SDK
/**
 / UI
 */
-(void)cmdUpdateResourceFlashFlag:(JL_FlashOperateFlag)flag Result:(JL_FlashUpdate_BK __nullable)result __attribute__((deprecated ( "The current interface is about to be canceled in version 2.0.0, please use cmdUpdateResourceFlashFlagAsync:Result:  instead")));
-(void)cmdUpdateResourceFlashFlag:(JL_FlashOperateFlag)flag;
/// - Parameters:
///   - flag: flag
-(void)cmdUpdateResourceFlashFlagAsync:(JL_FlashOperateFlag)flag Result:(JL_FlashUpdate_BK __nullable)result;

#pragma mark - Vendor SDK
-(void)cmdFlashActionDisconnect;

#pragma mark - Vendor SDK
-(void)cmdWatchUpdateResource __attribute__((deprecated ( "The current interface is about to be canceled in version 2.0.0, please use cmdWatchUpdateResourceWith:(JL_CMD_RESPOND __nullable)result instead")));

-(void)cmdWatchUpdateResourceWith:(JL_CMD_RESPOND __nullable)result;

#pragma mark - Vendor SDK
-(void)cmdFlashRecovery;

#pragma mark - Vendor SDK
-(void)cmdFlashInformationOfFile:(NSString*)file Result:(JL_FlashFileInfo_BK)result;

#pragma mark - Vendor SDK
-(void)cmdFlashLeftSizeResult:(JL_FlashLeftSize_BK)result;

-(void)cmdFlashGetSourceStorageInfo:(JL_FlashLeftSize_BK)result;
@end

NS_ASSUME_NONNULL_END
