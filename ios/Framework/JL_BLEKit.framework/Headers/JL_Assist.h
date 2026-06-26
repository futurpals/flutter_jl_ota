//
//  JL_Assist.h
//  QCY_Demo
//
//  Created by Jieli Technology on 2021/8/12.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>


@protocol JL_AssistDelegate <NSObject>

-(void)assistDidWriteData:(NSData *_Nonnull)data;

@end

NS_ASSUME_NONNULL_BEGIN
typedef void(^JL_Assist_BK)(BOOL isPaired);

@class JL_ManagerM;

@interface JL_Assist : NSObject
@property(strong,nonatomic)JL_ManagerM        *mCmdManager;
@property(strong,nonatomic)NSString           *mService;
@property(strong,nonatomic)NSString           *mRcsp_W;
@property(strong,nonatomic)NSString           *mRcsp_R;
@property(strong,nonatomic)NSData *__nullable mPairKey;
@property(assign,nonatomic)BOOL               mNeedPaired;
@property(assign,nonatomic)BOOL               mLogData;
@property(assign,nonatomic)NSInteger          mLimitMtu;
@property(strong,nonatomic)CBPeripheral       *__nullable mRcspPeripheral;
@property(strong,nonatomic)CBCharacteristic   *__nullable mRcspWrite;
@property(strong,nonatomic)CBCharacteristic   *__nullable mRcspRead;
@property(strong,nonatomic)NSString           *mBleName;

/// @discussion JL_AssistDelegate
@property(assign,nonatomic)id<JL_AssistDelegate> __nullable mDelegate;

/// Execute in a method 「- (void)centralManagerDidUpdateState:」
/// @param state CBManagerState
-(void)assistUpdateState:(CBManagerState)state;

/// Execute in a method 「- (void)centralManager:didDisconnectPeripheral:error:」
/// @param peripheral CBPeripheral
-(void)assistDisconnectPeripheral:(CBPeripheral *)peripheral;


/// Execute in a method 「- (void)peripheral:didDiscoverServices:」
/// @param service CBService
/// @param peripheral CBPeripheral
-(void)assistDiscoverCharacteristicsForService:(CBService*)service
                                    Peripheral:(CBPeripheral*)peripheral;

/// Execute in a method 「- (void)peripheral:didUpdateNotificationStateForCharacteristic:error:」
/// @param characteristic CBCharacteristic
/// @param peripheral CBPeripheral
-(void)assistUpdateCharacteristic:(nonnull CBCharacteristic *)characteristic
                       Peripheral:(CBPeripheral*)peripheral
                           Result:(JL_Assist_BK)result;

/// Execute in a method 「- (void)peripheral:didUpdateValueForCharacteristic:error:」
/// @param characteristic CBCharacteristic
-(void)assistUpdateValueForCharacteristic:(CBCharacteristic *)characteristic;


/// Execute in a method 「- (void)peripheral:didWriteValueForCharacteristic:error:」
/// Execute in a method 「- (void)peripheral:didIsReadyForWrite:error:」
-(void)assistDidReady;

@end

NS_ASSUME_NONNULL_END
