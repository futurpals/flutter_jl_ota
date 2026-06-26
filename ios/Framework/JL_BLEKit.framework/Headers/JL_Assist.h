//
//  JL_Assist.h
//  QCY_Demo
//
//  Created by 杰理科技 on 2021/8/12.
//  Copyright © 2021 杰理科技. All rights reserved.
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
@property(strong,nonatomic)JL_ManagerM        *mCmdManager;   //命令中心
@property(strong,nonatomic)NSString           *mService;      //服务号
@property(strong,nonatomic)NSString           *mRcsp_W;       //特征：RCSP写
@property(strong,nonatomic)NSString           *mRcsp_R;       //特征：RCSP读
@property(strong,nonatomic)NSData *__nullable mPairKey;       //握手(配对)秘钥
@property(assign,nonatomic)BOOL               mNeedPaired;    //是否需要配对
@property(assign,nonatomic)BOOL               mLogData;       //是否打印裸数据
@property(assign,nonatomic)NSInteger          mLimitMtu;      //(默认40)在最大的MTU基础上减少数据量
@property(strong,nonatomic)CBPeripheral       *__nullable mRcspPeripheral;
@property(strong,nonatomic)CBCharacteristic   *__nullable mRcspWrite;
@property(strong,nonatomic)CBCharacteristic   *__nullable mRcspRead;
@property(strong,nonatomic)NSString           *mBleName;      //设备名字

///代理,如果实现了此代理则发出的数据都需要走回调发送，内部不处理
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
/// @param result JL_Assist_BK （YES:配对成功   NO:配对失败）
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
