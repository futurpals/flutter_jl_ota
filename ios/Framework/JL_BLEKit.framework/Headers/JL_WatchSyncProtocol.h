//
//  JL_WatchSyncProtocol.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/27.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "JL_SDM_Header.h"
#import "JL_EntityM.h"

#ifndef JL_WatchSyncProtocol_h
#define JL_WatchSyncProtocol_h

@protocol JLWearSyncProtocol <NSObject>

@optional
-(void)jlWearSyncSportInfo:(JLWearSyncInfoModel *_Nonnull)model With:(JL_EntityM *_Nonnull)entity;

-(void)jlWearSyncStopMotion:(JLWearSyncFinishModel *_Nonnull)model With:(JL_EntityM *_Nonnull)entity;

-(void)jlWearSyncStartMotionWith:(JL_EntityM *_Nonnull)entity;

-(void)jlWearSyncStatusPauseWith:(JL_EntityM *_Nonnull)entity;

-(void)jlWearSyncStatusContiuneWith:(JL_EntityM *_Nonnull)entity;

-(void)jlWearSyncRealTimeData:(JLWearSyncRealTimeModel *_Nonnull)model With:(JL_EntityM *_Nonnull)entity;

@end

#endif /* JL_WatchSyncProtocol_h */
