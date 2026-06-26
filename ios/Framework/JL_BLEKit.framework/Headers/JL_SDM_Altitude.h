//
//  JL_SDM_Altitude.h
//  Test
//
//  Created by EzioChan on 2021/4/6.
//  Copyright © 2021 Zhuhai Jieli Technology Co.,Ltd. All rights reserved.
//

#import "JLSportDataModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface JL_SDM_Altitude : JLSportDataModel

@property(nonatomic,assign)float max;
@property(nonatomic,assign)float min;
@property(nonatomic,assign)float realTime;

+(JL_SDM_Altitude*)responseData:(NSData *)value subMask:(NSData *)submask;

+(JL_SDM_Altitude*)requireRealTime:(BOOL)rt min:(BOOL)min Max:(BOOL)max;



@end

NS_ASSUME_NONNULL_END
