//
//  JL_SDM_AirPressure.h
//  Test
//
//  Created by EzioChan on 2021/4/6.
//  Copyright © 2021 Zhuhai Jieli Technology Co.,Ltd. All rights reserved.
//

#import "JLSportDataModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface JL_SDM_AirPressure : JLSportDataModel
@property(nonatomic,assign)int realTime;
@property(nonatomic,assign)int max;
@property(nonatomic,assign)int min;

+(JL_SDM_AirPressure*)responseData:(NSData *)value subMask:(NSData *)submask;

+(JL_SDM_AirPressure*)requireRealTime:(BOOL)rt min:(BOOL)min Max:(BOOL)max;



@end

NS_ASSUME_NONNULL_END
