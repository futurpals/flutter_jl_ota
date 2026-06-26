//
//  JL_SDM_Stress.h
//  Test
//
//  Created by EzioChan on 2021/4/7.
//  Copyright © 2021 Zhuhai Jieli Technology Co.,Ltd. All rights reserved.
//

#import "JLSportDataModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface JL_SDM_Stress : JLSportDataModel

@property(nonatomic,assign)int stress;

+(JL_SDM_Stress*)responseData:(NSData *)value subMask:(NSData *)submask;

+(JL_SDM_Stress*)require;

@end

NS_ASSUME_NONNULL_END
