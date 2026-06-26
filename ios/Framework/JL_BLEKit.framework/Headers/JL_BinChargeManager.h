//
//  JL_BinCharge.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/12/16.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_FunctionBaseManager.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JL_Tools.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_ScanSetting) {
    JL_ScanTimeout     = 0x00,
    JL_ScanInterrupt   = 0x01,
    JL_ScanFail        = 0x02,
    JL_Scaning         = 0x03,
};

typedef NS_ENUM(UInt8, JL_ReverberationFunType) {
    JL_ReverberationAndDynamicType       = 0x00,
    JL_OnlyReverberationType             = 0x01,
    JL_OnlyDynamicLimiterType            = 0x02,
};

typedef void(^JL_CMD_VALUE_BK)(uint32_t value);
typedef void(^JL_LOW_DELAY_BK)(uint16_t mtu, uint32_t delay);

@interface JL_BinChargeManager : JL_FunctionBaseManager

#pragma mark - Vendor SDK
-(void)cmdSetAppInfo:(uint8_t)flag;

#pragma mark - Vendor SDK
-(void)cmdSetMTU:(uint16_t)mtu Result:(JL_CMD_VALUE_BK __nullable)result;

#pragma mark - Vendor SDK
-(void)cmdBTScanStartTimeout:(uint16_t)timeout Result:(JL_CMD_VALUE_BK __nullable)result;

#pragma mark - Vendor SDK
// @see JLBTModel
extern NSString *kJL_MANAGER_BT_LIST_RESULT;

#pragma mark - Vendor SDK
-(void)cmdBTScanStopReason:(JL_ScanSetting)reason Result:(JL_CMD_VALUE_BK __nullable)result;

#pragma mark - Vendor SDK
extern NSString *kJL_MANAGER_BT_SCAN_STOP_NOTE;

#pragma mark - Vendor SDK
-(void)cmdBTConnectAddress:(NSData*)addr Result:(JL_CMD_VALUE_BK __nullable)result;

extern NSString *kJL_MANAGER_ID3_Title;
extern NSString *kJL_MANAGER_ID3_Artist;
extern NSString *kJL_MANAGER_ID3_Album;
extern NSString *kJL_MANAGER_ID3_Time;
extern NSString *kJL_MANAGER_ID3_Current;
extern NSString *kJL_MANAGER_ID3_PlayPush;

#pragma mark - Vendor SDK
-(void)setID3_Status:(uint8_t)st;

#pragma mark - Vendor SDK
-(void)cmdID3_PP;

#pragma mark - Vendor SDK
-(void)cmdID3_Before;

#pragma mark - Vendor SDK
-(void)cmdID3_Next;

#pragma mark - Vendor SDK
-(void)cmdID3_PushEnable:(BOOL)enable;

#pragma mark - Vendor SDK

/// - Parameters:
-(void)cmdSetLowPitch:(int)p_low HighPitch:(int)p_high;

#pragma mark - Vendor SDK
-(void)cmdSetReverberation:(int)depthValue
            IntensityValue:(int)intensityValue
       DynamicLimiterValue:(int)dynamicLimiterValue
          SwtichReverState:(int)reverOn
                   FunType:(JL_ReverberationFunType)type;

#pragma mark - Vendor SDK
-(void)cmdGetLowDelay:(JL_LOW_DELAY_BK __nullable)result;


@end

NS_ASSUME_NONNULL_END
