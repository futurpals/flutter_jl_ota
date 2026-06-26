//
//  JLModelDevFunc.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/11/29.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface JLModelDevFunc : NSObject

@property (nonatomic, assign) uint8_t currentModel;

@property (nonatomic, assign) BOOL isSupportEDR;

@property (nonatomic, assign) BOOL isSupportDevMusic;

@property (nonatomic, assign) BOOL isSupportDevRTC;

@property (nonatomic, assign) BOOL isSupportDevLineIn;

@property (nonatomic, assign) BOOL isSupportDevFm;

@property (nonatomic, assign) BOOL isSupportDevLight;

@property (nonatomic, assign) BOOL isSupportDevFMTX;

@property (nonatomic, assign) BOOL isSupportDevEQ;

@property (nonatomic, assign, readonly) BOOL isSupportSPDIF;

@property (nonatomic, assign, readonly) BOOL isSupportPCServer;

@property (nonatomic, assign) BOOL isShowOfflineFunc;

@property (nonatomic, assign) BOOL isSupportUSB;

@property (nonatomic, assign) BOOL isSupportSD0;

@property (nonatomic, assign) BOOL isSupportSD1;

@property (nonatomic, assign) BOOL isSupportNetRadio;

-(instancetype)initWithData:(NSData *)data;

@end



NS_ASSUME_NONNULL_END
