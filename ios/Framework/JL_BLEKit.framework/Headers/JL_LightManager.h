//
//  JL_LightManager.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/12/16.
//  Modify by EzioChan on 2023/03/16
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_FunctionBaseManager.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JL_Tools.h>


NS_ASSUME_NONNULL_BEGIN

@class JL_LightManager;

@protocol JLLightStatusPtl <NSObject>

-(void)jlLightStatus:(JL_LightManager *)lightManager;

@end


@interface JL_LightManager : JL_FunctionBaseManager

@property(nonatomic,assign)BOOL isSupportLight;

@property (assign,nonatomic) JL_LightState      lightState;

@property (assign,nonatomic) JL_LightMode       lightMode;

@property (assign,nonatomic) uint8_t            lightRed;

@property (assign,nonatomic) uint8_t            lightGreen;

@property (assign,nonatomic) uint8_t            lightBlue;

@property (assign,nonatomic) JL_LightFlashModeIndex lightFlashIndex;

@property (assign,nonatomic) JL_LightFlashModeFrequency lightFrequencyIndex;

@property (assign,nonatomic) JL_LightSceneMode  lightSceneIndex;

@property (assign,nonatomic) uint16_t           lightHue;

@property (assign,nonatomic) uint8_t            lightSat;

@property (assign,nonatomic) uint8_t            lightLightness;

@property (weak,nonatomic)id<JLLightStatusPtl> delegate;


-(void)cmdGetLightStatus;
/**
 */
-(void)cmdSetState:(JL_LightState)lightState
              Mode:(JL_LightMode)lightMode
               Red:(uint8_t)red
             Green:(uint8_t)green
              Blue:(uint8_t)blue
         FlashInex:(JL_LightFlashModeIndex)flashIndex
         FlashFreq:(JL_LightFlashModeFrequency)flashFreqIndex
        SceneIndex:(JL_LightSceneMode)sceneIndex
               Hue:(uint16_t)hue
        Saturation:(uint8_t)saturation
         Lightness:(uint8_t)lightness;

@end

NS_ASSUME_NONNULL_END
