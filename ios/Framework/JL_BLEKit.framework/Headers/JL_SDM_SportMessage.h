//
//  JL_SDM_SportMessage.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/4/8.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLSportDataModel.h"
#import "JLWatchEnum.h"
NS_ASSUME_NONNULL_BEGIN

@interface JL_SDM_SportMessage : JLSportDataModel

@property(nonatomic,assign)JL_SportPattern sportPattern;
@property(nonatomic,assign)int               distance;
@property(nonatomic,strong)NSDate            *startTime;
@property(nonatomic,strong)NSDate            *endTime;
@property(nonatomic,assign)int               xkcal;
@property(nonatomic,assign)int               speed;


/// @param value subData
/// @param submask submask
+(JL_SDM_SportMessage *)responseData:(NSData *)value subMask:(NSData *)submask;

+(JL_SDM_SportMessage *)requireModel:(BOOL)m distance:(BOOL)d start:(BOOL)st end:(BOOL)et kcal:(BOOL)kcal speed:(BOOL)sp;

+(JL_SDM_SportMessage *)requireAll;



@end

NS_ASSUME_NONNULL_END
