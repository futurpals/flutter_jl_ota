//
//  JL_BatchManger.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/12/21.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_FunctionBaseManager.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JL_Tools.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_BatchType) {
    BatchType_Begin =  0x00,
    BatchType_Finish = 0x80,
    BatchType_Cancel = 0x81,
};

typedef NS_ENUM(NSUInteger, JL_BatchOptionType) {
    BatchOption_Format = 0x00,
    BatchOption_unKnow = 0xFF,
};

@interface JL_BatchManger : JL_FunctionBaseManager

#pragma mark - Vendor SDK
typedef void(^JL_BATCH_BK)(uint8_t flag);
/**
 */
-(void)cmdBatchType:(JL_BatchType)type
         Operations:(NSArray<NSNumber *>*)array
             Result:(JL_BATCH_BK __nullable)result;

@end

NS_ASSUME_NONNULL_END
