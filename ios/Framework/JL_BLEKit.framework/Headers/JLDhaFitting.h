//
//  JLDhaFitting.h
//  JL_BLEKit
//
//  Created by EzioChan on 2022/6/28.
//  Copyright © 2022 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_TypeEnum.h>

NS_ASSUME_NONNULL_BEGIN



@class JL_ManagerM;

typedef NS_ENUM(UInt8, DhaChannel) {
    DhaChannel_left = 0x00,
    DhaChannel_right = 0x01
};

typedef NS_ENUM(UInt8, DhaFittingType) {
    DhaFittingType_left = 0x00,
    DhaFittingType_right = 0x00,
    DhaFittingType_All = 0x00,
};


@interface DhaFittingInfo : NSObject
@property(nonatomic,assign)uint8_t version;
@property(nonatomic,assign)uint8_t ch_num;
@property(nonatomic,strong)NSArray *ch_freq;

- (instancetype)initWithData:(NSData *)basicData;

@end

@interface DhaFittingSwitch : NSObject

@property(nonatomic,assign)BOOL leftOn;

@property(nonatomic,assign)BOOL rightOn;

@end


@interface DhaFittingData : NSObject<NSCopying>
@property(nonatomic,assign)DhaChannel channel;

@property(nonatomic,assign)BOOL leftOn;
@property(nonatomic,assign)BOOL rightOn;

@property(nonatomic,assign)uint8_t reserved;
@property(nonatomic,assign)uint16_t freq;
@property(nonatomic,assign)float gain;

-(NSData*)beData;

@end


typedef void(^DhaInfoBlock)(DhaFittingInfo *info,NSArray <NSNumber *>*gains);


@interface JLDhaFitting : NSObject

/// @param manager manager
+(void)auxiGetInfo:(DhaInfoBlock)result Manager:(JL_ManagerM*)manager;

/// @param manager manager
-(void)auxiCheckByStep:(DhaFittingData *)dhaFit Manager:(JL_ManagerM*)manager Result:(JL_CMD_RESPOND __nullable)result;

-(void)auxiCloseManager:(JL_ManagerM*)manager Result:(JL_CMD_RESPOND __nullable)result;

/// @param manager manager
-(void)auxiSaveGainsList:(NSArray <DhaFittingData *>*) gains Manager:(JL_ManagerM*)manager  Type:(DhaFittingType)type Result:(JL_CMD_RESPOND __nullable)result;

@end

NS_ASSUME_NONNULL_END
