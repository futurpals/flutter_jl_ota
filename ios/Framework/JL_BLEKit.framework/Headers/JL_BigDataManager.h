//
//  JL_BigDataManager.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2022/12/7.
//  Copyright © 2022 www.zh-jieli.com. All rights reserved.
//

#import <JL_BLEKit/JL_FunctionBaseManager.h>

NS_ASSUME_NONNULL_BEGIN


@class JL_BigData;

typedef NS_ENUM(UInt8, JL_BigDataStatus) {
    JL_BigDataStatusSendSuccess               = 0,
    JL_BigDataStatusSendFailCRC               = 1,
    JL_BigDataStatusSendFailSEQ               = 2,
    JL_BigDataStatusSendFailFormat            = 3,
    JL_BigDataStatusSendFailWay               = 4,
    JL_BigDataStatusSendFailOutOfRange        = 5,
    JL_BigDataStatusSendFailWrite             = 6,
    JL_BigDataStatusSendFailMissingParameter  = 7,
    JL_BigDataStatusSendFailCmd               = 8,
    JL_BigDataStatusSendFailTimeout           = 9,
    JL_BigDataStatusGet                       = 10,
    JL_BigDataStatusSendFailUnknown           = 0xff,
};
typedef void(^JL_BIGDATA_RT)(JL_BigData *bigData);

@interface JL_BigDataManager : JL_FunctionBaseManager

-(void)cmdBigDataMonitor:(JL_BIGDATA_RT)result;

-(void)cmdInputBigData:(JL_BigData*)data;

@end

@interface JL_BigData : NSObject
@property(nonatomic,assign)JL_BigDataStatus mResult;
@property(nonatomic,assign)NSInteger        mIndex;

@property(nonatomic,assign)uint8_t          mType;
@property(nonatomic,assign)uint8_t          mVersion;
@property(nonatomic,strong)NSData           *mData;
@end

NS_ASSUME_NONNULL_END
