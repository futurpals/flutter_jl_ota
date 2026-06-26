//
//  JLSpdifPCManager.h
//  JL_BLEKit
//
//  Created by EzioChan on 2024/10/15.
//  Copyright © 2024 www.zh-jieli.com. All rights reserved.
//

#import <JL_BLEKit/ECOneToMorePtl.h>
#import <JL_BLEKit/JLModelSpdif.h>
#import <JL_BLEKit/JLModelPCServer.h>
#import <JL_BLEKit/JL_ManagerM.h>

NS_ASSUME_NONNULL_BEGIN

@protocol JLSpdifPCProtocol <NSObject>

-(void)updateSpdifModel:(JLModelSpdif *)spdifModel;

/// - Parameter pcServerModel: PC Server
-(void)updatePcServerModel:(JLModelPCServer *)pcServerModel;

@end

@interface JLSpdifPCManager : ECOneToMorePtl

@property(nonatomic,strong)JLModelSpdif *spdifModel;

@property(nonatomic,strong)JLModelPCServer *pcServerModel;


-(void)getSpdifStatus:(JL_ManagerM *)manager callBack:(JL_CMD_RESPOND)callBack;

-(void)getPcServerStatus:(JL_ManagerM *)manager callBack: (JL_CMD_RESPOND)callBack;

-(void)setSpdifPlayStatus:(BOOL)status Manager:(JL_ManagerM *)manager callBack:(JL_CMD_RESPOND)callBack;

-(void)setSpdifAction:(JLSpdifAudioType)type Manager:(JL_ManagerM *)manager callBack:(JL_CMD_RESPOND)callBack;

-(void)setPcServerPlayStatus:(BOOL)status Manager:(JL_ManagerM *)manager callBack:(JL_CMD_RESPOND)callBack;

-(void)setPcServerAction:(JLPcServerOpType)type Manager:(JL_ManagerM *)manager callBack:(JL_CMD_RESPOND)callBack;

@end

NS_ASSUME_NONNULL_END
