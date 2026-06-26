//
//  JLAiManager.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/8/9.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_TypeEnum.h>

NS_ASSUME_NONNULL_BEGIN

//MARK: - JLOpenPlatformInfo
@interface JLOpenPlatformInfo : NSObject
@property(nonatomic,assign)uint8_t version;
@property(nonatomic,copy)NSString *appID;
/// app key
@property(nonatomic,copy)NSString *appKey;
@property(nonatomic,copy)NSString *appSecret;
@property(nonatomic,copy)NSData *basicData;

-(instancetype)initData:(NSData *)data;

@end

@interface JLOpenPlatformMessage : NSObject
@property(nonatomic,assign)uint8_t version;
@property(nonatomic,copy)NSArray <JLOpenPlatformInfo *>* infoArray;

-(instancetype)initData:(NSData *)dt;

@end

@interface JLDialSize : NSObject

/// width
@property(nonatomic,assign) uint16_t width;

/// height
@property(nonatomic,assign) uint16_t height;

/// - Parameters:
///   - width: width
///   - height: height
+(JLDialSize *)makeSize:(uint16_t)width Height:(uint16_t)height;

@end

//MARK: - JLAiManager
@class JL_ManagerM;
@class JLAiManager;

@protocol JLAIManagerDelegate <NSObject>

/// - Parameter mgr: JLAiManager
-(void)jlaiUpdateStatus:(JLAiManager *)mgr;

@optional
/// - Parameters:
///   - infoArray: [JLOpenPlatformInfo]
-(void)jlaiUpdateDevAiOpenPlatforms:(JLAiManager *)mgr Info:(JLOpenPlatformMessage *)info;


@end

typedef void(^JLOpenPFBlock)(JLOpenPlatformMessage *message,JL_CMDStatus result);

///
@interface JLAiManager : NSObject

@property(assign,nonatomic)uint8_t version;

@property(assign,nonatomic)uint8_t status;

@property(weak,nonatomic)id<JLAIManagerDelegate> delegate;

///- Parameters:
-(void)getStatus:(JL_ManagerM *)manager;

/// - Parameters:
-(void)setToDevice:(JL_ManagerM *)manager result:(JL_CMD_RESPOND _Nullable)result;


/// - Parameters:
-(void)getOpenPlatformInfo:(JL_ManagerM *)manager result:(JLOpenPFBlock _Nullable)result;

@end

NS_ASSUME_NONNULL_END
