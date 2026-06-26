//
//  JLSensorFuncModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"
#import "JLWatchEnum.h"

NS_ASSUME_NONNULL_BEGIN


@interface JLSensorFuncModel : JLwSettingModel

@property(nonatomic,assign)BOOL pedometerStatus;
@property(nonatomic,assign)BOOL pedometerRecordStatus;
@property(nonatomic,assign)BOOL heartRateStatus;
@property(nonatomic,assign)BOOL heartRateRecordStatus;
@property(nonatomic,assign)BOOL bloodOxygenStatus;
@property(nonatomic,assign)BOOL bloodOxygenRecordStatus;
@property(nonatomic,assign)BOOL AltitudeAirPressureStatus;
@property(nonatomic,assign)BOOL AltitudeAirPressureRecordStatus;


-(void)setFuncBy:(JL_SENSOR_FUNC_SWITCH)status;

-(instancetype)initWhthFuncByte:(JL_SENSOR_FUNC_SWITCH)funcByte;

-(instancetype)initWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
