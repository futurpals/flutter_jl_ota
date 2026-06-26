//
//  JL_BLEKit.h
//  JL_BLEKit
//
//  Created by zhihui liang on 2018/11/9.
//  Copyright © 2018 www.zh-jieli.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
//! Project version number for JL_BLEKit.
FOUNDATION_EXPORT double JL_BLEKitVersionNumber;

//! Project version string for JL_BLEKit.
FOUNDATION_EXPORT const unsigned char JL_BLEKitVersionString[];

#import <JL_BLEKit/JL_Tools.h>
#import <JL_BLEKit/JL_RCSP.h>
#import <JL_BLEKit/JL_OpCode.h>
#import <JL_BLEKit/JL_Handle.h>
#import <JL_BLEKit/JL_BLEAction.h>
#import <JL_BLEKit/JL_vad.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JLTaskChain.h>

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
#import <JL_BLEKit/JLModel_SmallFile.h>
#import <JL_BLEKit/JLCmdBasic.h>
#import <JL_BLEKit/JLModelVocalBoost.h>
#import <JL_BLEKit/JLModelNoiseDetection.h>
#import <JL_BLEKit/JLModelSceneNoiseReduction.h>
#import <JL_BLEKit/JLModelSmartPickFree.h>

#import <JL_BLEKit/JL_BLEMultiple.h>
#import <JL_BLEKit/JL_EntityM.h>
#import <JL_BLEKit/JL_ManagerM.h>
#import <JL_BLEKit/JL_Assist.h>

#import <JL_BLEKit/JL_FunctionBaseManager.h>
#import <JL_BLEKit/JL_FileManager.h>
#import <JL_BLEKit/JL_SmallFileManager.h>
#import <JL_BLEKit/JL_FlashOperateManager.h>
#import <JL_BLEKit/JL_BinChargeManager.h>
#import <JL_BLEKit/JL_CallManager.h>
#import <JL_BLEKit/JL_AlarmClockManager.h>
#import <JL_BLEKit/JL_LightManager.h>
#import <JL_BLEKit/JL_TwsManager.h>
#import <JL_BLEKit/JLTwsSupportFuncs.h>
#import <JL_BLEKit/JLTranslateSet.h>
#import <JL_BLEKit/JLTranslateAudio.h>
#import <JL_BLEKit/JLTranslateSetMode.h>
#import <JL_BLEKit/JLTranslationManager.h>
#import <JL_BLEKit/JL_SoundCardManager.h>
#import <JL_BLEKit/JL_LrcManager.h>
#import <JL_BLEKit/JL_SpeexManager.h>
#import <JL_BLEKit/JL_SpeechAIttsHandler.h>
#import <JL_BLEKit/JL_FindDeviceManager.h>
#import <JL_BLEKit/JL_MusicControlManager.h>
#import <JL_BLEKit/JLDevPlayerCtrl.h>
#import <JL_BLEKit/JL_FmManager.h>
#import <JL_BLEKit/JL_SystemEQ.h>
#import <JL_BLEKit/JL_SystemTime.h>
#import <JL_BLEKit/JL_SystemVolume.h>
#import <JL_BLEKit/JL_CustomManager.h>
#import <JL_BLEKit/JL_BatchManger.h>
#import <JL_BLEKit/JL_DeviceLogs.h>
#import <JL_BLEKit/JLDhaFitting.h>
#import <JL_BLEKit/JLAutoConfigAnc.h>
#import <JL_BLEKit/JLDeviceConfig.h>
#import <JL_BLEKit/JL_BigDataManager.h>
#import <JL_BLEKit/JLAiManager.h>
#import <JL_BLEKit/JLAIDialManager.h>


#import <JL_BLEKit/JLWearable.h>
#import <JL_BLEKit/JLSportDataModel.h>
#import <JL_BLEKit/JL_SDM_Stress.h>
#import <JL_BLEKit/JL_SDM_Altitude.h>
#import <JL_BLEKit/JL_SDM_MaxOxg.h>
#import <JL_BLEKit/JL_SDM_RecTime.h>
#import <JL_BLEKit/JL_SDM_HeartRate.h>
#import <JL_BLEKit/JL_SDM_MoveSteps.h>
#import <JL_BLEKit/JL_SDM_TrainLoad.h>
#import <JL_BLEKit/JL_SDM_AirPressure.h>
#import <JL_BLEKit/JL_SDM_OxSaturation.h>
#import <JL_BLEKit/JL_SDM_SportMessage.h>
#import <JL_BLEKit/JL_SDM_Header.h>
#import <JL_BLEKit/NSData+ToUnit.h>
#import <JL_BLEKit/JL_MSG_Weather.h>
#import <JL_BlEKit/JL_MSG_Func.h>
#import <JL_BLEKit/JL_NFC.h>
#import <JL_BLEKit/JLWatchEnum.h>
#import <JL_BLEKit/JL_WatchProtocol.h>

#import <JL_BLEKit/ECThreadHelper.h>
#import <JL_BLEKit/JLHttpHelper.h>
#import <JL_BLEKit/ECBDTObjc.h>
#import <JL_BLEKit/ECBDTManager.h>
#import <JL_BLEKit/JLModelDevFunc.h>
#import <JL_BLEKit/JLModelCardInfo.h>
#import <JL_BLEKit/JLPublicSetting.h>
#import <JL_BLEKit/JL4GUpgradeManager.h>
#import <JL_BLEKit/JLDeviceConfigTws.h>
#import <JL_BLEKit/JLDialInfoExtentedModel.h>
#import <JL_BLEKit/JLDialInfoExtentManager.h>
#import <JL_BLEKit/JLModelSpdif.h>
#import <JL_BLEKit/JLModelPCServer.h>
#import <JL_BLEKit/JLSpdifPCManager.h>
#import <JL_BLEKit/JLFlashOpMgr.h>
#import <JL_BLEKit/JLTipsSoundReplaceMgr.h>

