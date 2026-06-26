//
//  JL_SDM_MoveSteps.h
//  Test
//
//  Created by EzioChan on 2021/4/6.
//  Copyright © 2021 Zhuhai Jieli Technology Co.,Ltd. All rights reserved.
//

#import "JLSportDataModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface JL_SDM_MoveSteps : JLSportDataModel
@property(nonatomic,assign)NSInteger rtStep;

@property(nonatomic,assign)NSInteger calories;

@property(nonatomic,assign)NSInteger distance;
+(JL_SDM_MoveSteps*)responseData:(NSData *)value subMask:(NSData *)submask;

+(JL_SDM_MoveSteps*)require:(BOOL)rst distance:(BOOL)dts calories:(BOOL)ca;


@end

NS_ASSUME_NONNULL_END
