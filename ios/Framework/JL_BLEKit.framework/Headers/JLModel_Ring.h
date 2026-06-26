//
//  JLModel_Ring.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/10/15.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface JLModel_Ring : NSObject

/// alarm default rings index
@property(assign,nonatomic) uint8_t         index;

/// alarm default rings name
@property(strong,nonatomic) NSString        *name;
@end

NS_ASSUME_NONNULL_END
