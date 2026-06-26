//
//  JL_TwsManager.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/12/17.
//  Modify by EzioChan on 2023/08/18
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_FunctionBaseManager.h>
#import <JL_BLEKit/JL_Tools.h>
#import <JL_BLEKit/JLModel_ANC.h>
#import <JL_BLEKit/JLTwsSupportFuncs.h>

NS_ASSUME_NONNULL_BEGIN

/// TWS earphones Electricity
@interface TwsElectricity:NSObject
@property(nonatomic,assign) BOOL isChargingLeft;

@property(nonatomic,assign) BOOL isChargingRight;

@property(nonatomic,assign) BOOL isChargingCenter;

@property(nonatomic,assign) int powerLeft;

@property(nonatomic,assign) int powerRight;

@property(nonatomic,assign) int powerCenter;

@end



@interface JL_TwsManager : JL_FunctionBaseManager

@property(nonatomic,strong,readonly)JLTwsSupportFuncs *supports;

///TWS earphones Electricity
@property (nonatomic,strong)TwsElectricity *electricity;

@property (nonatomic,strong)NSString *edrName;

@property (nonatomic,strong)NSArray *keySettings;

@property (nonatomic,assign)int ledScen;

@property (nonatomic,assign)int ledEffect;

@property (nonatomic,assign)int micMode;

@property (nonatomic,assign)int workMode;

@property (nonatomic,assign)uint16_t vid;

@property (nonatomic,assign)uint16_t uid;

@property (nonatomic,assign)uint16_t pid;

@property (nonatomic,assign)uint32_t linkTime;

@property (nonatomic,assign)uint8_t earEntryDection;

@property (nonatomic,strong)NSString *deviceLanguage;

@property (nonatomic,strong)NSArray *ancModels;

/// HeadSetInfoDict
@property (nonatomic,strong)NSDictionary *_Nullable headSetInfoDict;


@property(nonatomic,readonly,assign)BOOL dragWithMore;



-(void)cmdHeadsetEdrName:(NSData*)name;

#pragma mark - Vendor SDK
typedef NS_ENUM(UInt8, JL_HeadsetButtonSettingKey) {
    JL_HeadsetButtonSettingKeyOnlyLeftEar      = 0x01,
    JL_HeadsetButtonSettingKeyOnlyRightEar     = 0x02,
};
typedef NS_ENUM(UInt8, JL_HeadsetButtonSettingAction) {
    JL_HeadsetButtonSettingActionClick            = 0x01,
    JL_HeadsetButtonSettingActionDoubleClick      = 0x02,
};
typedef NS_ENUM(UInt8, JL_HeadsetButtonSettingFunction) {
    JL_HeadsetButtonSettingFunctionNone            = 0x00,
    JL_HeadsetButtonSettingFunctionBoot            = 0x01,
    JL_HeadsetButtonSettingFunctionTurnOff         = 0x02,
    JL_HeadsetButtonSettingFunctionPlayPrevious    = 0x03,
    JL_HeadsetButtonSettingFunctionPlayNext        = 0x04,
    JL_HeadsetButtonSettingFunctionPlayOrPause     = 0x05,
    JL_HeadsetButtonSettingFunctionAnswerOrHangup  = 0x06,
    JL_HeadsetButtonSettingFunctionReject          = 0x07,
    JL_HeadsetButtonSettingFunctionTakePhoto       = 0x08,
};
/**
            0x01
            0x02
            0x03
            0x04
            0x05    /
            0x06    /
            0x07
            0x08
 */
-(void)cmdHeadsetKeySettingKey:(uint8_t)key
                        Action:(uint8_t)act
                      Function:(uint8_t)fuc;

#pragma mark - Vendor SDK

typedef NS_ENUM(UInt8, JL_HeadsetScene) {
    JL_HeadsetSceneNotPaired                  = 0x01,
    JL_HeadsetSceneDisConnected               = 0x02,
    JL_HeadsetSceneConnected                  = 0x03,
    JL_HeadsetScenePlayDeviceMusic            = 0x04,
    JL_HeadsetScenePauseDeviceMusic           = 0x05,
    JL_HeadsetScenePlayExternalAudioSource    = 0x06,
    JL_HeadsetScenePauseExternalAudioSource   = 0x07,
};
typedef NS_ENUM(UInt8, JL_HeadsetLedEffect) {
    JL_HeadsetLedEffectAllClose                  = 0x00,
    JL_HeadsetLedEffectRedLightOn                = 0x01,
    JL_HeadsetLedEffectBlueLightOn               = 0x02,
    JL_HeadsetLedEffectRedLightBreathing         = 0x03,
    JL_HeadsetLedEffectBlueLightBreathing        = 0x04,
    JL_HeadsetLedEffectRedBlueLightQuickFlash    = 0x05,
    JL_HeadsetLedEffectRedBlueLightSlowFlash     = 0x06,
};
/**
              0x02
              0x03
              0x04:
              0x05：
              0x06：
              0x07：
               0x01
               0x02
               0x03
               0x04
               0x05
               0x06
 */
-(void)cmdHeadsetLedSettingScene:(uint8_t)scene
                          Effect:(uint8_t)effect;

#pragma mark - Vendor SDK
typedef NS_ENUM(UInt8, JL_HeadsetMicSettingMode) {
    JL_HeadsetMicSettingModeOnlyLeftEar      = 0x00,
    JL_HeadsetMicSettingModeOnlyRightEar     = 0x01,
    JL_HeadsetMicSettingModeAutomatic        = 0x02,
};
/**
 */
-(void)cmdHeadsetMicSettingMode:(JL_HeadsetMicSettingMode)mode
                         Result:(JL_CMD_RESPOND __nullable)result;

#pragma mark - Vendor SDK
typedef NS_ENUM(UInt8, JL_HeadsetWorkingMode) {
    JL_HeadsetWorkingModeNormal      = 0x01,
    JL_HeadsetWorkingModeGame        = 0x02,
};
/**
        2：
 */
-(void)cmdHeadsetWorkSettingMode:(uint8_t)mode;

#pragma mark - Vendor SDK
/**
*/
-(void)cmdHeadsetTimeSetting:(NSDate*)date;

#pragma mark - Vendor SDK
typedef void(^JL_HEADSET_BK)(NSDictionary* __nullable dict);
typedef NS_ENUM(uint32_t, JL_HeadsetAdviceFlag) {
    JL_HeadsetAdviceFlagGetElectricity              = 1,
    JL_HeadsetAdviceFlagEdrName                     = 1 << 1,
    JL_HeadsetAdviceFlagButtonFunction              = 1 << 2,
    JL_HeadsetAdviceFlagLedStatus                   = 1 << 3,
    JL_HeadsetAdviceFlagMicMode                     = 1 << 4,
    JL_HeadsetAdviceFlagWorkMode                    = 1 << 5,
    JL_HeadsetAdviceFlagProductInfo                 = 1 << 6,
    JL_HeadsetAdviceFlagConnectingTime              = 1 << 7,
    JL_HeadsetAdviceFlagEarDetection                = 1 << 8,
    JL_HeadsetAdviceFlagLanguage                    = 1 << 9,
    JL_HeadsetAdviceFlagAll                         = 0xFFFFFFFF
};
/**
             BIT1    Edr
             BIT2
             BIT3    LED
             BIT4    MIC
             BIT5
             BIT6
             BIT7
             BIT8
             BIT9
                @"ISCHARGING_L"
                @"ISCHARGING_R"
                @"ISCHARGING_C"
                @"POWER_L"
                @"POWER_R"
                @"POWER_C"
                @"EDR_NAME"
                @"KEY_LR"
                @"KEY_ACTION"
                @"KEY_FUNCTION"
                @"LED_SCENE"
                @"LED_EFFECT"
                @"MIC_MODE"
                @"WORK_MODE"
                @"UID"
                @"UID"
                @"PID"
                @"LINK_TIME"
                @""IN_EAR_TEST"
                @"DEVICE_LANGUAGE"
                @"KEY_ANC_MODE"    ANC
 */
-(void)cmdHeadsetGetAdvFlag:(JL_HeadsetAdviceFlag)flag
                     Result:(JL_HEADSET_BK __nullable)result;

#pragma mark - Vendor SDK
/**
    @{@"JLID": ID,
    @"UID": ,
    @"PID":  ,
    @"EDR": ,
    @"SCENE": ,
    @"ISCHARGING_L": ,
    @"ISCHARGING_R": ,
    @"ISCHARGING_C": ,
    @"POWER_L": ,
    @"POWER_R": ,
    @"POWER_C": ,
    @"CHIP_TYPE": ,
    @"PROTOCOL_TYPE": ,
    @"SEQ":};
 */
extern NSString *kJL_MANAGER_HEADSET_ADV;

#pragma mark - Vendor SDK
/**
    0x00：
    0x01：
    0x02：
    0x03：
 */
extern NSString *kJL_MANAGER_HEADSET_SET_ERR;

#pragma mark - Vendor SDK
/**
 */
-(void)cmdHeadsetAdvEnable:(BOOL)enable;

#pragma mark - Vendor SDK
/**
  1：，。
  2：
  3：BLE
  4：
 */
extern NSString *kJL_MANAGER_HEADSET_TIPS;

#pragma mark - Vendor SDK
/**
*/
-(void)cmdSetFMTX:(uint16_t)fmtx;

#pragma mark - Vendor SDK
/**
 */
-(void)cmdHeadsetAncArray:(NSArray*)array;

#pragma mark - Vendor SDK
-(void)cmdSetANC:(JLModel_ANC*)model;




typedef void(^JL_MulitLinksInfo_BK)(JL_CMDStatus status,NSArray <JLTWSAddrNameInfo *>* __nullable phoneInfos);

extern NSString* kJL_MULIT_NAME_LIST;

-(void)cmdGetDeviceInfoListResult:(JL_MulitLinksInfo_BK)result;

/// - Parameters:
-(void)cmdBindDeviceInfo:(NSData *)addr phone:(NSString *)name result:(JL_MulitLinksInfo_BK)result;

-(void)setDragWithMore:(BOOL)dragWithMore phoneBleAddr:(NSData *) addr result:(JL_CMD_RESPOND)result;

@end

NS_ASSUME_NONNULL_END
