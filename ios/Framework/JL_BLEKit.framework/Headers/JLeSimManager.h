//
//  JLeSimManager.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/12/4.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class JL_ManagerM;

@protocol JLEsimFinishDelegate <NSObject>

/// - Parameters:
-(void)jlEsimDidGetData:(uint8_t)version ESimData:(NSData *)data;

@end

typedef void(^JLESimFinishBlock)(NSError * _Nullable err);

@interface JLeSimManager : NSObject

@property(nonatomic,assign)id<JLEsimFinishDelegate> delegate;

/// - Parameters:
-(void)sendToDev:(JL_ManagerM *)mgr Data:(NSData *)data Result:(JLESimFinishBlock)block;

@end

NS_ASSUME_NONNULL_END
