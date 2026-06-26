//
//  JLDialInfoExtentedModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2024/2/20.
//  Copyright © 2024 www.zh-jieli.com. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class JL_ManagerM;

/// device dial information extended model
@interface JLDialInfoExtentedModel : NSObject


/// shape of screen
/// default 0x01 circular
@property(nonatomic, assign) uint8_t shape;


/// radius of circle
@property(nonatomic, assign) CGFloat radius;

/// background color
/// default is clean color
@property(nonatomic, strong) UIColor *backgroundColor;

/// default is (240 * 240)
/// device screen sice
@property(nonatomic, assign) CGSize size;


/// initialize
-(instancetype)initWithData:(NSData *)data Manager:(JL_ManagerM*)manager;

@end

NS_ASSUME_NONNULL_END
