//
//  JLModel_Device.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/10/15.
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
    JL_DevicePlatformTuring         = 0,    //适用于【图灵】
    JL_DevicePlatformDeepbrain      = 1,    //适用于【Deepbrain】
    JL_DevicePlatformUnknown,
};
typedef NS_ENUM(UInt8, JL_SDKType) {
    JL_SDKTypeAI                    = 0x0,    //AI SDK  AC692x
    JL_SDKTypeST                    = 0x1,    //标准 SDK AC692x
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
    JL_SDKTypeChargingCase          = 0x0C,   //ChargingCase 彩屏充电仓
    JL_SDKType707nWATCH             = 0x0D,   //707N Watch
    JL_SDKTypeUnknown,
};
typedef NS_ENUM(UInt8, JL_FunctionCode) {
    JL_FunctionCodeBT               = 0,    //BT
    JL_FunctionCodeMUSIC            = 1,    //音乐
    JL_FunctionCodeRTC              = 2,    //闹钟
    JL_FunctionCodeLINEIN           = 3,    //LineIn
    JL_FunctionCodeFM               = 4,    //FM
    JL_FunctionCodeLIGHT            = 5,    //LIGHT
    JL_FunctionCodeFMTX             = 6,    //发射频点
    JL_FunctionCodeEQ               = 7,    //EQ
    JL_FunctionCodeSPDIF            = 8,    //SPDIF
    JL_FunctionCodePCServer         = 9,    //PCServer
    JL_FunctionCodeCOMMON           = 0xff, //通用
};

typedef NS_ENUM(UInt8, JL_FCmdMusic) {
    JL_FCmdMusicPP                  = 0x01, //PP按钮
    JL_FCmdMusicPREV                = 0x02, //上一曲
    JL_FCmdMusicNEXT                = 0x03, //下一曲
    JL_FCmdMusicMODE                = 0x04, //切换播放模式
    JL_FCmdMusicEQ                  = 0x05, //EQ
    JL_FCmdMusicFastBack            = 0x06, //快退
    JL_FCmdMusicFastPlay            = 0x07, //快进
};

typedef NS_ENUM(UInt8, JL_OtaBleAllowConnect) {
    JL_OtaBleAllowConnectYES        = 0,    //OTA 允许BLE连接
    JL_OtaBleAllowConnectNO         = 1,    //OTA 禁止BLE连接
    JL_OtaBleAllowConnectUnknow     = 2,    //未定义
};
typedef NS_ENUM(UInt8, JL_BLEOnly) {        //是否仅仅支持BLE
    JL_BLEOnlyNO                    = 0,    //否
    JL_BLEOnlyYES                   = 1,    //是
};
typedef NS_ENUM(UInt8, JL_FasheEnable) {    //是否发射模式
    JL_FasheEnableNO                = 0,    //否
    JL_FasheEnableYES               = 1,    //是
};
typedef NS_ENUM(UInt8, JL_FasheType) {      //当前是否为发射模式
    JL_FasheTypeNO                  = 0,    //否
    JL_FasheTypeYES                 = 1,    //是
};
typedef NS_ENUM(UInt8, JL_MD5Type) {        //是否支持MD5校验
    JL_MD5TypeNO                    = 0,    //否
    JL_MD5TypeYES                   = 1,    //是
};
typedef NS_ENUM(UInt8, JL_GameType) {       //是否为游戏模式
    JL_GameTypeNO                   = 0,    //否
    JL_GameTypeYES                  = 1,    //是
};
typedef NS_ENUM(UInt8, JL_SearchType) {     //是否支持查找设备
    JL_SearchTypeNO                 = 0,    //否
    JL_SearchTypeYES                = 1,    //是
};
typedef NS_ENUM(UInt8, JL_KaraokeType) {    //是否支持卡拉OK
    JL_KaraokeTypeNO                = 0,    //否
    JL_KaraokeTypeYES               = 1,    //是
};
typedef NS_ENUM(UInt8,JL_KaraokeEQType){    //是否禁止app调节设备音效
    JL_KaraokeEQTypeNO              = 0,    //不禁止
    JL_KaraokeEQTypeYES             = 1,    //禁止
};
typedef NS_ENUM(UInt8,JL_FlashType){        //是否支持外挂Flash
    JL_FlashTypeNO                  = 0,    //不支持
    JL_FlashTypeYES                 = 1,    //支持
};
typedef NS_ENUM(UInt8,JL_AncType){          //是否支持ANC
    JL_AncTypeNO                    = 0,    //不支持
    JL_AncTypeYES                   = 1,    //支持
};
typedef NS_ENUM(UInt8, JL_AudioFileType) {  //是否支持音频文件传输
    JL_AudioFileTypeNO              = 0,    //否
    JL_AudioFileTypeYES             = 1,    //是
};
typedef NS_ENUM(UInt8, JL_FileSubcontractTransferCrc16Type){//文件分包传输是否支持crc16方式
    JL_FileSubcontractTransferCrc16TypeNO      = 0,    //不支持
    JL_FileSubcontractTransferCrc16TypeYES     = 1,    //支持
};
typedef NS_ENUM(UInt8, JL_ReadFileInNewWayType){       //是否以新的方式读取固件文件
    JL_ReadFileInNewWayTypeNO                  = 0,    //不支持
    JL_ReadFileInNewWayTypeYES                 = 1,    //支持
};

typedef NS_ENUM(UInt8, JL_SmallFileWayType){           //是否支持小文件传输
    JL_SmallFileWayTypeNO                      = 0,    //不支持
    JL_SmallFileWayTypeYES                     = 1,    //支持
};

typedef NS_ENUM(UInt8,JL_CALLType) {
    JL_CALLType_OFF                 = 0,    //空闲
    JL_CALLType_ON                  = 1,    //通话中
};

typedef NS_ENUM(UInt8, JL_LightState) {
    JL_LightStateClose          = 0x00, //关闭
    JL_LightStateOpen           = 0x01, //开启
    JL_LightStateSetting        = 0x02, //设置模式
};
typedef NS_ENUM(UInt8, JL_LightMode) {
    JL_LightModeNormal          = 0x00, //彩色模式
    JL_LightModeFlash           = 0x01, //闪烁模式
    JL_LightModeScene           = 0x02, //情景模式
};
typedef NS_ENUM(UInt8, JL_LightFlashModeIndex) {
    JL_LightModeIndexColorfulFlash          = 0x00, //七彩闪烁
    JL_LightModeIndexRedFlash               = 0x01, //红色闪烁
    JL_LightModeIndexOrangeFlash            = 0x02, //橙色闪烁
    JL_LightModeIndexYeallowFlash           = 0x03, //黄色闪烁
    JL_LightModeIndexGreenFlash             = 0x04, //绿色闪烁
    JL_LightModeIndexCyanFlash              = 0x05, //青色闪烁
    JL_LightModeIndexBlueFlash              = 0x06, //蓝色闪烁
    JL_LightModeIndexPurpleFlash            = 0x07, //紫色闪烁
};

typedef NS_ENUM(UInt8, JL_LightFlashModeFrequency) {
    JL_LightFlashModeFrequencyFast          = 0x00, //快闪
    JL_LightFlashModeFrequencySlow          = 0x01, //慢闪
    JL_LightFlashModeFrequencyNormal        = 0x02, //缓闪
    JL_LightFlashModeFrequencyMusic         = 0x03, //音乐闪烁
};

typedef NS_ENUM(UInt8, JL_LightSceneMode) {
    JL_LightSceneModeRainbow                = 0x00, //彩虹
    JL_LightSceneModeHeartbeat              = 0x01, //心跳
    JL_LightSceneModeCandlelight            = 0x02, //烛火
    JL_LightSceneModeNightLight             = 0x03, //夜灯
    JL_LightSceneModeStage                  = 0x04, //舞台
    JL_LightSceneModeDiffuseColourBreathing = 0x05, //漫彩呼吸
    JL_LightSceneModeDiffuseRedBreathing    = 0x06, //漫红呼吸
    JL_LightSceneModeDiffuseGreenBreathing  = 0x07, //漫绿呼吸
    JL_LightSceneModeDiffuseBlueBreathing   = 0x08, //漫蓝呼吸
    JL_LightSceneModeGreenMood              = 0x09, //绿色心情
    JL_LightSceneModeSettingSunView         = 0x10, //夕阳美景
    JL_LightSceneModeMusicRhythm            = 0x11, //音乐律动
};

typedef NS_ENUM(UInt8, JL_FileHandleType) {     //文件句柄
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
    JL_MusicModeLoopAll             = 0x01, //全部循环
    JL_MusicModeLoopDevice          = 0x02, //单设备循环
    JL_MusicModeLoopOne             = 0x03, //单曲循环
    JL_MusicModeRandomDevice        = 0x04, //单设备随机
    JL_MusicModeLoopFolder          = 0x05, //文件夹循环
};

typedef NS_ENUM(UInt8, JL_MusicStatus) {
    JL_MusicStatusPlay              = 0x01, //播放
    JL_MusicStatusPause             = 0x00, //暂停
};

typedef NS_ENUM(UInt8, JL_EQType) {         //EQ段数类型
    JL_EQType10                     = 0,    //固定10段式
    JL_EQTypeMutable                = 1,    //动态EQ段
};

//---------------------------------------------------------//
#pragma mark - RTC
typedef NS_ENUM(UInt8, JL_RTCAlarmType) {   //是否支持闹铃设置
    JL_RTCAlarmTypeNO               = 0,    //不支持
    JL_RTCAlarmTypeYES              = 1,    //支持
};
//---------------------------------------------------------//
#pragma mark - LINEIN
typedef NS_ENUM(UInt8, JL_LineInStatus) {
    JL_LineInStatusPause            = 0x00, //暂停
    JL_LineInStatusPlay             = 0x01, //播放
    JL_LineInStatusUnknown,
};
//---------------------------------------------------------//
#pragma mark - FM
typedef NS_ENUM(UInt8, JL_FMStatus) {
    JL_FMStatusPause                = 0x01, //播放
    JL_FMStatusPlay                 = 0x02, //暂停
    JL_FMStatusSearching            = 0x03, //搜索中
    JL_FMStatusUnknown,
};
typedef NS_ENUM(UInt8, JL_FMMode) {
    JL_FMMode875Mhz                 = 0x00, //87.5-108.0Mhz
    JL_FMMode760Mhz                 = 0x01, //76.5-108.0Mhz
    JL_FMModeUnknown,
};

typedef NS_ENUM(UInt8,JL_ReverberationType) {
    JL_ReverberationTypeNormal      = 0,     //混响
    JL_ReverberationTypeDynamic     = 1,     //限幅器
};


@interface JLModel_Device : NSObject<NSCopying>

///设备UUID
@property (copy,  nonatomic) NSString           *mBLE_UUID;

///协议版本
@property (copy,  nonatomic) NSString           *versionProtocol;

///固件版本
@property (copy,  nonatomic) NSString           *versionFirmware;

/// 单包固件最大发送值，APP单次能收到最大的值
@property (assign,nonatomic) NSInteger          getMtu;

/// 单包固件最大接收值（MaxMtu）APP单次可发送最大值
@property (assign,nonatomic) NSInteger          sendMtu;

///SDK类型
@property (assign,nonatomic) JL_SDKType         sdkType;

///电量0~9
@property (assign,nonatomic) NSUInteger         battery;

/// 是否支持音量同步
@property (assign,nonatomic) BOOL               isSyncVoice;

/// 最低允许升级资源/OTA电量
@property (assign,nonatomic) NSInteger          lowBattery;

///当前音量
@property (assign,nonatomic) NSUInteger         currentVol;

///最大音量
@property (assign,nonatomic) NSUInteger         maxVol;

///经典蓝牙地址
@property (copy,  nonatomic) NSString           *btAddr;

///平台序列号
@property (copy,  nonatomic) NSString           *license;

///平台类型（图灵，Deepbrain）
@property (assign,nonatomic) JL_DevicePlatform  platform;

///经典蓝牙状态
@property (assign,nonatomic) JL_DeviceBTStatus  btStatus;

///BIT(0):BT BIT(1):MUSIC BIT(2):RTC
@property (assign,nonatomic) uint32_t           function __deprecated_msg("已过时，可使用deviceFuncs");

///当前处于的模式
@property (assign,nonatomic) JL_FunctionCode    currentFunc;

///USb,SD,LineIn,网络电台是否在线
@property (assign,nonatomic) uint8_t            funcOnlineStatus;

/// 设备功能模式支持
@property (strong,nonatomic) JLModelDevFunc     *deviceFuncs;

///uboot版本
@property (copy,  nonatomic) NSString           *versionUBoot;

///设备单、双备份
@property (assign,nonatomic) JL_Partition       partitionType __deprecated_msg("已过时，可使用JL_OTAManager");


/// 是否支持复用空间进行 OTA
@property (assign,nonatomic) BOOL               isSupportReuseSpaceOTA __deprecated_msg("已过时，可使用JL_OTAManager");


///OTA状态
@property (assign,nonatomic) JL_OtaStatus       otaStatus __deprecated_msg("已过时，可使用JL_OTAManager");

///耳机单备份 是否需要强制升级
@property (assign,nonatomic) JL_OtaHeadset      otaHeadset __deprecated_msg("已过时，可使用JL_OTAManager");

///手表资源 是否需要强制升级
@property (assign,nonatomic) JL_OtaWatch        otaWatch __deprecated_msg("已过时，可使用JL_OTAManager");

///资源是否需要强制升级
@property (assign,nonatomic) JLOtaSourcesExtendMode   otaSourceMode __deprecated_msg("已过时，可使用JL_OTAManager");


///厂商ID
@property (copy,  nonatomic) NSString           *pidvid;

///授权Key
@property (copy,  nonatomic) NSString           *authKey;

///授权Code
@property (copy,  nonatomic) NSString           *proCode;

///是否下载BootLoader
@property (assign,nonatomic) JL_BootLoader      bootLoaderType;

///OTA是否允许BLE连接
@property (assign,nonatomic) JL_OtaBleAllowConnect otaBleAllowConnect;

///是否仅仅支持BLE
@property (assign,nonatomic) JL_BLEOnly         bleOnly;

///ble蓝牙地址
@property (copy,  nonatomic) NSString           *bleAddr;

///是否支持发射模式
@property (assign,nonatomic) JL_FasheEnable     fasheEnable;

///当前是否为发射模式
@property (assign,nonatomic) JL_FasheType       fasheType;

///是否支持MD5固件校验
@property (assign,nonatomic) JL_MD5Type         md5Type;

///是否为游戏模式
@property (assign,nonatomic) JL_GameType        gameType;

///是否支持游戏模式
@property (assign,nonatomic) BOOL               isSupportGameModel;

///是否支持查找设备
@property (assign,nonatomic) JL_SearchType      searchType;

///是否支持卡拉OK
@property (assign,nonatomic) JL_KaraokeType     karaokeType;

///是否禁止app调节设备音效
@property (assign,nonatomic) JL_KaraokeEQType   karaokeEQType;

///是否外挂flash
@property (assign,nonatomic) JL_FlashType       flashType;

///是否支持ANC
@property (assign,nonatomic) JL_AncType         ancType;

///是否支持音频文件传输功能
@property (assign,nonatomic) JL_AudioFileType   audioFileType;

/// 是否支持日志获取
@property (assign,nonatomic) BOOL               isSupportLog;

/// 是否支持辅听设置
@property (assign,nonatomic) BOOL               isSupportDhaFitting;

///验配信息交互：版本、通道数、通道频率
///Fitting information interaction: version, channel number, channel frequency
@property (strong,nonatomic) DhaFittingInfo     *dhaFitInfo;

/// 验配中断/开启的对象，仅限于监听
/// Fitting interrupted/opened object, only for listening
@property (strong,nonatomic) DhaFittingSwitch   *dhaFitSwitch;

/// 通道增益值数组,先左耳后右耳，个数和验配信息中返回的一致
/// Array of channel gain values, first left ear then right ear, the number is the same as the one returned in the fitting information
@property (strong,nonatomic) NSArray<NSNumber *> *dhaFittingList;

/// 是否支持获取设备配置信息
@property (assign,nonatomic) BOOL               isSupportDevConfigInfo;

/// 是否支持自适应ANC
@property (assign,nonatomic) BOOL               isSupportAutoANC;

///低音
@property (assign,nonatomic) int                pitchLow;

///高音
@property (assign,nonatomic) int                pitchHigh;

///外挂flash信息
@property (copy,  nonatomic) JLModel_Flash      *flashInfo;

/// 设备信息中指明，外部SD卡/U盘引脚是否被复用
/// Specify in the device information, whether the external SD card/U disk pins are multiplexed
@property (assign,nonatomic) BOOL               devPinMultiplex;


/*--- File INFO ---*/
///当前文件传输句柄
@property (assign,nonatomic) JL_FileHandleType        currentFileHandleType;
///当前文件所存放的位置
@property (assign,nonatomic,readonly) JL_CardType     currentCardType;
///文件分包传输是否支持crc16方式
@property (assign,nonatomic) JL_FileSubcontractTransferCrc16Type fileSubcontractTransferCrc16Type;
///是否以新的方式读取固件文件
@property (assign,nonatomic) JL_ReadFileInNewWayType readFileInNewWayType;
///是否小文件方式传输
@property (assign,nonatomic) JL_SmallFileWayType smallFileWayType;

/*--- 公用INFO ---*/
//MARK: - 存储信息
///卡的数组
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

/// 设备存储信息（卡信息）
@property (strong, nonatomic)JLModelCardInfo    *cardInfo;

/// 错误原因
@property (copy,  nonatomic) NSString           *errReason;

/// 发射频点
@property (assign,nonatomic) uint16_t           fmtxPoint;
/// 0x00:普通模式 0x01:发射模式
@property (assign,nonatomic) uint8_t            mTWS_Mode;
/// 0x00:未连接   0x01:已连接
@property (assign,nonatomic) uint8_t            mTWS_Status;
/// 发射模式中，连接的外设地址
@property (copy  ,nonatomic) NSString           *mTWS_Addr;
/// 当前ANC的模式
@property (copy  ,nonatomic) JLModel_ANC        *mAncModeCurrent;
/// ANC模式数组
@property (copy  ,nonatomic) NSMutableArray     *mAncModeArray;
///通话状态
@property (assign,nonatomic) JL_CALLType        mCallType;

/// 混响所支持的类型
@property (strong,nonatomic) NSArray            *reverberationTypes;
/// 混响的开关
@property (assign,nonatomic) int                reverberationSwitchState;
/// 深度值
@property (assign,nonatomic) int                depthValue;
/// 混响度值
@property (assign,nonatomic) int                intensityValue;
/// 混响幅值
@property (assign,nonatomic) int                dynamicLimiterValue;

//MARK: - 卡拉OK
///卡拉OK 固件返回的掩码
@property (assign,nonatomic)uint64_t kalaokMask __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SoundCardManager class instead, this property is about to become invalid")));

///卡拉OK 频率数组
@property (strong,nonatomic)NSArray *mKaraokeMicFrequencyArray __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SoundCardManager class instead, this property is about to become invalid")));

///卡拉OK EQ数组
@property (strong,nonatomic)NSArray *mKaraokeMicEQArray __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SoundCardManager class instead, this property is about to become invalid")));

//MARK: - EQ 属性列表
/// EQ模式
@property (assign,nonatomic) JL_EQMode          eqMode __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SystemEQ class instead, this property is about to become invalid")));;
/// EQ参数值（只适用于EQ Mode == CUSTOM情况）
@property (copy,  nonatomic) NSArray            *eqArray __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SystemEQ class instead, this property is about to become invalid")));;
///自定义EQ
@property (copy,  nonatomic) NSArray            *eqCustomArray __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SystemEQ class instead, this property is about to become invalid")));;

///EQ频率
@property (copy,  nonatomic) NSArray            *eqFrequencyArray __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SystemEQ class instead, this property is about to become invalid")));;
///EQ段数类型
@property (assign,nonatomic) JL_EQType          eqType __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SystemEQ class instead, this property is about to become invalid")));;

///EQ的预设值数组 数组元素类型-->【JLEQModel】
@property (strong,nonatomic) NSArray            *eqDefaultArray __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_SystemEQ class instead, this property is about to become invalid")));;

//MARK: - 灯光属性列表
/// 0:关闭 1：打开 2：设置模式(彩色/闪烁/情景)
@property (assign,nonatomic) JL_LightState      lightState __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
/// 0：彩色 1:闪烁 2: 情景
@property (assign,nonatomic) JL_LightMode       lightMode __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
/// 灯光红色
@property (assign,nonatomic) uint8_t            lightRed __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
/// 灯光绿色
@property (assign,nonatomic) uint8_t            lightGreen __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
/// 灯光蓝色
@property (assign,nonatomic) uint8_t            lightBlue __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
/// 闪烁模式Index
@property (assign,nonatomic) JL_LightFlashModeIndex lightFlashIndex __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
/// 闪烁频率Index
@property (assign,nonatomic) JL_LightFlashModeFrequency lightFrequencyIndex __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
/// 情景模式Index
@property (assign,nonatomic) JL_LightSceneMode  lightSceneIndex __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
/// 色调，范围0-360
@property (assign,nonatomic) uint16_t           lightHue __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
/// 饱和度，0-100
@property (assign,nonatomic) uint8_t            lightSat __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));
/// 亮度，0-100
@property (assign,nonatomic) uint8_t            lightLightness __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_LightManager class instead, this property is about to become invalid")));


//MARK: -  BT INFO
@property (strong,nonatomic) NSString           *ID3_Title;
@property (strong,nonatomic) NSString           *ID3_Artist;
@property (strong,nonatomic) NSString           *ID3_AlBum;
@property (assign,nonatomic) uint8_t            ID3_Number;
@property (assign,nonatomic) uint16_t           ID3_Total;
@property (strong,nonatomic) NSString           *ID3_Genre;
@property (assign,nonatomic) uint32_t           ID3_Time;
/// 0x01:播放 0x00:暂停
@property (assign,nonatomic) uint8_t            ID3_Status;

@property (assign,nonatomic) uint32_t           ID3_CurrentTime;

//MARK: -  Music INFO
///播放状态
@property (assign,nonatomic) JL_MusicStatus     playStatus __attribute__((deprecated ( "Use the instance property rtcVersion of the JLDevPlayerCtrl class instead, this property is about to become invalid")));

///播放模式
@property (assign,nonatomic) JL_MusicMode       playMode __attribute__((deprecated ( "Use the instance property rtcVersion of the JLDevPlayerCtrl class instead, this property is about to become invalid")));

///当前播放文件的簇号
@property (assign,nonatomic) uint32_t           currentClus __attribute__((deprecated ( "Use the instance property rtcVersion of the JLDevPlayerCtrl class instead, this property is about to become invalid")));

///当前时间
@property (assign,nonatomic) uint32_t           currentTime __attribute__((deprecated ( "Use the instance property rtcVersion of the JLDevPlayerCtrl class instead, this property is about to become invalid")));

///总时长
@property (assign,nonatomic) uint32_t           tolalTime __attribute__((deprecated ( "Use the instance property rtcVersion of the JLDevPlayerCtrl class instead, this property is about to become invalid")));

///当前卡
@property (assign,nonatomic) JL_CardType        currentCard __attribute__((deprecated ( "Use the instance property rtcVersion of the JLDevPlayerCtrl class instead, this property is about to become invalid")));

///名字
@property (copy,  nonatomic) NSString           *fileName __attribute__((deprecated ( "Use the instance property rtcVersion of the JLDevPlayerCtrl class instead, this property is about to become invalid")));

///目录浏览文件类型(所支持解码音频格式）
@property (copy,  nonatomic) NSString           *typeSupport;
    
//MARK: -  RTC INFO

///RTC 版本
@property (assign,nonatomic) uint8_t             rtcVersion __attribute__((deprecated ( "Use the instance property rtcVersion of the JL_AlarmClockManager class instead, this property is about to become invalid")));

///是否支持闹铃设置
@property (assign,nonatomic) JL_RTCAlarmType     rtcAlarmType __attribute__((deprecated ( "Use the instance property rtcAlarmType of the JL_AlarmClockManager class instead, this property is about to become invalid")));

///设备当前时间
@property (strong,nonatomic) JLModel_RTC         *rtcModel __attribute__((deprecated ( "Use the instance property rtcModel of the JL_AlarmClockManager class instead, this property is about to become invalid")));

///设备闹钟数组
@property (strong,nonatomic) NSMutableArray      *rtcAlarms __attribute__((deprecated ( "Use the instance property rtcAlarms of the JL_AlarmClockManager class instead, this property is about to become invalid")));

///默认铃声
@property (strong,nonatomic) NSMutableArray      *rtcDfRings __attribute__((deprecated ( "Use the instance property rtcDfRings of the JL_AlarmClockManager class instead, this property is about to become invalid")));

//MARK: -  LineIn INFO

///LineIn状态
@property (assign,nonatomic) JL_LineInStatus    lineInStatus;


//MARK: - Fm 模式
///Fm状态
@property (assign,nonatomic) JL_FMStatus        fmStatus;

///Fm 频段范围
///76.5-108.0Mhz
///87.5-108.0Mhz
@property (assign,nonatomic) JL_FMMode          fmMode;

///当前fm
@property (strong,nonatomic) JLModel_FM          *currentFm;

///Fm列表
@property (strong,nonatomic) NSArray            *fmArray;

//MARK: -  custom version info
/// 自定义版本信息
@property(strong,nonatomic) NSData              *customizeInfo;


-(void)cleanMe;
+(void)observeModelProperty:(NSString*)prty Action:(SEL)action Own:(id)own __attribute__((deprecated("This method has been abandoned. You can use the system's KVO to monitor object changes.")));
+(void)removeModelProperty:(NSString*)prty Own:(id)own __attribute__((deprecated("This method has been abandoned. You can use the system's KVO to monitor object changes.")));

#pragma mark ---> 设备信息
-(void)deviceInfoData:(NSData*)infoData;

#pragma mark ---> 各个模式信息
-(void)deviceModeInfoData:(NSData*)infoData;


@end

NS_ASSUME_NONNULL_END
