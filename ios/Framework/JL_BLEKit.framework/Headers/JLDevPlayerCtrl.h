//
//  JLDevPlayerCtrl.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/9/25.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <JL_BLEKit/JL_BLEKit.h>

NS_ASSUME_NONNULL_BEGIN

@class JL_ManagerM;
@class JLDevPlayerCtrl;

@protocol JLDevPlayerCtrlDelegate<NSObject>

/// - Parameters:
-(void)jlDevPlayerCtrl:(JLDevPlayerCtrl *)ctrl playMode:(uint8_t)playMode;

/// - Parameters:
-(void)jlDevPlayerCtrl:(JLDevPlayerCtrl *)ctrl playStatus:(uint8_t)status currentCard:(uint8_t)card currentTime:(uint32_t)time tolalTime:(uint32_t)total;

/// - Parameters:
-(void)jlDevPlayerCtrl:(JLDevPlayerCtrl *)ctrl fileName:(NSString *)name currentClus:(uint32_t)clus;

@end


@interface JLDevPlayerCtrl : JLCmdBasic

@property(nonatomic,assign)uint8_t playStatus;

/// 0x00 : USB
/// 0x01 : SD_0
/// 0x02 : SD_1
/// 0x03 : FLASH
/// 0x04 : LineIn
/// 0x05 : FLASH2
@property(nonatomic,assign)uint8_t currentCard;

@property(nonatomic,assign)uint32_t currentTime;

@property(nonatomic,assign)uint32_t tolalTime;

@property(nonatomic,strong)NSString *fileName;

@property(nonatomic,assign)uint32_t currentClus;

@property (nonatomic,assign)uint8_t playMode;

@property(nonatomic,weak)id<JLDevPlayerCtrlDelegate> delegate;

/// - Parameters:
///    0x05：EQ
-(void)cmdPlayerCtrl:(uint8_t)cmd
              Second:(uint16_t)sec
             Manager:(JL_ManagerM *)manager
              Result:(JL_CMD_RESPOND __nullable)result;

@end

NS_ASSUME_NONNULL_END
