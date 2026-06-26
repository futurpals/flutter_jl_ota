//
//  JL_EntityM.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2020/9/1.
//  Copyright © 2020 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <UIKit/UIKit.h>
#import <JL_BLEKit/JL_Tools.h>
#import <JL_BLEKit/JL_ManagerM.h>
#import <JL_AdvParse/JLAdvParse.h>

NS_ASSUME_NONNULL_BEGIN
//@class JL_EntityM;
typedef NS_ENUM(NSInteger, JL_EntityM_Status) {
    JL_EntityM_StatusBleOFF         = 0,
    JL_EntityM_StatusConnectFail    = 1,
    JL_EntityM_StatusConnecting     = 2,
    JL_EntityM_StatusConnectRepeat  = 3,
    JL_EntityM_StatusConnectTimeout = 4,
    JL_EntityM_StatusConnectRefuse  = 5,
    JL_EntityM_StatusPairFail       = 6,
    JL_EntityM_StatusPairTimeout    = 7,
    JL_EntityM_StatusPaired         = 8,
    JL_EntityM_StatusMasterChanging = 9,
    JL_EntityM_StatusDisconnectOk   = 10,
    JL_EntityM_StatusNull           = 11,
};

typedef NS_ENUM(NSUInteger, JLEntityConnectType) {
    JLEntityConnectTypeBLE = 0,
    JLEntityConnectTypeSPP = 1,
    JLEntityConnectTypeATT = 2,
};

typedef void(^JL_EntityM_STATUS_BK)(JL_EntityM_Status status);

@interface JL_EntityM : NSObject<NSCopying>

@property(nonatomic,strong) JL_ManagerM   *mCmdManager;

@property(nonatomic,readonly,copy) CBPeripheral  *mPeripheral;
@property(nonatomic,strong) NSString        *mSERVICE;
@property(nonatomic,strong) NSString        *mRCSP_W;
@property(nonatomic,strong) NSString        *mRCSP_R;
@property(nonatomic,strong) NSData *__nullable mFilterKey;
@property(nonatomic,strong) NSData *__nullable mPairKey;
@property(strong,nonatomic) NSData          *mAdvData;

@property(nonatomic,assign) int             mBLE_TIMEOUT;
@property(nonatomic,assign) BOOL            mBLE_FILTER_ENABLE;
@property(nonatomic,assign) BOOL            mBLE_PAIR_ENABLE;
@property(nonatomic,assign) BOOL            mBLE_IS_PAIRED;
@property(nonatomic,assign) BOOL            mBLE_NEED_OTA;
@property(nonatomic,assign) BOOL            isFrom_HISTROY;
@property(nonatomic,assign) BOOL            isBLE_CHANGE;
@property(nonatomic,assign) BOOL            isCMD_PREPARED;

@property(strong,nonatomic) NSString        *mUUID;
@property(strong,nonatomic) NSNumber        *mRSSI;
@property(readonly,copy,nonatomic)NSString  *mItem;
/**
 *  1：TWS
 */
@property(assign,nonatomic) JL_DeviceType   mType;
@property(assign,nonatomic) BOOL            isExclusive;
@property(assign,nonatomic) BOOL            isBound;
@property(assign,nonatomic) BOOL            isEdrLinked;
@property(assign,nonatomic) BOOL            isCharging;
@property(assign,nonatomic) BOOL            isCharging_L;
@property(assign,nonatomic) BOOL            isCharging_R;
@property(assign,nonatomic) BOOL            isCharging_C;
@property(assign,nonatomic) uint8_t         mPower;
@property(assign,nonatomic) uint8_t         mPower_L;
@property(assign,nonatomic) uint8_t         mPower_R;
@property(assign,nonatomic) uint8_t         mPower_C;
@property(strong,nonatomic) NSString        *mVID __attribute__((deprecated("Deprecated, use mUID instead")));
@property(strong,nonatomic) NSString        *mUID;
@property(strong,nonatomic) NSString        *mPID;
@property(strong,nonatomic) NSString        *mEdr;
@property(strong,nonatomic) NSString        *mBleAddr;
@property(assign,nonatomic) uint8_t         mChipType;            //0：690x 1：692x 2：693x
@property(assign,nonatomic) uint8_t         mProtocolType;
/**
 0x00 - dismiss
 0x01 - unconnected
    iOS : ，XXX
    Android：，
 0x02 - connected
    iOS：，，
         “”。，。
    Android：Mac，Mac，
             “”。，。
 0x03 - connecting
    Android  iOS “ ”
 0x04 - connectionless （）
    Android  iOS
 */
@property(assign,nonatomic) int8_t          mScene;

@property(assign,nonatomic) uint8_t         mSeq;

@property(assign,nonatomic) uint8_t         mTWS_Paired;

@property(assign,nonatomic) uint8_t         mTWS_Cap;

@property(assign,nonatomic) uint8_t         mTWS_Mode;
@property(assign,nonatomic) uint8_t         mHeadsetMaster;

@property(assign,nonatomic) uint8_t         mHeadsetLinkEnable;
/**
 */
@property(assign,nonatomic) uint8_t         mWatchScene;

///0:ble
///1:spp
///2:att
@property(assign,nonatomic) JLEntityConnectType      mConnectWay;

@property(assign,nonatomic) BOOL mIsSupportChargeBin;

@property(assign,nonatomic) BOOL mIsSupportLeAudio;

@property(assign,nonatomic) BOOL mLeAudioConnected;

@property(assign,nonatomic) JLDevSpecialType  mSpecialType;

-(void)setBlePeripheral:(CBPeripheral *)mPeripheral;
-(void)setBleItem:(NSString *)mItem;

/**
*/
-(void)updateDelegate;

/**
*/
-(void)releaseEntityTimer;

/**
 RCSP
 */
-(BOOL)writeRcspData:(NSData*)data;

/**
*/
-(void)setGameMode:(BOOL)isGame MTU:(NSUInteger)mtu Delay:(int)delay;


-(void)flashFinishedAction;


#pragma mark - Vendor SDK
-(void)startTimeout:(int)code;
-(void)stopTimeout;
-(void)cancelAuthPair;
#pragma mark - Vendor SDK
-(void)updateEntity:(NSDictionary*)dic;
+(JL_EntityM*)changeToEntity:(NSDictionary*)dic;
+(NSArray*)turnToEntityArray:(NSArray*)array;

@end

NS_ASSUME_NONNULL_END
