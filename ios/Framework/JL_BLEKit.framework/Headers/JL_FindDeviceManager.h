//
//  JL_FindDeviceManager.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/12/17.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_FunctionBaseManager.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JL_Tools.h>

NS_ASSUME_NONNULL_BEGIN


@interface JLFindDeviceOperation : NSObject

@property(nonatomic,assign)uint8_t playWay;

@property(nonatomic,assign)uint16_t timeout;

@property(nonatomic,assign)uint8_t sound;


@end


@interface JLFindPhoneModel : NSObject

@property(nonatomic,assign)uint8_t sound;

@property(nonatomic,assign)uint16_t timeout;

@end



@protocol JL_FindDeviceDelegate <NSObject>


/// - Parameter model:JLFindPhoneModel
-(void)findDeviceStartFindMyPhone:(JLFindPhoneModel *)model;

/// - Parameter model: JLFindDeviceOperation
-(void)findDeviceCheckStatus:(JLFindDeviceOperation *)model;

@end

@interface JL_FindDeviceManager : JL_FunctionBaseManager

#pragma mark - Vendor SDK
extern NSString *kJL_MANAGER_FIND_PHONE;

extern NSString *kJL_MANAGER_FIND_DEVICE;

extern NSString *kJL_MANAGER_FIND_DEVICE_STATUS;


typedef void(^JL_FIND_DEVICE_CHECK_RESPOND)(JL_CMDStatus status, JLFindDeviceOperation * _Nullable model);

@property(nonatomic,weak)id<JL_FindDeviceDelegate> delegate;

// opDict：{@"way":@"0",@"player":@"0"}
-(void)cmdFindDevice:(BOOL)isVoice
             timeOut:(uint16_t)timeout
          findIphone:(BOOL)isIphone
           Operation:( NSDictionary * _Nullable )opDict __attribute__((deprecated ( "This method will be replaced with subcommands cmdFindDeviceWith and proxy etc.")));



-(void)cmdFindDeviceWith:(JLFindDeviceOperation *)operation;



-(void)cmdFindDeviceCheckStatus:(JL_FIND_DEVICE_CHECK_RESPOND _Nullable)result;


@end

NS_ASSUME_NONNULL_END
