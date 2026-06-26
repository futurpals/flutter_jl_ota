//
//  JL_NFC.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/8/2.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_TypeEnum.h"
#import "JL_ManagerM.h"

@class JL_RCSP;
@class JL_EntityM;
@class NfcFileModel;
@class NfcModel;
NS_ASSUME_NONNULL_BEGIN

typedef void(^NfcSyncResult)(UInt8 result,NSArray<NfcModel *> * _Nullable models);

typedef void(^NfcIDResult)(UInt16 result);

typedef void(^NfcDefaultResult)(BOOL result);

typedef void(^NfcBeginAddResult)(JL_EntityM *entity);


@interface JL_NFC : NSObject

-(instancetype)initWith:(JL_EntityM *)entity FileHandler:(JL_FileHandleType)handler;


-(void)w_syncNfcStart:(NfcSyncResult)result;


/**
 dict
 {
 @"timestamp" : NSDate()
 @"nickname" : @""
 }
 keyvalue，
 */
-(void)w_modifyNfc:(NSDictionary *)dict WithID:(UInt16)nfcID;


-(void)w_deleteNfc:(NfcModel *)model;


-(void)w_getNfcDefaultCard:(NfcIDResult)result;


-(void)w_setNfcDefalutCard:(NfcModel *)model result:(NfcDefaultResult)result;


-(void)w_NfcDefaultNotify:(NfcModel *)model;

/** examp.
 NfcFileModel *fm = [[NfcFileModel alloc] init];
//    fm.idCard = ...
//    fm.nfcFileName = ...
 JL_NFC *mgr = [[JL_NFC alloc] init];
 [mgr w_NfcAddCard:fm BeginAdd:^(JL_EntityM * _Nonnull entity) {
     [entity.mCmdManager cmdBigFileData:#path WithFileName:#fileName Result:^(JL_BigFileResult result, float progress) {
         if (result == JL_BigFileTransferEnd) {
             [mgr w_NfcEndAdd:fm];
         }
         
     }];
 }];
 */
-(void)w_NfcAddCard:(NfcFileModel *)model BeginAdd:(NfcBeginAddResult)result;

-(void)w_NfcEndAdd:(NfcFileModel *)model;

@end

NS_ASSUME_NONNULL_END
