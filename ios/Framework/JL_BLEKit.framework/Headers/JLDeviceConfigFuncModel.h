//
//  JLDeviceConfigFuncModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2022/10/31.
//  Copyright © 2022 www.zh-jieli.com. All rights reserved.
//

#import "ECOneToMorePtl.h"

NS_ASSUME_NONNULL_BEGIN


@interface JLDeviceBasicFuncModel : NSObject

@property(nonatomic,assign)BOOL spOTA;

@property(nonatomic,assign)BOOL spSourceUpdate;

@property(nonatomic,assign)BOOL spDialOperation;

@property(nonatomic,assign)BOOL spDialSwitch;

@property(nonatomic,assign)BOOL spDialPreview;


-(instancetype)init:(NSData *)data;

@end

@interface JLDeviceSystemFuncModel : NSObject

@property(nonatomic,assign)BOOL spScreenSetting;
@property(nonatomic,assign)BOOL spVibrationIntensity;
@property(nonatomic,assign)BOOL spDoNotDisturb;
@property(nonatomic,assign)BOOL spExerciseSettings;
@property(nonatomic,assign)BOOL spDisconnectReminder;

-(instancetype)init:(NSData *)data;

@end

@interface JLDeviceExportFuncModel : NSObject
@property(nonatomic,assign)BOOL spTopContacts;
@property(nonatomic,assign)BOOL spMusicFileBrows;
@property(nonatomic,assign)BOOL spMusicFileOp;
@property(nonatomic,assign)BOOL spAlarmSettings;
@property(nonatomic,assign)BOOL spSyncInfo;
@property(nonatomic,assign)BOOL spSyncWeather;
@property(nonatomic,assign)BOOL spFindPhoneOrDevice;
@property(nonatomic,assign)BOOL spAiCloud;
@property(nonatomic,assign)BOOL spAiDial;
@property(nonatomic,assign)BOOL spOpenInfo;
@property(nonatomic,assign)BOOL sp4GModel;

@property(nonatomic,assign)BOOL spDialInfoExtend;

-(instancetype)init:(NSData *)data;

@end


@interface JLHealthFuncComprehensive : NSObject

@property(nonatomic,assign)BOOL spHealthMonitor;
@property(nonatomic,assign)BOOL spPersonInfo;
@property(nonatomic,assign)BOOL spSleepMonitor;
@property(nonatomic,assign)BOOL spSportHeartRateRemind;
@property(nonatomic,assign)BOOL spSedentaryRemind;
@property(nonatomic,assign)BOOL spStressDetection;
@property(nonatomic,assign)BOOL spFallDetection;
@property(nonatomic,assign)BOOL spSensorSetup;

-(instancetype)init:(NSData *)data;

@end

@interface JLHealthFuncSportModel : NSObject
@property(nonatomic,assign)BOOL spRecord;
@property(nonatomic,assign)BOOL spStatistics;
@property(nonatomic,assign)BOOL spOutdoor;
@property(nonatomic,assign)BOOL spIndoor;

-(instancetype)init:(NSData *)data;
@end

@interface JLHealthFuncGSensorModel : NSObject
@property(nonatomic,assign)BOOL spExist;
@property(nonatomic,assign)BOOL spStep;

-(instancetype)init:(NSData *)data;

@end


@interface JLHealthFuncHeartRateModel : NSObject
@property(nonatomic,assign)BOOL spExist;
@property(nonatomic,assign)BOOL spSerialTest;

-(instancetype)init:(NSData *)data;

@end

@interface JLHealthFuncBloodOxygenModel : NSObject
@property(nonatomic,assign)BOOL spExist;

-(instancetype)init:(NSData *)data;

@end


@interface JLHealthFuncAltitudeModel : NSObject
@property(nonatomic,assign)BOOL spExist;

-(instancetype)init:(NSData *)data;

@end

@interface JLHealthFuncGPSModel : NSObject
@property(nonatomic,assign)BOOL spExist;

-(instancetype)init:(NSData *)data;

@end



@interface JLDeviceHealthFuncModel : NSObject

@property(nonatomic,strong)JLHealthFuncComprehensive *spComprehensive;
@property(nonatomic,strong)JLHealthFuncSportModel *spSportModel;
@property(nonatomic,strong)JLHealthFuncGSensorModel *spGSensor;
@property(nonatomic,strong)JLHealthFuncHeartRateModel *spHeartRate;
@property(nonatomic,strong)JLHealthFuncBloodOxygenModel *spBloodOxygen;
@property(nonatomic,strong)JLHealthFuncAltitudeModel *spAltitude;
@property(nonatomic,strong)JLHealthFuncGPSModel *spGPS;

-(instancetype)init:(NSData *)data;

@end


@interface JLDeviceConfigBasic:NSObject
@property(nonatomic,assign)int deviceType;
@property(nonatomic,assign)int version;

@property(nonatomic,copy)NSData *basicData;

@property(nonatomic,strong)NSString  * _Nullable mbleIdentifyStr;

-(instancetype)init:(NSData *)data;

@end


@interface JLDeviceConfigModel:JLDeviceConfigBasic
@property(nonatomic,strong)JLDeviceBasicFuncModel *basicFunc;
@property(nonatomic,strong)JLDeviceSystemFuncModel *systemFunc;
@property(nonatomic,strong)JLDeviceExportFuncModel * exportFunc;
@property(nonatomic,strong)JLDeviceHealthFuncModel *healthFunc;

@end

NS_ASSUME_NONNULL_END
