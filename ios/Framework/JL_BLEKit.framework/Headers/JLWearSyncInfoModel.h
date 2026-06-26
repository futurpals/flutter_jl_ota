//
//  JLWearSyncInfoModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/27.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JLWatchEnum.h"

NS_ASSUME_NONNULL_BEGIN

@interface JLWearSyncDataModel : NSObject

@property(nonatomic,strong)NSData *basicData;

@end


@interface JLWearSyncInfoModel : JLWearSyncDataModel

@property(nonatomic,assign)uint8_t sportType;

@property(nonatomic,assign)WatchSportStatus status;

@property(nonatomic,assign)double sportID;

@property(nonatomic,assign)BOOL  hasGPS;

@property(nonatomic,assign)WatchHeartRateType heartRateType;

@property(nonatomic,assign)UInt16   interval;

+(JLWearSyncInfoModel *)initWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
