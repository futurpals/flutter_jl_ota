//
//  JLWearSync.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/26.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_RCSP.h"
#import "JLWatchEnum.h"
#import "JL_EntityM.h"
#import "JL_SDM_Header.h"
#import "JL_WatchSyncProtocol.h"


NS_ASSUME_NONNULL_BEGIN

@interface JLWearSync : NSObject

+(instancetype)share;

-(void)addProtocol:(id<JLWearSyncProtocol>)delegate;

-(void)removeProtocol:(id<JLWearSyncProtocol>)delegate;

///-(void)jlWearSyncSportInfo:(JLWearSyncInfoModel *_Nonnull)model;
-(void)w_requireSportInfoWith:(JL_EntityM *)entity Block:(JL_CB_SyncSportInfo _Nullable)block;

-(void)w_SportStart:(uint8_t)type With:(JL_EntityM *)entity Block:(JL_CB_Status _Nullable)block;

///-(void)jlWearSyncStopMotion:(JLWearSyncFinishModel *_Nonnull)model With:(JL_EntityM *_Nonnull)entity;
-(void)w_SportFinishWith:(JL_EntityM*)entity;

-(void)w_SportPauseWith:(JL_EntityM*)entity Block:(JL_CB_Status _Nullable)block;

-(void)w_SportContinueWith:(JL_EntityM*)entity Block:(JL_CB_Status _Nullable)block;

-(void)w_requireRealTimeSportInfoWith:(JL_EntityM *)entity;

-(void)pr_setTimeInterval:(UInt16)interval With:(JL_EntityM *)entity;

@end

NS_ASSUME_NONNULL_END
