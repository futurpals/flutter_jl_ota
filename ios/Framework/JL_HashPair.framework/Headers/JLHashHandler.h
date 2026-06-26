//
//  JLHashHandler.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/1/30.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JLLogHelper/JLLogHelper.h>

NS_ASSUME_NONNULL_BEGIN

typedef void(^JLHashBlock)(BOOL ret);

@protocol JLHashHandlerDelegate <NSObject>

/// 需要发送到设备校验认证的数据
/// - Parameter data: 数据
-(void)hashOnPairOutputData:(NSData*)data;

@end


/// 设备认证
@interface JLHashHandler : NSObject

@property(nonatomic,weak)id<JLHashHandlerDelegate> delegate;


/// APP端发起设备认证
/// - Parameters:
///   - pKey: 加密Key（默认为空）
///   - bk: 配对认证回调结果
-(void)bluetoothPairingKey:(NSData *__nullable)pKey Result:(JLHashBlock)bk;


/// 重置设备认证过程
-(void)hashResetPair;


/// 填入设备回复数据
/// - Parameter rData: 数据
-(void)inputPairData:(NSData*)rData;


/// 停止设备认证过程
/// stop device pairing
-(void)stopAuthPair;


/// 打印当前SDK的版本
+(void)sdkVersion;



@end

NS_ASSUME_NONNULL_END
