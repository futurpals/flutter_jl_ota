//
//  JLBleEntity.h
//  JL_OTA
//
//  Created by the Jieli OTA sample on 2021/10/11.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>


NS_ASSUME_NONNULL_BEGIN

@interface JLBleEntity : NSObject                                // Bluetooth device model.

@property (strong, nonatomic) NSNumber *mRSSI;
@property (strong, nonatomic) CBPeripheral *mPeripheral;
@property (strong, nonatomic) NSString *mName;
@property (strong, nonatomic) NSString *bleMacAddress;
@property (strong, nonatomic) NSString *edrMacAddress;
@property (assign, nonatomic) uint8_t mType;
@property (assign, nonatomic) uint16_t pid;
@property (assign, nonatomic) uint16_t uid;

@end

NS_ASSUME_NONNULL_END
