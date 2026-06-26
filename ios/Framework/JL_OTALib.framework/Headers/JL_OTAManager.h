//
//  JL_OTAManager.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/11/16.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JLLogHelper/JLLogHelper.h>

NS_ASSUME_NONNULL_BEGIN
@class JLOtaReConnectOption;

typedef NS_ENUM(UInt16, JL_OTAResult) {
    JL_OTAResultSuccess = 0x00,
    JL_OTAResultFail = 0x01,
    JL_OTAResultDataIsNull = 0x02,
    JL_OTAResultCommandFail = 0x03,
    JL_OTAResultSeekFail = 0x04,
    JL_OTAResultInfoFail = 0x05,
    JL_OTAResultLowPower = 0x06,
    JL_OTAResultEnterFail = 0x07,
    JL_OTAResultUpgrading = 0x08,
    JL_OTAResultReconnect = 0x09,
    JL_OTAResultReboot = 0x0a,
    JL_OTAResultPreparing = 0x0b,
    JL_OTAResultPrepared = 0x0f,
    JL_OTAResultStatusIsUpdating = 0x10,
    JL_OTAResultFailedConnectMore = 0x11,
    JL_OTAResultFailSameSN = 0xe0,
    JL_OTAResultCancel = 0xe1,
    JL_OTAResultFailVerification = 0xf1,
    JL_OTAResultFailCompletely = 0xf2,
    JL_OTAResultFailKey = 0xf3,
    JL_OTAResultFailErrorFile = 0xf4,
    JL_OTAResultFailUboot = 0xf5,
    JL_OTAResultFailLenght = 0xf6,
    JL_OTAResultFailFlash = 0xf7,
    JL_OTAResultFailCmdTimeout = 0xf8,
    JL_OTAResultFailSameVersion = 0xf9,
    JL_OTAResultFailTWSDisconnect = 0xfa,
    JL_OTAResultFailNotInBin = 0xfb,
    JL_OTAResultReconnectWithMacAddr = 0xfc,
    JL_OTAResultDisconnect = 0xfd,
    JL_OTAResultReconnectUpdateSource = 0xfe,
    JL_OTAResultUnknown
};

typedef NS_ENUM(UInt8, JL_OTAReconnectType) {
    JL_OTAReconnectTypeUUID = 0x00,
    JL_OTAReconnectTypeMACAddr = 0x01,
};

typedef NS_ENUM(UInt8, JL_OtaStatus) {
    JL_OtaStatusNormal = 0,
    JL_OtaStatusForce = 1,
};
typedef NS_ENUM(UInt8, JL_OtaHeadset) {
    JL_OtaHeadsetNO = 0,
    JL_OtaHeadsetYES = 1,
};

typedef NS_ENUM(UInt8, JL_OtaWatch) {
    JL_OtaWatchNO = 0,
    JL_OtaWatchYES = 1,
}__attribute__((deprecated("This enum is deprecated. Use JLOtaSourcesExtendMode instead.")));

typedef NS_ENUM(UInt8, JLOtaSourcesExtendMode) {
    JLSourcesExtendModeDisable = 0,
    JLSourcesExtendModeNormal = 1,
    JLSourcesExtendModeSourceOnly = 2,
    JLSourcesExtendModeFirmwareOnly = 3,
};

typedef NS_ENUM(UInt8, JL_BootLoader) {
    JL_BootLoaderNO = 0,
    JL_BootLoaderYES = 1,
};
typedef NS_ENUM(UInt8, JL_Partition) {
    JL_PartitionSingle = 0,
    JL_PartitionDouble = 1,
};

typedef void (^JL_OTA_RT)(JL_OTAResult result, float progress);

typedef void (^JL_OTA_RESULT)(uint8_t status, uint8_t sn, NSData *__nullable data);

@class JL_OTAManager;

@protocol JL_OTAManagerDelegate <NSObject>

- (void)otaDataSend:(NSData *_Nonnull)data;

@optional
- (void)otaFeatureResult:(JL_OTAManager *_Nonnull)manager;

- (void)otaUpgradeResult:(JL_OTAResult)result Progress:(float)progress;

- (void)otaCancel;

@end

@interface JL_OTAManager : NSObject

@property(strong, nonatomic) NSString *mBLE_UUID;

@property(strong, nonatomic) NSString *mBLE_NAME;

@property(assign, nonatomic) BOOL bleOnly;

@property(strong, nonatomic) NSString *bleAddr;

@property(assign, nonatomic) uint8_t mCmdSN;

@property(assign, nonatomic) uint16_t version;

@property(strong, nonatomic) NSString *versionFirmware;

@property(assign, nonatomic) JL_OtaStatus otaStatus;

@property(assign, nonatomic) JL_OtaHeadset otaHeadset;

@property(assign, nonatomic) JL_OtaWatch otaWatch __attribute__((deprecated("This property is deprecated. Use otaSourceMode instead.")));

@property(assign, nonatomic) BOOL isSupportReuseSpaceOTA;

@property(assign, nonatomic) JLOtaSourcesExtendMode otaSourceMode;

@property(assign, nonatomic) JL_Partition otaPartition;

@property(assign, nonatomic) JL_BootLoader bootloaderType;

@property(assign, nonatomic) JL_OTAReconnectType otaReconnectType;

@property(assign, nonatomic, readonly) int64_t otaLength;

@property(assign, nonatomic, readonly) uint32_t otaSent;

@property(weak, nonatomic) id<JL_OTAManagerDelegate> delegate;

+ (JL_OTAManager *)getOTAManager;

- (instancetype)init __attribute__((deprecated("Please use getOTAManager instead.")));

- (void)logSendData:(BOOL)status;

- (void)noteEntityConnected;

- (void)noteEntityDisconnected;

/// default: 10
- (void)maxLostCount:(int)count;

/// default: 5
- (void)cmdTimeOut:(int)timeOut;

- (void)setOTARelink:(BOOL)isReLink __attribute__((deprecated("Can't be used externally.")));

/// Receive data from rcsp
/// - Parameter data: data
- (void)cmdOtaDataReceive:(NSData *)data;

- (void)cmdTargetFeature;

- (void)cmdSystemFunction;

- (BOOL)cmdOtaIsRelinking;

#pragma mark - Vendor SDK
/**
 OTA
 */
- (void)cmdOTAData:(NSData *)data
            Result:(JL_OTA_RT __nullable)result;

- (void)cmdOtaDataIIResult:(JL_OTA_RT __nullable)result;

-(void)cmdUpgrade:(NSData *)data Option:(JLOtaReConnectOption *_Nullable)option Result:(JL_OTA_RT _Nonnull)result;

/**
 OTA
 */
- (void)cmdOTACancelResult:(JL_OTA_RESULT __nullable)result;

- (void)cmdRebootDevice;

- (void)cmdRebootForceDevice;

- (void)resetOTAManager;

+ (NSString *)logSDKVersion;

@end

NS_ASSUME_NONNULL_END
