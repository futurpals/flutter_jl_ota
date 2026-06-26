//
//  JLModel_EQ.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/10/15.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_TypeEnum.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_EQMode) {
    JL_EQModeNORMAL                 = 0,
    JL_EQModeROCK                   = 1,
    JL_EQModePOP                    = 2,
    JL_EQModeCLASSIC                = 3,
    JL_EQModeJAZZ                   = 4,
    JL_EQModeCOUNTRY                = 5,
    JL_EQModeCUSTOM                 = 6,
    JL_EQModeLATIN                  = 7,
    JL_EQModeDANCE                  = 8,
};

@interface JLModel_EQ : NSObject
@property(assign,nonatomic)JL_EQMode        mMode;
@property(strong,nonatomic)NSArray *__nullable mEqArray;
@end

NS_ASSUME_NONNULL_END
