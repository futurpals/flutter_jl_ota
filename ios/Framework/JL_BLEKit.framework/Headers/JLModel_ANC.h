//
//  JLModel_ANC.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/10/15.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8,JL_AncMode) {
    JL_AncMode_Normal               = 0,
    JL_AncMode_NoiseReduction       = 1,
    JL_AncMode_Transparent          = 2,
};

@interface JLModel_ANC : NSObject
@property(assign,nonatomic)JL_AncMode       mAncMode;
@property(assign,nonatomic) uint16_t        mAncMax_L;
@property(assign,nonatomic) uint16_t        mAncCurrent_L;
@property(assign,nonatomic) uint16_t        mAncMax_R;
@property(assign,nonatomic) uint16_t        mAncCurrent_R;
-(NSData*)dataModel;
@end



@interface JLTWSAddrNameInfo : NSObject

@property(nonatomic,assign)uint8_t isBind;

@property(nonatomic,strong)NSData *phoneEdrAddr;

@property(nonatomic,strong)NSString *phoneName;

+(NSArray<JLTWSAddrNameInfo *>*)dataBeObjc:(NSData *)data;

@end
NS_ASSUME_NONNULL_END
