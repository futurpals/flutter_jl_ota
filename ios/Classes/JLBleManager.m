//
//  JLBleManager.m
//  JL_OTA
//
//  Created by the Jieli OTA sample on 2021/10/11.
//

#import "JLBleManager.h"
//#import "FittingView.h"
#import "SingleDataSender.h"

#define SENDBYSINGLE  0 // 1: send after signal detection; 0: send data directly.

NSString *kFLT_BLE_FOUND = @"FLT_BLE_FOUND";            // Device discovered.
NSString *kFLT_BLE_PAIRED = @"FLT_BLE_PAIRED";           // BLE paired.
NSString *kFLT_BLE_CONNECTED = @"FLT_BLE_CONNECTED";        // BLE connected.
NSString *kFLT_BLE_DISCONNECTED = @"FLT_BLE_DISCONNECTED";     // BLE disconnected.

NSString *FLT_BLE_SERVICE = @"AE00"; // Service UUID.
NSString *FLT_BLE_RCSP_W = @"AE01"; // Command write channel.
NSString *FLT_BLE_RCSP_R = @"AE02"; // Command read channel.



@interface JLBleManager () <CBCentralManagerDelegate, CBPeripheralDelegate, JL_OTAManagerDelegate, JLHashHandlerDelegate, SingleSendDelegate>

@property(strong, nonatomic) CBCentralManager *bleManager;
@property(strong, nonatomic) JLHashHandler *pairHash;
@property(assign, nonatomic) BOOL pairStatus;

@property(strong, nonatomic)
NSMutableArray<JLBleEntity *> *
blePeripheralArr;
@property(strong, nonatomic) CBPeripheral *bleCurrentPeripheral;
@property(strong, nonatomic) CBService *mService;
@property(strong, nonatomic) CBCharacteristic *mRcspWrite;
@property(strong, nonatomic) CBCharacteristic *mRcspRead;

@property(strong, nonatomic) NSString *selectedOtaFilePath;
@property(strong, nonatomic) NSString *connectByUUID;

@property(strong, nonatomic) GET_DEVICE_CALLBACK getCallback;


@end

@implementation JLBleManager

+ (instancetype)sharedInstance {
    static JLBleManager *singleton = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        singleton = [[self alloc] init];
    });
    return singleton;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _isPaired = YES;
        _pairStatus = NO;

        _bleManager = [[CBCentralManager alloc] initWithDelegate:self queue:nil];

        /*--- JLSDK ADD ---*/
        _otaManager = [JL_OTAManager getOTAManager];
        [JL_OTAManager logSDKVersion];
        [JLHashHandler sdkVersion];
        [_otaManager logSendData:false];

        _otaManager.delegate = self;

        self.pairHash = [[JLHashHandler alloc] init];
        self.pairHash.delegate = self;

        _connectByUUID = nil;
#if SENDBYSINGLE
        [[SingleDataSender share] addDelegate:self];
#endif

    }
    return self;
}

- (void)setIsPaired:(BOOL)isPaired {
    _isPaired = isPaired;
}


#pragma mark - Device Scanning

#pragma mark Start Scan

- (void)startScanBLE {
    NSLog(@"BLE ---> startScanBLE.");
    _blePeripheralArr = [NSMutableArray new];
    if (_bleManager) {
        if (_bleManager.state == CBManagerStatePoweredOn) {
            [_bleManager scanForPeripheralsWithServices:nil options:nil];
        } else {
            __weak typeof(self) weakSelf = self;
            dispatch_after(5, dispatch_get_main_queue(), ^{
                if (weakSelf.bleManager.state == CBManagerStatePoweredOn) {
                    [weakSelf.bleManager scanForPeripheralsWithServices:nil options:nil];
                }
            });
        }
    }
}

#pragma mark Stop Scan

- (void)stopScanBLE {
    if (_bleManager) [_bleManager stopScan];
}


#pragma mark - Bluetooth Device Connection

#pragma mark Disconnect Current Bluetooth Device

- (void)disconnectBLE {
    if (_bleCurrentPeripheral) {
        NSLog(@"BLE --->To disconnectBLE.");
        [_bleManager cancelPeripheralConnection:_bleCurrentPeripheral];
        self.isConnected = false;
        self.currentEntity = nil;
    }
}

#pragma mark Connect Bluetooth Device

- (void)connectBLE:(CBPeripheral *)peripheral {
    if (_bleCurrentPeripheral) {
        [_bleManager cancelPeripheralConnection:_bleCurrentPeripheral];
    }
    _bleCurrentPeripheral = peripheral;
    [_bleCurrentPeripheral setDelegate:self];
    [_bleManager connectPeripheral:_bleCurrentPeripheral options:@{
            CBConnectPeripheralOptionNotifyOnDisconnectionKey: @(YES)}];
    [_bleManager stopScan];

    NSLog(@"BLE Connecting... Name ---> %@", peripheral.name);
}

- (void)connectPeripheralWithUUID:(NSString *)uuid {
    _connectByUUID = uuid;
    [self startScanBLE];

    NSLog(@"sn_log => input uuid: %@", uuid);

    [self findHid:uuid];
}

- (void)findHid:(NSString *)uuid {
    NSUUID *uuidNs = [[NSUUID alloc] initWithUUIDString:uuid];
    NSArray *array = [self.bleManager retrievePeripheralsWithIdentifiers:@[uuidNs]];

    NSLog(@"sn_log => findHid: %@ , array: %@", uuid, array);

    for (CBPeripheral *cbp in array) {
        if ([cbp.identifier.UUIDString isEqualToString:uuid]) {
            NSLog(@"sn_log => reconnect:%@", cbp);
            [self connectBLE:cbp];
            break;
        }
    }

}

- (void)connectAction {

    if (self.connectByUUID == nil) return;

    NSArray<NSUUID *> *uuidArr = @[[[NSUUID alloc] initWithUUIDString:self.connectByUUID]];
    NSArray<CBPeripheral *> *phArr = [_bleManager retrievePeripheralsWithIdentifiers:uuidArr];

    if (phArr.count == 0) {
        return;
    }

    CBPeripheral *peripheral = phArr.firstObject;

    if (peripheral && peripheral.state != CBPeripheralStateConnected &&
        peripheral.state != CBPeripheralStateConnecting) {

        NSString * ble_name = peripheral.name;
        NSString * ble_uuid = peripheral.identifier.UUIDString;
        NSLog(@"FLT Connecting(Last)... Name ---> %@ UUID:%@", ble_name, ble_uuid);

        _bleCurrentPeripheral = peripheral;
        [_bleCurrentPeripheral setDelegate:self];

        [_bleManager connectPeripheral:_bleCurrentPeripheral options:@{
                CBConnectPeripheralOptionNotifyOnDisconnectionKey: @(YES)}];
        _connectByUUID = nil;
    }
}

#pragma mark - CBCentralManagerDelegate

#pragma mark Bluetooth Initialization Callback

- (void)centralManagerDidUpdateState:(CBCentralManager *)central {

    _mBleManagerState = central.state;

    if (_mBleManagerState != CBManagerStatePoweredOn) {
        self.mBlePeripheral = nil;
        self.blePeripheralArr = [NSMutableArray array];
    } else { // Start scanning once Bluetooth is powered on.
        [self findHid:self.connectByUUID];
        [self startScanBLE];
    }
}

#pragma mark Discover Device

- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral
     advertisementData:(NSDictionary

<NSString *,id> *)
advertisementData RSSI
:(NSNumber *)RSSI {

    NSString * ble_name = advertisementData[@"kCBAdvDataLocalName"];
    NSData *ble_AD = advertisementData[@"kCBAdvDataManufacturerData"];
    NSDictionary * info = [JLAdvParse bluetoothAdvParse:self.pairKey AdvData:advertisementData];
    if (ble_name.length == 0) return;

    NSLog(@"Discovered ----> NAME:%@ RSSI:%@ AD:%@", ble_name, RSSI, ble_AD);

//    NSString *key = [[FittingView getFitterKey] uppercaseString];
    NSString * key = @"";
    if ([key isEqualToString:@""]) {
        [self addPeripheral:peripheral RSSI:RSSI Name:ble_name Info:info];
    } else {
        if ([[ble_name uppercaseString] rangeOfString:key].location == NSNotFound) {
            //
            NSLog(@"Filtered ----> NAME:%@ RSSI:%@ AD:%@", ble_name, RSSI, ble_AD);
        } else {
            [self addPeripheral:peripheral RSSI:RSSI Name:ble_name Info:info];
        }
    }

    [DFNotice post:kFLT_BLE_FOUND Object:_blePeripheralArr];

    // Used for OTA reconnection during upgrade.
    if ([JLAdvParse otaBleMacAddress:self.lastBleMacAddress isEqualToCBAdvDataManufacturerData:ble_AD]) {
        [self connectBLE:peripheral];
    }
}

- (void)addPeripheral:(CBPeripheral *)peripheral RSSI:(NSNumber *)rssi Name:(NSString *)name Info:(NSDictionary *)info {
    int flag = 0;
    for (JLBleEntity *bleEntity in _blePeripheralArr) {
        CBPeripheral *info_pl = bleEntity.mPeripheral;
        NSString * info_uuid = info_pl.identifier.UUIDString;
        NSString * ble_uuid = peripheral.identifier.UUIDString;
        if ([info_uuid isEqualToString:ble_uuid]) {
            bleEntity.mRSSI = rssi;
            flag = 1;
            break;
        }
    }
    if (flag == 0 && name.length > 0) {
        JLBleEntity *bleEntity = [JLBleEntity new];
        bleEntity.mName = name ?: @"Unknow";
        bleEntity.mRSSI = rssi;
        bleEntity.mType = [info[@"TYPE"] intValue];
        bleEntity.edrMacAddress = info[@"EDR"];
        NSLog(@"type:%d,name:%@", [info[@"TYPE"] intValue], name);
        bleEntity.mPeripheral = peripheral;
        [_blePeripheralArr addObject:bleEntity];
    }
    if (_connectByUUID && [peripheral.identifier.UUIDString isEqualToString:_connectByUUID]) {
        [self stopScanBLE];
        [self connectAction];
    }
}

#pragma mark Device Connection Callback

- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral {
    NSLog(@"BLE Connected ---> Device %@", peripheral.name);
    for (JLBleEntity *entity in self.blePeripheralArr) {
        if ([entity.mPeripheral.identifier.UUIDString isEqualToString:peripheral.identifier.UUIDString]) {
            self.currentEntity = entity;
            break;
        }
    }
    self.isConnected = YES;

    _otaManager.mBLE_NAME = peripheral.name;
    _otaManager.mBLE_UUID = peripheral.identifier.UUIDString;

    [DFNotice post:kFLT_BLE_CONNECTED Object:peripheral];
    // Discover services after connection succeeds.
    [peripheral discoverServices:nil];
}

- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(nullable NSError

*)error {
    NSLog(@"Err:BLE Connect FAIL ---> Device:%@ Error:%@", peripheral.name, [error description]);
}

#pragma mark Device Disconnect Callback

- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(nullable NSError

*)error {
    NSLog(@"BLE Disconnect ---> Device %@ error:%d", peripheral.name, (int) error.code);

    [_otaManager noteEntityDisconnected];
    self.isConnected = NO;
    self.pairStatus = NO;
    /*--- UI refresh: device disconnected. ---*/
    [[NSNotificationCenter defaultCenter] postNotificationName:kFLT_BLE_DISCONNECTED object:peripheral];
}

#pragma mark - CBPeripheralDelegate

#pragma mark Device Service Callback

- (void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(nullable NSError

*)error {
    if (error) {
        NSLog(@"Err: Discovered services fail.");
        return;
    }
    _mBlePeripheral = peripheral;
    for (CBService *service in peripheral.services) {
        // Pass a CBUUID array as the first parameter when specific characteristics are known.
        //if ([service.UUID.UUIDString isEqual:FLT_BLE_SERVICE]) {
        NSLog(@"BLE Service ---> %@", service.UUID.UUIDString);
        [peripheral discoverCharacteristics:nil forService:service];
        //break;
        //}
    }
}

#pragma mark Device Characteristic Callback

- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(nullable NSError

*)error {
    if (error) {
        NSLog(@"Err: Discovered Characteristics fail.");
        return;
    }

    if ([service.UUID.UUIDString isEqual:FLT_BLE_SERVICE]) {

        for (CBCharacteristic *character in service.characteristics) {
            /*--- RCSP ---*/
            if ([character.UUID.UUIDString isEqual:FLT_BLE_RCSP_W]) {
                NSLog(@"BLE Get Rcsp(Write) Channel ---> %@", character.UUID.UUIDString);
                self.mRcspWrite = character;
            }

            if ([character.UUID.UUIDString isEqual:FLT_BLE_RCSP_R]) {
                NSLog(@"BLE Get Rcsp(Read) Channel ---> %@", character.UUID.UUIDString);
                self.mRcspRead = character;
                [peripheral setNotifyValue:YES forCharacteristic:character];

                if (self.mRcspRead.properties == CBCharacteristicPropertyRead) {
                    [peripheral readValueForCharacteristic:character];
                    NSLog(@"BLE  Rcsp(Read) Read Value For Characteristic.");
                }
            }
        }
    }
}

#pragma mark Update Notify Characteristic State

- (void)peripheral:(CBPeripheral *)peripheral didUpdateNotificationStateForCharacteristic:(nonnull CBCharacteristic

*)
characteristic error
:(
nullable NSError
*)error {

    if (error) {
        NSLog(@"Err: Update NotificationState For Characteristic fail.");
        return;
    }

    if ([characteristic.service.UUID.UUIDString isEqual:FLT_BLE_SERVICE] &&
        [characteristic.UUID.UUIDString isEqual:FLT_BLE_RCSP_R] &&
        characteristic.isNotifying == YES) {

        __weak typeof(self) weakSelf = self;
        self.bleMtu = [peripheral maximumWriteValueLengthForType:CBCharacteristicWriteWithoutResponse];
        NSLog(@"BLE ---> MTU:%lu", (unsigned long) self.bleMtu);
        if (self.isPaired == YES) {
            [_pairHash hashResetPair];
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.3 * NSEC_PER_SEC)),
                           dispatch_get_main_queue(), ^{
                        // Device authentication.
                        [self->_pairHash bluetoothPairingKey:self.pairKey Result:^(BOOL ret) {
                            if (ret) {
                                weakSelf.lastUUID = peripheral.identifier.UUIDString;
                                weakSelf.lastBleMacAddress = nil;
                                [[NSNotificationCenter defaultCenter] postNotificationName:kFLT_BLE_PAIRED object:peripheral];
                                [weakSelf.otaManager noteEntityConnected];
                                weakSelf.pairStatus = YES;
                            } else {
                                NSLog(@"JL_Assist Err: bluetooth pairing fail.");
                                [weakSelf.bleManager cancelPeripheralConnection:peripheral];
                            }
                        }];
                    });
        } else {
            self.lastUUID = peripheral.identifier.UUIDString;
            self.lastBleMacAddress = nil;
            [[NSNotificationCenter defaultCenter] postNotificationName:kFLT_BLE_PAIRED object:peripheral];
            [self.otaManager noteEntityConnected];
        }
    }
    self.isConnected = YES;
}

#pragma mark Device Data Callback

- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error {
    if (error) {
        NSLog(@"Err: receive data fail.");
        return;
    }

    if (_isPaired == YES && _pairStatus == NO) {
        // Received device authentication data.
        [_pairHash inputPairData:characteristic.value];
    } else {
        // Received normal device communication data.
        [_otaManager cmdOtaDataReceive:characteristic.value];
    }

}

- (void)peripheralIsReadyToSendWriteWithoutResponse:(CBPeripheral *)peripheral {

#if SENDBYSINGLE
    [[SingleDataSender share] sendSingle];
#endif

}


#pragma mark - Jieli OTA SDK Flow

/**
 *  Gets connected device information. If the previous upgrade did not finish,
 *  the SDK asks the caller to run otaFuncWithFilePath: for a forced upgrade.
 */
- (void)getDeviceInfo:(GET_DEVICE_CALLBACK _Nonnull)callback {
    /*--- Get device information. ---*/
    _getCallback = callback;
    [_otaManager cmdTargetFeature];
}

/**
 *  OTA update.
 *  @param otaFilePath OTA firmware file path.
 */
- (void)otaFuncWithFilePath:(NSString *)otaFilePath {
    NSLog(@"current otaFilePath ---> %@", otaFilePath);
    self.selectedOtaFilePath = otaFilePath;
    NSData *otaData = [[NSData alloc] initWithContentsOfFile:otaFilePath];

    [_otaManager cmdOTAData:otaData Result:^(JL_OTAResult result, float progress) {
        for (id <JLBleManagerOtaDelegate> objc in self.delegates) {
            if ([objc respondsToSelector:@selector(otaProgressWithOtaResult:withProgress:)]) {
                [objc otaProgressWithOtaResult:result withProgress:progress];
            }
        }
    }];
}

- (void)otaFuncCancel:(CANCEL_CALLBACK _Nonnull)result {

    [_otaManager cmdOTACancelResult:^(uint8_t status, uint8_t sn, NSData *_Nullable data) {
        result(status);
    }];
}


//MARK: - ota manager delegate callback
- (void)otaCancel {
    // TODO: Handle OTA cancellation callback.
}

- (void)otaUpgradeResult:(JL_OTAResult)result Progress:(float)progress {
    // TODO: Handle OTA progress and state callback.
}

- (void)otaDataSend:(NSData *)data {
    [self writeDataByCbp:data];
}

- (void)otaFeatureResult:(JL_OTAManager *)manager {

    NSLog(@"getDeviceInfo:%d", __LINE__);
    if (manager.otaStatus == JL_OtaStatusForce) {
        NSLog(@"---> Entering forced upgrade.");
        if (self.selectedOtaFilePath) {
            [self otaFuncWithFilePath:self.selectedOtaFilePath];
        } else {
            _getCallback(true);
        }
        return;
    } else {
        if (manager.otaHeadset == JL_OtaHeadsetYES) {
            NSLog(@"---> Entering forced upgrade: updating the other earbud.");
            if (self.selectedOtaFilePath) {
                [self otaFuncWithFilePath:self.selectedOtaFilePath];
            } else {
                _getCallback(true);
            }
            return;
        }
    }
    NSLog(@"---> Device is ready for normal use...");
    dispatch_async(dispatch_get_main_queue(), ^{
        /*--- Get common device information. ---*/
        [self->_otaManager cmdSystemFunction];
        self->_getCallback(false);
    });

}

//MARK: - Hash pair delegate callback

- (void)hashOnPairOutputData:(NSData *)data {
    [self writeDataByCbp:data];
}


//MARK: - data send manager

/// Sends data in MTU-sized chunks.
/// - Parameter data: Data to send.
- (void)writeDataByCbp:(NSData *)data {
    //    NSLog(@"%s:data:%@",__func__,data);
    if (_mBlePeripheral && self.mRcspWrite) {
        if (data.length > 0) {
            NSInteger len = data.length;
            while (len > 0) {
                if (len <= _bleMtu) {
                    NSData *mtuData = [data subdataWithRange:NSMakeRange(0, data.length)];
                    [self selectSendAction:mtuData];
                    len -= data.length;
                } else {
                    NSData *mtuData = [data subdataWithRange:NSMakeRange(0, _bleMtu)];
                    [self selectSendAction:mtuData];
                    len -= _bleMtu;
                    data = [data subdataWithRange:NSMakeRange(_bleMtu, len)];
                }
            }
        }
    } else {
        // The write characteristic must be initialized first.
        NSLog(@"need to init");
    }
}

- (void)selectSendAction:(NSData *)data {

#if SENDBYSINGLE
    [[SingleDataSender share] appendSend:data];
#else
    [_mBlePeripheral writeValue:data
              forCharacteristic:self.mRcspWrite
                           type:CBCharacteristicWriteWithoutResponse];
#endif

}


//MARK: - Send Through Signal Gate
- (void)singleDidSendData:(NSData *)data {
    [_mBlePeripheral writeValue:data
              forCharacteristic:self.mRcspWrite
                           type:CBCharacteristicWriteWithoutResponse];
}


@end


