//
//  JLBleManager.h
//  JL_OTA
//
//  Created by the Jieli OTA sample on 2021/10/11.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <UIKit/UIKit.h>
#import <DFUnits/DFUnits.h>
#import "JLBleEntity.h"
#import "HandleBroadcastPtl.h"

#import <JL_OTALib/JL_OTALib.h>
#import <JL_HashPair/JL_HashPair.h>
#import <JL_AdvParse/JL_AdvParse.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - BLE State Notifications
extern NSString *kFLT_BLE_FOUND;         // Device discovered.
extern NSString *kFLT_BLE_PAIRED;        // Device paired.
extern NSString *kFLT_BLE_CONNECTED;     // Device connected.
extern NSString *kFLT_BLE_DISCONNECTED;  // Device disconnected.



@protocol JLBleManagerOtaDelegate <NSObject>

@required
/**
 *  OTA state callback.
 */
- (void)otaProgressWithOtaResult:(JL_OTAResult)result withProgress:(float)progress;

@end


@interface JLBleManager : HandleBroadcastPtl

@property (assign, nonatomic) CBManagerState mBleManagerState;
@property (strong, nonatomic) CBPeripheral *__nullable mBlePeripheral;

/// Whether Bluetooth authentication pairing is required.
@property (assign, nonatomic) BOOL isPaired;

/// Pairing key. Empty by default.
@property (assign, nonatomic) NSData *pairKey;

/// Connected device MTU. This is the maximum payload for one send.
@property (assign, nonatomic) NSInteger bleMtu;

/// Last connected Bluetooth UUID.
@property (strong, nonatomic) NSString *lastUUID;

/// Last connected Bluetooth address.
@property (strong, nonatomic) NSString *__nullable lastBleMacAddress;

@property (strong, nonatomic) JL_OTAManager *otaManager;

@property (assign,nonatomic)BOOL isConnected;

@property (strong, nonatomic) JLBleEntity *__nullable currentEntity;

/**
 * Singleton instance.
 */
+ (instancetype)sharedInstance;

/**
 Starts scanning.
 */
-(void)startScanBLE;

/**
 Stops scanning.
 */
-(void)stopScanBLE;

/**
 Connects to a device.
 @param peripheral Bluetooth peripheral.
 */
-(void)connectBLE:(CBPeripheral*)peripheral;

/**
 Disconnects the current device.
 */
-(void)disconnectBLE;

/**
 Reconnects a device by UUID.
*/
-(void)connectPeripheralWithUUID:(NSString *)uuid;


/// Reconnects a HID device.
/// - Parameter uuid: Device identifier string.
-(void)findHid:(NSString *)uuid;

#pragma mark - Jieli OTA SDK Flow

typedef void(^GET_DEVICE_CALLBACK)(BOOL needForcedUpgrade);

typedef void(^CANCEL_CALLBACK)(uint8_t status);

/**
 *  Gets connected device information.
 */
- (void)getDeviceInfo:(GET_DEVICE_CALLBACK _Nonnull)callback;

/**
 *  Starts OTA update.
 */
- (void)otaFuncWithFilePath:(NSString *)otaFilePath;

- (void)otaFuncCancel:(CANCEL_CALLBACK _Nonnull)result;

@end

NS_ASSUME_NONNULL_END
