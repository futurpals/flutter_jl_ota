//
//  JL_ManagerM.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2020/9/4.
//  Modify By EzioChan on 2023/03/27.
//  Copyright © 2020 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JL_RCSP.h>

#import <JL_BLEKit/JLModel_Device.h>
#import <JL_BLEKit/JLModel_RTC.h>
#import <JL_BLEKit/JLModel_Ring.h>
#import <JL_BLEKit/JLModel_File.h>
#import <JL_BLEKit/JLModel_FM.h>
#import <JL_BLEKit/JLModel_Headset.h>
#import <JL_BLEKit/JLModel_BT.h>
#import <JL_BLEKit/JLModel_EQ.h>
#import <JL_BLEKit/JLModel_SPEEX.h>
#import <JL_BLEKit/JLModel_Flash.h>
#import <JL_BLEKit/JLModel_ANC.h>
#import <JL_BLEKit/JLModel_AlarmSetting.h>
#import <JL_BLEKit/RTC_RingInfo.h>

#import <JL_BLEKit/JL_FunctionBaseManager.h>
#import <JL_BLEKit/JL_SmallFileManager.h>
#import <JL_BLEKit/JL_FileManager.h>
#import <JL_BLEKit/JL_FlashOperateManager.h>
#import <JL_BLEKit/JL_BinChargeManager.h>
#import <JL_BLEKit/JL_AlarmClockManager.h>
#import <JL_BLEKit/JL_CallManager.h>
#import <JL_BLEKit/JL_LightManager.h>
#import <JL_BLEKit/JL_TwsManager.h>
#import <JL_BLEKit/JL_SoundCardManager.h>
#import <JL_BLEKit/JL_LrcManager.h>
#import <JL_BLEKit/JL_SpeexManager.h>
#import <JL_BLEKit/JL_FindDeviceManager.h>
#import <JL_BLEKit/JL_MusicControlManager.h>
#import <JL_BLEKit/JL_FmManager.h>
#import <JL_BLEKit/JL_SystemEQ.h>
#import <JL_BLEKit/JL_SystemTime.h>
#import <JL_BLEKit/JL_SystemVolume.h>
#import <JL_BLEKit/JL_CustomManager.h>
#import <JL_BLEKit/JL_BigDataManager.h>
#import <JL_BLEKit/JL_DeviceLogs.h>
#import <JL_BLEKit/JL_BatchManger.h>
#import <JL_OTALib/JL_OTALib.h>


NS_ASSUME_NONNULL_BEGIN

/*
 *
 */
extern NSString *kJL_MANAGER_KEY_UUID;      //KEY --> UUID
extern NSString *kJL_MANAGER_KEY_OBJECT;


@protocol JL_ManagerMDelegate <NSObject>
@optional
-(void)onManagerSendPackage:(JL_PKG*)pkg;
@end

@class JL_EntityM;
@interface JL_ManagerM : NSObject
@property(nonatomic,weak)id<JL_ManagerMDelegate>delegate;
@property(nonatomic,readonly,copy)NSString  *mBLE_UUID;
@property(nonatomic,readonly,copy)NSString  *mBLE_NAME;
@property(nonatomic,readonly,assign)uint8_t mCmdSN;
@property(nonatomic,weak)JL_EntityM         *mEntity;

@property(nonatomic,strong)JL_SmallFileManager      *mSmallFileManager;
@property(nonatomic,strong)JL_FileManager           *mFileManager;
@property(nonatomic,strong)JL_OTAManager            *mOTAManager;
@property(nonatomic,strong)JL_FlashOperateManager   *mFlashManager;
@property(nonatomic,strong)JL_BinChargeManager      *mChargingBinManager;
@property(nonatomic,strong)JL_CallManager           *mCallManager;
@property(nonatomic,strong)JL_AlarmClockManager     *mAlarmClockManager;
@property(nonatomic,strong)JL_LightManager          *mLightManager;
@property(nonatomic,strong)JL_TwsManager            *mTwsManager;
@property(nonatomic,strong)JL_SpeexManager          *mSpeexManager __attribute__((deprecated("alloc with JL_SpeexManager shareSpeexManager")));
@property(nonatomic,strong)JL_LRCManager            *mLrcManager;
@property(nonatomic,strong)JL_FindDeviceManager     *mFindDeviceManager;
@property(nonatomic,strong)JL_MusicControlManager   *mMusicControlManager;
@property(nonatomic,strong)JL_FmManager             *mFmManager;
@property(nonatomic,strong)JL_SystemEQ              *mSystemEQ;
@property(nonatomic,strong)JL_SystemTime            *mSystemTime;
@property(nonatomic,strong)JL_SystemVolume          *mSystemVolume;
@property(nonatomic,strong)JL_CustomManager         *mCustomManager;
@property(nonatomic,strong)JL_BatchManger           *mBatchManger;

@property(nonatomic,strong)JL_SoundCardManager      *mSoundCardManager;
@property(nonatomic,strong)JL_DeviceLogs            *mDeviceLogs;

@property(nonatomic,strong)JL_BigDataManager        *mBigDataManager;


-(void)setPropertyUpdate:(BOOL)isUpdate;
-(void)setBleUuid:(NSString*)uuid;
-(void)setBleName:(NSString*)name;
-(void)inputPKG:(JL_PKG*)pkg;

-(void)noteEntityConnected;
-(void)noteEntityDisconnected;
-(void)noteEntityBleOff;

/**
 【】
 @discussion isCommandYESneedResponse，
 */
-(void)xmCommandCode:(uint8_t)cmdCode
             needRep:(BOOL)needResponse
                data:(NSData *)sendData;

/**
 【】
 */
-(void)cmdResponseCode:(uint8_t)code
                  OpSN:(UInt8)sn
                Status:(JL_CMDStatus)st
                  Data:(NSData* __nullable)data;

/**
 【】
 */
-(void)managerPost:(NSString*)name Object:(id __nullable)obj;

/**
 */
-(uint8_t)xmCommandSN;

#pragma mark - Vendor SDK

-(JLModel_Device *)outputDeviceModel;

-(JLModel_Device *)getDeviceModel;

#pragma mark - Vendor SDK
extern NSString *kJL_MANAGER_TARGET_INFO;
-(void)cmdTargetFeatureResult:(JL_CMD_RESPOND __nullable)result;
-(void)cmdTargetFeature:(uint32_t)feature Result:(JL_CMD_RESPOND __nullable)result;

#pragma mark - Vendor SDK
-(void)cmdDisconnectEdrResult:(JL_CMD_RESPOND __nullable)result;

#pragma mark - Vendor SDK
-(void)cmdResetPairingResult:(JL_CMD_RESPOND __nullable)result;

#pragma mark - Vendor SDK
/**
 */
-(void)cmdGetSystemInfo:(JL_FunctionCode)function
                 Result:(JL_CMD_RESPOND __nullable)result;
-(void)cmdGetSystemInfoResult;

#pragma mark - Vendor SDK
/**
 */
-(void)cmdGetSystemInfo:(JL_FunctionCode)function
           SelectionBit:(uint32_t)bits
                 Result:(JL_CMD_RESPOND __nullable)result;
-(void)cmdGetSystemInfoResult_1;

#pragma mark - Vendor SDK
extern NSString *kJL_MANAGER_SYSTEM_INFO;

#pragma mark - Vendor SDK
/**
 */
-(void)cmdFunction:(JL_FunctionCode)function
           Command:(UInt8)cmd
            Extend:(UInt8)ext
            Result:(JL_CMD_RESPOND __nullable)result;

typedef void(^JL_IMAGE_RT)(NSMutableDictionary* __nullable dict);
#pragma mark - Vendor SDK
/**
 */
-(void)cmdRequestDeviceImageVid:(NSString*)vid
                            Pid:(NSString*)pid
                         Result:(JL_IMAGE_RT __nullable)result;

-(void)cmdRequestDeviceImageVid:(NSString*)vid
                            Pid:(NSString*)pid
                      ItemArray:(NSArray *__nullable)itemArray
                         Result:(JL_IMAGE_RT __nullable)result;

-(NSDictionary*)localDeviceImage:(NSString*)jsonFile;

#pragma mark - Vendor SDK

-(void)cmdStartTTSNote:(uint8_t)status;


-(void)cmdGetMD5_Result:(JL_CMD_RESPOND)result;

@end

NS_ASSUME_NONNULL_END
