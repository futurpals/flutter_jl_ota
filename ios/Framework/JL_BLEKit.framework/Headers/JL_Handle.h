//
//  JL_Handle.h
//  JL_BLEKit
//
//  Created by zhihui liang on 2018/11/10.
//  Copyright © 2018 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_FlashOperateManager.h>
#import <JL_BLEKit/JL_BLEAction.h>
#import <JL_BLEKit/JL_RCSP.h>

NS_ASSUME_NONNULL_BEGIN

/**
 */
extern NSString *kJL_CMD_RECEIVE;

@protocol JL_HandleDelegate <NSObject>
@optional
-(void)onHandleOutputPKG:(JL_PKG*)pkg;
@end

@interface JL_Handle : NSObject
@property(nonatomic,weak)id<JL_HandleDelegate>delegate;

/**
BLE
*/
-(void)inputHandleData:(NSData*)data;

/**[]
JL_PKG。
*/
-(NSData*)sendPackage:(JL_PKG*)pkg WithName:(NSString*)name;

+(void)logPackage:(JL_PKG*)pkg WithName:(NSString *__nullable)name IsSend:(BOOL)isSend;

@end

NS_ASSUME_NONNULL_END
