//
//  JLWearSyncCustom.h
//  JL_BLEKit
//
//  Created by EzioChan on 2022/4/13.
//  Copyright © 2022 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_RCSP.h"
#import "JL_EntityM.h"
#import "JL_SDM_Header.h"



NS_ASSUME_NONNULL_BEGIN

@protocol JLWearSyncCustomPtl <NSObject>

-(void)jlWearSyncSportInfo:(JLWearSyncDataModel *_Nonnull)model With:(JL_EntityM *_Nonnull)entity;

-(void)jlWearSyncStopMotion:(JLWearSyncFinishDataModel *_Nonnull)model With:(JL_EntityM *_Nonnull)entity;

-(void)jlWearSyncStartMotionWith:(JL_EntityM *_Nonnull)entity;

-(void)jlWearSyncStatusPauseWith:(JL_EntityM *_Nonnull)entity;

-(void)jlWearSyncStatusContiuneWith:(JL_EntityM *_Nonnull)entity;

-(void)jlWearSyncRealTimeData:(JLWearSyncRealTimeData *_Nonnull)model With:(JL_EntityM *_Nonnull)entity;

@end



@interface JLWearSyncCustom : NSObject

@property(nonatomic,weak)id<JLWearSyncCustomPtl> delegate;

///-(void)jlWearSyncSportInfo:(JLWearSyncInfoModel *_Nonnull)model;
-(void)w_requireSportInfoWith:(JL_EntityM *)entity Block:(JL_CB_SyncSportDataInfo _Nullable)block;

-(void)w_SportStart:(UInt8)type With:(JL_EntityM *)entity Block:(JL_CB_Status _Nullable)block;

///-(void)jlWearSyncStopMotion:(JLWearSyncFinishModel *_Nonnull)model With:(JL_EntityM *_Nonnull)entity;
-(void)w_SportFinishWith:(JL_EntityM*)entity;

-(void)w_SportPauseWith:(JL_EntityM*)entity Block:(JL_CB_Status _Nullable)block;

-(void)w_SportContinueWith:(JL_EntityM*)entity Block:(JL_CB_Status _Nullable)block;

-(void)w_requireRealTimeSportInfoWith:(JL_EntityM *)entity;

-(void)pr_setTimeInterval:(UInt16)interval With:(JL_EntityM *)entity;


@end

NS_ASSUME_NONNULL_END
