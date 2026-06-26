//
//  JL_BLEMultiple.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2020/9/1.
//  Copyright © 2020 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <UIKit/UIKit.h>

#import <JL_BLEKit/JL_EntityM.h>

NS_ASSUME_NONNULL_BEGIN

/**
 */
extern NSString *kJL_BLE_M_FOUND;
extern NSString *kJL_BLE_M_FOUND_SINGLE;
extern NSString *kJL_BLE_M_ENTITY_CONNECTED;
extern NSString *kJL_BLE_M_ENTITY_DISCONNECTED;
extern NSString *kJL_BLE_M_ON;
extern NSString *kJL_BLE_M_OFF;
extern NSString *kJL_BLE_M_EDR_CHANGE;
extern NSString *kJL_BLE_M_SAVE_BLEADDR;
extern NSString *kJL_BLE_M_ANCS_UPDATE;


@interface JL_BLEMultiple : NSObject
@property (strong, nonatomic) NSData   *__nullable filterKey;
@property (strong, nonatomic) NSData   *__nullable pairKey;
@property (assign, nonatomic) BOOL                 BLE_IS_CONNECTING;
@property (assign, nonatomic) BOOL                 BLE_FILTER_ENABLE;
@property (assign, nonatomic) BOOL                 BLE_PAIR_ENABLE;
@property (assign, nonatomic) int                  BLE_TIMEOUT;

@property (strong, nonatomic) NSMutableArray<JL_EntityM *> *blePeripheralArr;
@property (strong, nonatomic) NSArray<CBPeripheral *> *bleAttDevices;
@property (strong, nonatomic) NSMutableArray<JL_EntityM *> *bleConnectedArr;
@property (assign, nonatomic) CBManagerState                bleManagerState;
@property (strong, nonatomic) NSArray<NSNumber *> *__nullable bleDeviceTypeArr;
@property (strong, nonatomic) NSArray<NSNumber *> *__nullable managerClassArr;


@property (strong, nonatomic) NSString             *JL_BLE_SERVICE;
@property (strong, nonatomic) NSString             *JL_BLE_RCSP_W;
@property (strong, nonatomic) NSString             *JL_BLE_RCSP_R;

+(NSString*)versionOfSDK;

/**
 */
-(void)scanStart;

/**
 */
-(void)scanContinue;

/**
 */
-(void)scanStop;


-(CBCentralManager *)getCenterManaer;

/**
 UUIDEntity。
 */
-(JL_EntityM *_Nullable)makeEntityWithUUID:(NSString*)uuid;

/// @param uuid uuid
-(void)getEntityWithSearchUUID:(NSString *)uuid SearchStatus:(BOOL)status Result:(void(^)(JL_EntityM *_Nullable entity))result;
/**
 */
-(void)connectEntity:(JL_EntityM*)entity Result:(JL_EntityM_STATUS_BK)result;


-(void)connectEntityWithAdvMac:(NSString *)advMac Result:(JL_EntityM_STATUS_BK) result;

-(void)connectEntityForMac:(NSString *)mac Result:(JL_EntityM_STATUS_BK)result;

/**
 */
-(void)disconnectEntity:(JL_EntityM*)entity Result:(JL_EntityM_STATUS_BK)result;

/**
*/
-(void)updateHistoryRename:(NSString*)name withUuid:(NSString*)uuid;

-(void)cleanHistoryDeviceCache;

-(JL_EntityM *__nullable)connectingEntity;

/**
           @"TYPE"   :@"BluetoothA2DPOutput",
           @"NAME"   :@"earphone"}
 */
+(NSDictionary*)outputEdrInfo;

/**
 edr
 */
+(NSArray<NSString *>*)outputEdrList;


#pragma mark - Vendor SDK
/**
 */
- (void)otaFuncWithEntityM:(JL_EntityM *)mBleEntityM
              withFilePath:(NSString *)otaFilePath
                    Result:(JL_OTA_RT __nullable)result;
- (void)setOtaReconnectBleAddr:(NSString* __nullable)addr;

@end

NS_ASSUME_NONNULL_END
