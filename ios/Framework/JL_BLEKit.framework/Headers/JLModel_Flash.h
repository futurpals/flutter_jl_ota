//
//  JLModel_Flash.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/10/15.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_TypeEnum.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_FlashSystemType) {
    JL_FlashSystemType_FATFS        = 0,
    JL_FlashSystemType_RCSP         = 1,
};

@interface JLModel_Flash : NSObject

@property(assign,nonatomic)uint32_t         mFlashSize;

@property(assign,nonatomic)uint32_t         mFatfsSize;

@property(assign,nonatomic)JL_FlashSystemType mFlashType;

@property(assign,nonatomic)uint8_t          mFlashStatus;

@property(assign,nonatomic)uint16_t         mFlashVersion;

@property(assign,nonatomic)uint16_t         mFlashReadMtu;

@property(assign,nonatomic)uint16_t         mFlashCluster;

@property(strong,nonatomic)NSString         *mFlashMatchVersion;

@property(assign,nonatomic)uint16_t         mFlashWriteMtu;

@property(assign,nonatomic)uint16_t         mScreenWidth;

@property(assign,nonatomic)uint16_t         mScreenHeight;

+(JLModel_Flash*)modelWithFlash:(NSData *)flashData;

@end

NS_ASSUME_NONNULL_END
