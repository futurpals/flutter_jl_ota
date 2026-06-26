//
//  JLModel_Device.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/10/15.
//  Modify by EzioChan on 2023/03/16
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JLModel_Flash.h>
#import <JL_BLEKit/JLModel_ANC.h>
#import <JL_BLEKit/JLModel_RTC.h>
#import <JL_BLEKit/JLModel_FM.h>
#import <JL_BLEKit/JLModel_File.h>
#import <JL_BLEKit/JLModel_EQ.h>
#import <JL_BLEKit/JLDhaFitting.h>
#import <JL_OTALib/JL_OTALib.h>
#import <JL_BLEKit/JLModelCardInfo.h>
#import <JL_BLEKit/JLModelDevFunc.h>


NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_DevicePlatform) {
    JL_DevicePlatformTuring         = 0,
    JL_DevicePlatformDeepbrain      = 1,
    JL_DevicePlatformUnknown,
};
typedef NS_ENUM(UInt8, JL_SDKType) {
    JL_SDKTypeAI                    = 0x0,    //AI SDK  AC692x
    JL_SDKTypeST                    = 0x1,
    JL_SDKType693xTWS               = 0x2,    //TWS
    JL_SDKType695xSDK               = 0x3,    //
    JL_SDKType697xTWS               = 0x4,    //TWS
    JL_SDKType696xSB                = 0x5,    //696x_soundbox
    JL_SDKType696xTWS               = 0x6,    //TWS
    JL_SDKType695xSC                = 0x7,    //695x_sound_card
    JL_SDKType695xWATCH             = 0x8,    //BR23 Watch
    JL_SDKType701xWATCH             = 0x9,    //BR28 Watch
    JL_SDKTypeManifestEarphone      = 0x0A,   //ManifestEarphone
    JL_SDKTypeManifestSoundbox      = 0x0B,   //ManifestSoundbox
    JL_SDKTypeChargingCase          = 0x0C,
    JL_SDKType707nWATCH             = 0x0D,   //707N Watch
    JL_SDKTypeUnknown,
};
typedef NS_ENUM(UInt8, JL_FunctionCode) {
    JL_FunctionCodeBT               = 0,    //BT
    JL_FunctionCodeMUSIC            = 1,
    JL_FunctionCodeRTC              = 2,
    JL_FunctionCodeLINEIN           = 3,    //LineIn
    JL_FunctionCodeFM               = 4,    //FM
    JL_FunctionCodeLIGHT            = 5,    //LIGHT
    JL_FunctionCodeFMTX             = 6,
    JL_FunctionCodeEQ               = 7,    //EQ
    JL_FunctionCodeSPDIF            = 8,    //SPDIF
    JL_FunctionCodePCServer         = 9,    //PCServer
    JL_FunctionCodeCOMMON           = 0xff,
};

typedef NS_ENUM(UInt8, JL_FCmdMusic) {
    JL_FCmdMusicPP                  = 0x01,
    JL_FCmdMusicPREV                = 0x02,
    JL_FCmdMusicNEXT                = 0x03,
    JL_FCmdMusicMODE                = 0x04,
    JL_FCmdMusicEQ                  = 0x05, //EQ
    JL_FCmdMusicFastBack            = 0x06,
    JL_FCmdMusicFastPlay            = 0x07,
};

typedef NS_ENUM(UInt8, JL_OtaBleAllowConnect) {
    JL_OtaBleAllowConnectYES        = 0,
    JL_OtaBleAllowConnectNO         = 1,
    JL_OtaBleAllowConnectUnknow     = 2,
};
typedef NS_ENUM(UInt8, JL_BLEOnly) {
    JL_BLEOnlyNO                    = 0,
    JL_BLEOnlyYES                   = 1,
};
typedef NS_ENUM(UInt8, JL_FasheEnable) {
    JL_FasheEnableNO                = 0,
    JL_FasheEnableYES               = 1,
};
typedef NS_ENUM(UInt8, JL_FasheType) {
    JL_FasheTypeNO                  = 0,
    JL_FasheTypeYES                 = 1,
};
typedef NS_ENUM(UInt8, JL_MD5Type) {
    JL_MD5TypeNO                    = 0,
    JL_MD5TypeYES                   = 1,
};
typedef NS_ENUM(UInt8, JL_GameType) {
    JL_GameTypeNO                   = 0,
    JL_GameTypeYES                  = 1,
};
typedef NS_ENUM(UInt8, JL_SearchType) {
    JL_SearchTypeNO                 = 0,
    JL_SearchTypeYES                = 1,
};
typedef NS_ENUM(UInt8, JL_KaraokeType) {
    JL_KaraokeTypeNO                = 0,
    JL_KaraokeTypeYES               = 1,
};
typedef NS_ENUM(UInt8,JL_KaraokeEQType){
    JL_KaraokeEQTypeNO              = 0,
    JL_KaraokeEQTypeYES             = 1,
};
typedef NS_ENUM(UInt8,JL_FlashType){
    JL_FlashTypeNO                  = 0,
    JL_FlashTypeYES                 = 1,
};
typedef NS_ENUM(UInt8,JL_AncType){
    JL_AncTypeNO                    = 0,
    JL_AncTypeYES                   = 1,
};
typedef NS_ENUM(UInt8, JL_AudioFileType) {
    JL_AudioFileTypeNO              = 0,
    JL_AudioFileTypeYES             = 1,
};
typedef NS_ENUM(UInt8, JL_FileSubcontractTransferCrc16Type){
    JL_FileSubcontractTransferCrc16TypeNO      = 0,
    JL_FileSubcontractTransferCrc16TypeYES     = 1,
};
typedef NS_ENUM(UInt8, JL_ReadFileInNewWayType){
    JL_ReadFileInNewWayTypeNO                  = 0,
    JL_ReadFileInNewWayTypeYES                 = 1,
};

typedef NS_ENUM(UInt8, JL_SmallFileWayType){
    JL_SmallFileWayTypeNO                      = 0,
    JL_SmallFileWayTypeYES                     = 1,
};

typedef NS_ENUM(UInt8,JL_CALLType) {
    JL_CALLType_OFF                 = 0,
    JL_CALLType_ON                  = 1,
};

typedef NS_ENUM(UInt8, JL_LightState) {
    JL_LightStateClose          = 0x00,
    JL_LightStateOpen           = 0x01,
    JL_LightStateSetting        = 0x02,
};
typedef NS_ENUM(UInt8, JL_LightMode) {
    JL_LightModeNormal          = 0x00,
    JL_LightModeFlash           = 0x01,
    JL_LightModeScene           = 0x02,
};
typedef NS_ENUM(UInt8, JL_LightFlashModeIndex) {
    JL_LightModeIndexColorfulFlash          = 0x00,
    JL_LightModeIndexRedFlash               = 0x01,
    JL_LightModeIndexOrangeFlash            = 0x02,
    JL_LightModeIndexYeallowFlash           = 0x03,
    JL_LightModeIndexGreenFlash             = 0x04,
    JL_LightModeIndexCyanFlash              = 0x05,
    JL_LightModeIndexBlueFlash              = 0x06,
    JL_LightModeIndexPurpleFlash            = 0x07,
};

typedef NS_ENUM(UInt8, JL_LightFlashModeFrequency) {
    JL_LightFlashModeFrequencyFast          = 0x00,
    JL_LightFlashModeFrequencySlow          = 0x01,
    JL_LightFlashModeFrequencyNormal        = 0x02,
    JL_LightFlashModeFrequencyMusic         = 0x03,
};

typedef NS_ENUM(UInt8, JL_LightSceneMode) {
    JL_LightSceneModeRainbow                = 0x00,
    JL_LightSceneModeHeartbeat              = 0x01,
    JL_LightSceneModeCandlelight            = 0x02,
    JL_LightSceneModeNightLight             = 0x03,
    JL_LightSceneModeStage                  = 0x04,
    JL_LightSceneModeDiffuseColourBreathing = 0x05,
    JL_LightSceneModeDiffuseRedBreathing    = 0x06,
    JL_LightSceneModeDiffuseGreenBreathing  = 0x07,
    JL_LightSceneModeDiffuseBlueBreathing   = 0x08,
    JL_LightSceneModeGreenMood              = 0x09,
    JL_LightSceneModeSettingSunView         = 0x10,
    JL_LightSceneModeMusicRhythm            = 0x11,
};

typedef NS_ENUM(UInt8, JL_FileHandleType) {
    JL_FileHandleTypeSD_0                 = 0,    //SD_0
    JL_FileHandleTypeSD_1                 = 1,    //SD_1
    JL_FileHandleTypeFLASH                = 2,    //FLASH
    JL_FileHandleTypeUSB                  = 3,    //USB
    JL_FileHandleTypeLineIn               = 4,    //LineIn
    JL_FileHandleTypeFLASH2               = 5,    //FLASH2
    JL_FileHandleTypeFLASH3               = 6,    //FLASH3
    JL_FileHandleTypeReservedArea         = 7,    //ReservedArea
};

typedef NS_ENUM(UInt8, JL_MusicMode) {
    JL_MusicModeLoopAll             = 0x01,
    JL_MusicModeLoopDevice          = 0x02,
    JL_MusicModeLoopOne             = 0x03,
    JL_MusicModeRandomDevice        = 0x04,
    JL_MusicModeLoopFolder          = 0x05,
};

typedef NS_ENUM(UInt8, JL_MusicStatus) {
    JL_MusicStatusPlay              = 0x01,
    JL_MusicStatusPause             = 0x00,
};

typedef NS_ENUM(UInt8, JL_EQType) {
    JL_EQType10                     = 0,
    JL_EQTypeMutable                = 1,
};

//---------------------------------------------------------//
#pragma mark - RTC
typedef NS_ENUM(UInt8, JL_RTCAlarmType) {
    JL_RTCAlarmTypeNO               = 0,
    JL_RTCAlarmTypeYES              = 1,
};
//---------------------------------------------------------//
#pragma mark - LINEIN
typedef NS_ENUM(UInt8, JL_LineInStatus) {
    JL_LineInStatusPause            = 0x00,
    JL_LineInStatusPlay             = 0x01,
    JL_LineInStatusUnknown,
};
//---------------------------------------------------------//
#pragma mark - FM
typedef NS_ENUM(UInt8, JL_FMStatus) {
    JL_FMStatusPause                = 0x01,
    JL_FMStatusPlay                 = 0x02,
    JL_FMStatusSearching            = 0x03,
    JL_FMStatusUnknown,
};
typedef NS_ENUM(UInt8, JL_FMMode) {
    JL_FMMode875Mhz                 = 0x00, //87.5-108.0Mhz
    JL_FMMode760Mhz                 = 0x01, //76.5-108.0Mhz
    JL_FMModeUnknown,
};

typedef NS_ENUM(UInt8,JL_ReverberationType) {
    JL_ReverberationTypeNormal      = 0,
    JL_ReverberationTypeDynamic     = 1,
};


@interface JLModel_Device : NSObject<NSCopying>

@property (copy,  nonatomic) NSString           *mBLE_UUID;

@property (copy,  nonatomic) NSString           *versionProtocol;

@property (copy,  nonatomic) NSString           *versionFirmware;

@property (assign,nonatomic) NSInteger          getMtu;

@property (assign,nonatomic) NSInteger          sendMtu;

@property (assign,nonatomic) JL_SDKType         sdkType;

@property (assign,nonatomic) NSUInteger         battery;

@property (assign,nonatomic) BOOL               isSyncVoice;

@property (assign,nonatomic) NSInteger          lowBattery;

@property (assign,nonatomic) NSUInteger         currentVol;

@property (assign,nonatomic) NSUInteger         maxVol;

@property (copy,  nonatomic) NSString           *btAddr;

@property (copy,  nonatomic) NSString           *license;

@property (assign,nonatomic) JL_DevicePlatform  platform;

@property (assign,nonatomic) JL_DeviceBTStatus  btStatus;

///BIT(0):BT BIT(1):MUSIC BIT(2):RTC
@property (assign,nonatomic) uint32_t           function __deprecated_msg("，deviceFuncs");

@property (assign,nonatomic) JL_FunctionCode    currentFunc;

@property (assign,nonatomic) uint8_t            funcOnlineStatus;

@property (strong,nonatomic) JLModelDevFunc     *deviceFuncs;

@property (copy,  nonatomic) NSString           *versionUBoot;

@property (assign,nonatomic) JL_Partition       partitionType __deprecated_msg("，JL_OTAManager");


@property (assign,nonatomic) BOOL               isSupportReuseSpaceOTA __deprecated_msg("，JL_OTAManager");


@property (assign,nonatomic) JL_OtaStatus       otaStatus __deprecated_msg("，JL_OTAManager");

@property (assign,nonatomic) JL_OtaHeadset      otaHeadset __deprecated_msg("，JL_OTAManager");

@property (assign,nonatomic) JL_OtaWatch        otaWatch __deprecated_msg("，JL_OTAManager");

@property (assign,nonatomic) JLOtaSourcesExtendMode   otaSourceMode __deprecated_msg("，JL_OTAManager");


@property (copy,  nonatomic) NSString           *pidvid;

@property (copy,  nonatomic) NSString           *authKey;

@property (copy,  nonatomic) NSString           *proCode;

@property (assign,nonatomic) JL_BootLoader      bootLoaderType;

@property (assign,nonatomic) JL_OtaBleAllowConnect otaBleAllowConnect;

@property (assign,nonatomic) JL_BLEOnly         bleOnly;

@property (copy,  nonatomic) NSString           *bleAddr;

@property (assign,nonatomic) JL_FasheEnable     fasheEnable;

@property (assign,nonatomic) JL_FasheType       fasheType;

@property (assign,nonatomic) JL_MD5Type         md5Type;

@property (assign,nonatomic) JL_GameType        gameType;

@property (assign,nonatomic) BOOL               isSupportGameModel;

@property (assign,nonatomic) JL_SearchType      searchType;

@property (assign,nonatomic) JL_KaraokeType     karaokeType;

@property (assign,nonatomic) JL_KaraokeEQType   karaokeEQType;

@property (assign,nonatomic) JL_FlashType       flashType;

@property (assign,nonatomic) JL_AncType         ancType;

@property (assign,nonatomic) JL_AudioFileType   audioFileType;

@property (assign,nonatomic) BOOL               isSupportLog;

@property (assign,nonatomic) BOOL               isSupportDhaFitting;

///Fitting information interaction: version, channel number, channel frequency
@property (strong,nonatomic) DhaFittingInfo     *dhaFitInfo;

/// Fitting interrupted/opened object, only for listening
@property (strong,nonatomic) DhaFittingSwitch   *dhaFitSwitch;

/// Array of channel gain values, first left ear then right ear, the number is the same as the one returned in the fitting information
@property (strong,nonatomic) NSArray<NSNumber *> *dhaFittingList;

@property (assign,nonatomic) BOOL               isSupportDevConfigInfo;

@property (assign,nonatomic) BOOL               isSupportAutoANC;

@property (assign,nonatomic) int                pitchLow;

@property (assign,nonatomic) int                pitchHigh;

@property (copy,  nonatomic) JLModel_Flash      *flashInfo;

/// Specify in the device information, whether the external SD card/U disk pins are multiplexed
@property (assign,nonatomic) BOOL               devPinMultiplex;


/*--- File INFO ---*/
@property (assign,nonatomic) JL_FileHandleType        currentFileHandleType;
@property (assign,nonatomic,readonly) JL_CardType     currentCardType;
@property (assign,nonatomic) JL_FileSubcontractTransferCrc16Type fileSubcontractTransferCrc16Type;
@property (assign,nonatomic) JL_ReadFileInNewWayType readFileInNewWayType;
@property (assign,nonatomic) JL_SmallFileWayType smallFileWayType;

@property (copy,  nonatomic) NSArray            *cardArray __attribute__((deprecated ( "Use the instance property cardArray of the JLModelCardInfo class instead, this property is about to become invalid")));
///USB   handle
@property (copy,  nonatomic) NSString           *handleUSB __attribute__((deprecated ( "Use the instance property usbHandle of the JLModelCardInfo class instead, this property is about to become invalid")));
///SD_0  handle
@property (copy,  nonatomic) NSString           *handleSD_0 __attribute__((deprecated ( "Use the instance property sd0Handle of the JLModelCardInfo class instead, this property is about to become invalid")));
///SD_1  handle
@property (copy,  nonatomic) NSString           *handleSD_1 __attribute__((deprecated ( "Use the instance property sd1Handle of the JLModelCardInfo class instead, this property is about to become invalid")));
///Flash handle
@property (copy,  nonatomic) NSString           *handleFlash __attribute__((deprecated ( "Use the instance property flashHandle of the JLModelCardInfo class instead, this property is about to become invalid")));
///Flash2 handle
@property (copy,  nonatomic) NSString           *handleFlash2 __attribute__((deprecated ( "Use the instance property flash2Handle of the JLModelCardInfo class instead, this property is about to become invalid")));

///Flash3 handle
@property (copy,  nonatomic) NSString           *handleFlash3 __attribute__((deprecated ( "Use the instance property flash3Handle of the JLModelCardInfo class instead, this property is about to become invalid")));

///USB    handle Data
@property (copy,  nonatomic) NSData             *handleUSBData __attribute__((deprecated ( "Use the instance property usbHandle of the JLModelCardInfo class instead, this property is about to become invalid")));
///SD_0   handle Data
@property (copy,  nonatomic) NSData             *handleSD_0Data __attribute__((deprecated ( "Use the instance property sd0Handle of the JLModelCardInfo class instead, this property is about to become invalid")));
///SD_1   handle Data
@property (copy,  nonatomic) NSData             *handleSD_1Data __attribute__((deprecated ( "Use the instance property sd1Handle of the JLModelCardInfo class instead, this property is about to become invalid")));
///Flash  handle Data
@property (copy,  nonatomic) NSData             *handleFlashData __attribute__((deprecated ( "Use the instance property flashHandle of the JLModelCardInfo class instead, this property is about to become invalid")));
///Flash2 handle Data
@property (copy,  nonatomic) NSData             *handleFlash2Data __attribute__((deprecated ( "Use the instance property flash2Handle of the JLModelCardInfo class instead, this property is about to become invalid")));

///Flash3 handle Data
@property (copy,  nonatomic) NSData             *handleFlash3Data __attribute__((deprecated ( "Use the instance property flash3Handle of the JLModelCardInfo class instead, this property is about to become invalid")));

@property (strong, nonatomic)JLModelCardInfo    *cardInfo;

@property (copy,  nonatomic) NSString           *errReason;

@property (assign,nonatomic) uint16_t           fmtxPoint;
@property (assign,nonatomic) uint8_t            mTWS_Mode;
@property (assign,nonatomic) uint8_t            mTWS_Status;
@property (copy  ,nonatomic) NSString           *mTWS_Addr;
@property (copy  ,nonatomic) JLModel_ANC        *mAncModeCurrent;
@property (copy  ,nonatomic) NSMutableArray     *mAncModeArray;
@property (assign,nonatomic) JL_CALLType        mCallType;

@property (strong,nonatomic) NSArray            *reverberationTypes;
@property (assign,nonatomic) int                reverberationSwitchState;
@property (assign,nonatomic) int                depthValue;
@property (assign,nonatomic) int                intensityValue;
@property (assign,nonatomic) int                dynamicLimiterValue;

@property (assign,nonatomic)uint64_t kalaokMask __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SoundCardManager class instead, this property is about to become invalid")));

@property (strong,nonatomic)NSArray *mKaraokeMicFrequencyArray __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SoundCardManager class instead, this property is about to become invalid")));

@property (strong,nonatomic)NSArray *mKaraokeMicEQArray __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SoundCardManager class instead, this property is about to become invalid")));

@property (assign,nonatomic) JL_EQMode          eqMode __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SystemEQ class instead, this property is about to become invalid")));;
@property (copy,  nonatomic) NSArray            *eqArray __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SystemEQ class instead, this property is about to become invalid")));;
@property (copy,  nonatomic) NSArray            *eqCustomArray __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SystemEQ class instead, this property is about to become invalid")));;

@property (copy,  nonatomic) NSArray            *eqFrequencyArray __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SystemEQ class instead, this property is about to become invalid")));;
@property (assign,nonatomic) JL_EQType          eqType __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SystemEQ class instead, this property is about to become invalid")));;

@property (strong,nonatomic) NSArray            *eqDefaultArray __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SystemEQ class instead, this property is about to become invalid")));;

@property (assign,nonatomic) JL_LightState      lightState __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
@property (assign,nonatomic) JL_LightMode       lightMode __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
@property (assign,nonatomic) uint8_t            lightRed __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
@property (assign,nonatomic) uint8_t            lightGreen __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
@property (assign,nonatomic) uint8_t            lightBlue __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
@property (assign,nonatomic) JL_LightFlashModeIndex lightFlashIndex __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
@property (assign,nonatomic) JL_LightFlashModeFrequency lightFrequencyIndex __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
@property (assign,nonatomic) JL_LightSceneMode  lightSceneIndex __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
@property (assign,nonatomic) uint16_t           lightHue __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
@property (assign,nonatomic) uint8_t            lightSat __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
@property (assign,nonatomic) uint8_t            lightLightness __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));


//MARK: -  BT INFO
@property (strong,nonatomic) NSString           *ID3_Title;
@property (strong,nonatomic) NSString           *ID3_Artist;
@property (strong,nonatomic) NSString           *ID3_AlBum;
@property (assign,nonatomic) uint8_t            ID3_Number;
@property (assign,nonatomic) uint16_t           ID3_Total;
@property (strong,nonatomic) NSString           *ID3_Genre;
@property (assign,nonatomic) uint32_t           ID3_Time;
@property (assign,nonatomic) uint8_t            ID3_Status;

@property (assign,nonatomic) uint32_t           ID3_CurrentTime;

//MARK: -  Music INFO
@property (assign,nonatomic) JL_MusicStatus     playStatus __attribute__((deprecated ( "Use the instance property rtcVersion of the JLDevPlayerCtrl class instead, this property is about to become invalid")));

@property (assign,nonatomic) JL_MusicMode       playMode __attribute__((deprecated ( "Use the instance property rtcVersion of the JLDevPlayerCtrl class instead, this property is about to become invalid")));

@property (assign,nonatomic) uint32_t           currentClus __attribute__((deprecated ( "Use the instance property rtcVersion of the JLDevPlayerCtrl class instead, this property is about to become invalid")));

@property (assign,nonatomic) uint32_t           currentTime __attribute__((deprecated ( "Use the instance property rtcVersion of the JLDevPlayerCtrl class instead, this property is about to become invalid")));

@property (assign,nonatomic) uint32_t           tolalTime __attribute__((deprecated ( "Use the instance property rtcVersion of the JLDevPlayerCtrl class instead, this property is about to become invalid")));

@property (assign,nonatomic) JL_CardType        currentCard __attribute__((deprecated ( "Use the instance property rtcVersion of the JLDevPlayerCtrl class instead, this property is about to become invalid")));

@property (copy,  nonatomic) NSString           *fileName __attribute__((deprecated ( "Use the instance property rtcVersion of the JLDevPlayerCtrl class instead, this property is about to become invalid")));

@property (copy,  nonatomic) NSString           *typeSupport;
    
//MARK: -  RTC INFO

@property (assign,nonatomic) uint8_t             rtcVersion __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_AlarmClockManager class instead, this property is about to become invalid")));

@property (assign,nonatomic) JL_RTCAlarmType     rtcAlarmType __attribute__((deprecated ( "Use the instance property rtcAlarmType of the JL_AlarmClockManager class instead, this property is about to become invalid")));

@property (strong,nonatomic) JLModel_RTC         *rtcModel __attribute__((deprecated ( "Use the instance property rtcModel of the JL_AlarmClockManager class instead, this property is about to become invalid")));

@property (strong,nonatomic) NSMutableArray      *rtcAlarms __attribute__((deprecated ( "Use the instance property rtcAlarms of the JL_AlarmClockManager class instead, this property is about to become invalid")));

@property (strong,nonatomic) NSMutableArray      *rtcDfRings __attribute__((deprecated ( "Use the instance property rtcDfRings of the JL_AlarmClockManager class instead, this property is about to become invalid")));

//MARK: -  LineIn INFO

@property (assign,nonatomic) JL_LineInStatus    lineInStatus;


@property (assign,nonatomic) JL_FMStatus        fmStatus;

///76.5-108.0Mhz
///87.5-108.0Mhz
@property (assign,nonatomic) JL_FMMode          fmMode;

@property (strong,nonatomic) JLModel_FM          *currentFm;

@property (strong,nonatomic) NSArray            *fmArray;

//MARK: -  custom version info
@property(strong,nonatomic) NSData              *customizeInfo;


-(void)cleanMe;
+(void)observeModelProperty:(NSString*)prty Action:(SEL)action Own:(id)own __attribute__((deprecated("This method has been abandoned. You can use the system's KVO to monitor object changes.")));
+(void)removeModelProperty:(NSString*)prty Own:(id)own __attribute__((deprecated("This method has been abandoned. You can use the system's KVO to monitor object changes.")));

#pragma mark - Vendor SDK
-(void)deviceInfoData:(NSData*)infoData;

#pragma mark - Vendor SDK
-(void)deviceModeInfoData:(NSData*)infoData;


@end

NS_ASSUME_NONNULL_END
