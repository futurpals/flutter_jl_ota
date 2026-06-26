//
//  JLDevicesAdv.h
//  JL_AdvParse
//
//  Created by EzioChan on 2023/12/12.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JLAdvParse.h"


NS_ASSUME_NONNULL_BEGIN

@interface JLDevicesAdv : NSObject

@property(nonatomic,assign)uint16_t uid;

@property(nonatomic,assign)uint16_t pid;

@property(nonatomic,assign)JL_DeviceType type;

@property(nonatomic,assign)uint8_t version;

@property(nonatomic,copy)NSData *variableData;

- (instancetype)initWithData:(NSData *)data;


+(JLDevicesAdv *__nullable)advertDataToModel:(NSData *)basicData;

+(JLDevicesAdv *__nullable)advertDataHexStrToModel:(NSString *)basicHexStr;

@end



NS_ASSUME_NONNULL_END
