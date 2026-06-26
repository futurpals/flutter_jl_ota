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

-(void)hashOnPairOutputData:(NSData*)data;

@end


@interface JLHashHandler : NSObject

@property(nonatomic,weak)id<JLHashHandlerDelegate> delegate;


/// - Parameters:
-(void)bluetoothPairingKey:(NSData *__nullable)pKey Result:(JLHashBlock)bk;


-(void)hashResetPair;


-(void)inputPairData:(NSData*)rData;


/// stop device pairing
-(void)stopAuthPair;


+(void)sdkVersion;



@end

NS_ASSUME_NONNULL_END
