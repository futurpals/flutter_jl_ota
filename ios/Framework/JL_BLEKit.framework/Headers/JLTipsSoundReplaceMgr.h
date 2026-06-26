//
//  JLTipsSoundReplay.h
//  JL_BLEKit
//
//  Created by EzioChan on 2025/5/14.
//  Copyright © 2025 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_BLEKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef void(^JLTipsVoiceBlock)(JL_CMDStatus,NSData *_Nullable info);

@interface JLTipsSoundReplaceMgr : NSObject

+(instancetype)share;

-(BOOL)isReplacing;

/// - Parameters:
-(void)isSupportTipsVoiceReplace:(JL_ManagerM *)manager result:(JLConfigTwsRsp)result;

/// - Parameters:
-(void)voicesReplaceGetVoiceInfo:(JL_ManagerM *)manager Result:(JLTipsVoiceBlock)result;

/// - Parameters:
-(void)voicesReplacePushDataRequest:(JL_ManagerM *)mgr DevHandle:(NSData *)devhandle TonePath:(NSString *)path IsReborn:(BOOL)isReborn Result:(JL_BIGFILE_RT __nullable)result;

@end

NS_ASSUME_NONNULL_END
