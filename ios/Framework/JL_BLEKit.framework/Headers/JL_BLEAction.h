//
//  JL_BLEAction.h
//  JL_BLEKit
//
//  Created by zhihui liang on 2018/11/10.
//  Copyright © 2018 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 */
extern NSString *kJL_RCSP_RECEIVE;
extern NSString *kJL_RCSP_SEND;


typedef void(^ATC_Block)(BOOL ret);
@protocol JL_BLEActionDelegate <NSObject>
@optional
-(void)onPairOutputData:(NSData*)data;

@end

@interface JL_BLEAction : NSObject
@property(nonatomic,weak)id<JL_BLEActionDelegate>delegate;

+(id)sharedMe;

/**
 */
+(NSDictionary*)bluetoothKey_1:(NSData*)key Filter:(NSDictionary*)advertData;

/**
 */
-(void)bluetoothPairingKey:(NSData *__nullable)pKey Result:(ATC_Block)bk;
-(void)inputPairData:(NSData*)rData;
-(void)cancelPair;

#pragma mark - Vendor SDK

/**
 */
+ (NSString * _Nullable)otaBleMacAddressFromCBAdvDataManufacturerData:(NSData *)kCBAdvDataManufacturerData;

/**
 */
+ (Boolean)otaBleMacAddress:(NSString *)otaBleMacAddress isEqualToCBAdvDataManufacturerData:(NSData *)kCBAdvDataManufacturerData;

@end

NS_ASSUME_NONNULL_END
