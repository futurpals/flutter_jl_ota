//
//  JLModelCardInfo.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/11/30.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JLModel_File.h>

NS_ASSUME_NONNULL_BEGIN

@interface JLCardInfo : NSObject

/// 0x00 USB
/// 0x01 SD0
/// 0x02 SD1
/// 0x03 flash
/// 0x04 lineIn
/// 0x05 flash2
/// 0x06 flash3
/// 0x07 ReservedArea
@property(nonatomic,assign)uint8_t type;

@property(nonatomic,assign)BOOL isOnline;

@property(nonatomic,copy)NSData *handle;

@end

@interface JLModelCardInfo:NSObject

@property(nonatomic,assign)uint8_t version;

@property(nonatomic,strong,readonly)NSArray *cardArray;

@property (nonatomic, assign) BOOL usbOnline;

@property (nonatomic, assign) BOOL sd0Online;

@property (nonatomic, assign) BOOL sd1Online;

@property (nonatomic, assign) BOOL lineInOnline;

@property (nonatomic, assign) BOOL flashOnline;

@property (nonatomic, assign) BOOL flash2Online;

@property (nonatomic, assign) BOOL flash3Online;

@property (nonatomic, assign) BOOL reservedAreaOnline;

@property (nonatomic, assign) BOOL isComplex;

@property (nonatomic, copy)NSData *usbHandle;

@property (nonatomic, copy)NSData *sd0Handle;

@property (nonatomic, copy)NSData *sd1Handle;

@property (nonatomic, copy)NSData *flashHandle;

@property (nonatomic, copy)NSData *flash2Handle;

@property (nonatomic, copy)NSData *flash3Handle;

@property (nonatomic, copy)NSData *reservedAreaHandle;

@property (nonatomic, strong)NSArray <JLCardInfo *> *cardInfos;

-(instancetype)initData:(NSData *)data;

-(BOOL)hasStorageCard;

-(NSData *_Nullable)getCardHandle:(JL_CardType)cardType;

@end




NS_ASSUME_NONNULL_END
