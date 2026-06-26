//
//  JL4GUpgradeManager.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/12/18.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JLPublicSettingBlocks.h"

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(uint8_t, JL4GUpgradeStatus) {
    JL4GUpgradeStatusFinish = 0x00,
    JL4GUpgradeStatusStart = 0x01,
    JL4GUpgradeStatusTransporting = 0x02,
    JL4GUpgradeStatusDeviceProcessing = 0xff
};

@class JL4GUpgradeManager;

@protocol JL4GUpgradeDelegate  <NSObject>

/// - Parameters:
-(void)jl4GUpgradeResult:(JL4GUpgradeManager *)mgr Status:(JL4GUpgradeStatus) status Progress:(float)progress Code:(uint8_t)code error:(NSError * _Nullable)error;

-(void)jl4GGetDeviceInfo:(JLPublic4GModel *)g4Model;

@end

@class JL_ManagerM;

@interface JL4GUpgradeManager : NSObject

+(instancetype)share;

@property(nonatomic,strong)JLPublic4GModel *g4Model;

@property(nonatomic,weak) id<JL4GUpgradeDelegate> delegate;

/// - Parameters:
-(void)cmdGetDevice4GInfo:(JL_ManagerM *)manager result:(JLPSSource4GCbk)result;


/// - Parameters:
-(void)cmdStartUpgrade4G:(JL_ManagerM *)manager Data:(NSData *)data;

-(void)cmdCancel4GUpgrade:(JL_ManagerM *)manager;

@end

NS_ASSUME_NONNULL_END
