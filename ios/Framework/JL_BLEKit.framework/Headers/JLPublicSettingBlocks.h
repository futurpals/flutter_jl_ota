//
//  JLPublicSettingBlocks.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/12/1.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_TypeEnum.h>

NS_ASSUME_NONNULL_BEGIN

#define PUBLIC_SCREEN_LIGHT             0x0001
#define PUBLIC_FLASH_LIGHT              0x0002
#define PUBLIC_DEVICE_BIND_STATUS       0x0003
#define PUBLIC_FUNC_SOURCE              0x0004
#define PUBLIC_FUNC_4G                  0x0005
#define PUBLIC_TIPS_VOICE               0x0006
#define PUBLIC_SDK_INFO                 0x0008

@class JLPublicBindDeviceModel;
@class JLPublicSourceInfoModel;
@class JLPublic4GModel;
@class JLPublicSDKInfoModel;

typedef void(^JLPSScreenLightCbk)(JL_CMDStatus status,uint8_t value);

typedef void(^JLPSFlashLightCbk)(JL_CMDStatus status,BOOL isOn);

typedef void(^JLPSBindStatusCbk)(JL_CMDStatus status,JLPublicBindDeviceModel *_Nullable model);
typedef void (^JLPSSourceInfoCbk)(JL_CMDStatus status,JLPublicSourceInfoModel *_Nullable model);

typedef void (^JLPSSource4GCbk)(JL_CMDStatus status,JLPublic4GModel *_Nullable model);

typedef void(^JLPSTipsVoiceRpCbk)(JL_CMDStatus status,uint8_t op);

typedef void(^JLPSSDKInfoCbk)(JL_CMDStatus status,JLPublicSDKInfoModel *_Nullable model);

@interface JLPublicBindDeviceModel : NSObject

@property(nonatomic,assign)uint8_t type;

@property(nonatomic,copy)NSString *edrAddr;

@property(nonatomic,copy)NSString *bleAddr;

@property(nonatomic,assign)uint8_t status;

/// 0 BLE
/// 1 SPP 
@property(nonatomic,assign)uint8_t way;

+(JLPublicBindDeviceModel *)initData:(NSData *)data;
@end

@interface JLPublicSourceInfoModel:NSObject

@property(nonatomic,assign)uint8_t type;

@property(nonatomic,copy)NSData *fileHandle;

@property(nonatomic,assign)uint32_t cluster;

@property(nonatomic,assign)uint16_t crc;

@property(nonatomic,strong)NSString *filePath;

-(NSData *)beData;

+(JLPublicSourceInfoModel *)initData:(NSData *)data;

@end


@interface JLPublic4GModel:NSObject

@property(nonatomic,assign)uint8_t vendor;

@property(nonatomic,assign)uint8_t updateStatus;

@property(nonatomic,copy)NSString *version;

@property(nonatomic,assign)NSTimeInterval startOtaMaxTimeout;

@property(nonatomic,assign)NSTimeInterval endOtaMaxTimeout;


+(JLPublic4GModel *)initData:(NSData *)data;

@end

@interface JLPublicTipsVoiceRpInfo : NSObject

/// JLModelCardInfo    *cardInfo;
@property(nonatomic,copy)NSData *devHandle;

@property(nonatomic,strong)NSString *fileName;

@property(nonatomic,copy)NSData *sendData;

-(NSData *)createData;

@end


@interface JLPublicSDKInfoModel : NSObject

@property(nonatomic,assign)uint16_t projectId;

@property(nonatomic,assign)uint16_t productId;

/// 0x0001 AC701N
/// 0x0002 AC707N
@property(nonatomic,assign)uint16_t chipId;

@property(nonatomic,assign)BOOL isSupportGif;

+ (JLPublicSDKInfoModel *)initData:(NSData *)data;

@end
NS_ASSUME_NONNULL_END
