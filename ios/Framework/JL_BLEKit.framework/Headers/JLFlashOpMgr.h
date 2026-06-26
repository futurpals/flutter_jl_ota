//
//  JLFlashOpMgr.h
//  JL_BLEKit
//
//  Created by EzioChan on 2025/3/14.
//  Copyright © 2025 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_BLEKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, FlashDialOperationType) {
    FlashDialOperationTypeReadCurrent = 0,
    FlashDialOperationTypeSet,
    FlashDialOperationTypeNotify,
    FlashDialOperationTypeGetExtraInfo,
    FlashDialOperationTypeActivateCustom,
    FlashDialOperationTypeGetBackground,
    FlashDialOperationTypeNoteBackground
};

@interface JLFlashOpMgr : NSObject

@property(nonatomic, assign)NSInteger timeOutMax;

/// - Parameters:
-(void)flashGetInfoMode:(JL_ManagerM *)managerM
                 Result:(void (^)(JLModel_Flash *_Nullable model, NSError *_Nullable error))result;
- (void)flashWriteData:(JL_ManagerM *)managerM
                Offset:(uint32_t)offset
                  Data:(NSData*)data
                isLast:(BOOL)isLast
                Result:(void (^)(BOOL success, NSError *error))result;
- (void)flashInsertFile:(JL_ManagerM *)managerM
               fileName:(NSString *)fileName
               fileSize:(uint32_t)fileSize
                 isLast:(BOOL)isLast
                 Result:(void (^)(BOOL, NSError * _Nullable error))result;
- (void)flashDialOperation:(JL_ManagerM *)managerM
                      type:(FlashDialOperationType)type
                  filePath:(nullable NSString *)filePath
                    result:(void (^)(BOOL success, NSData *_Nullable response, NSError *_Nullable error))result;
- (void)flashEraseData:(JL_ManagerM *)managerM
                Offset:(uint32_t)offset
           ClusterSize:(uint16_t)clusterSize
                Result:(void (^)(BOOL success, NSError *_Nullable error))result;

- (void)flashDeleteFile:(JL_ManagerM *)managerM
               FilePath:(nullable NSString *)filePath
                isStart:(BOOL)isStart
                 Result:(void (^)(BOOL success, NSError *_Nullable error))result;
- (void)flashWriteProtect:(JL_ManagerM *)managerM
                 isEnable:(BOOL)isEnable
                   Result:(void (^)(BOOL success, NSError *_Nullable error))result;
- (void)flashUpdateWatchFace:(JL_ManagerM *)managerM
                     isStart:(BOOL)isStart
                      Result:(void (^)(BOOL success, NSError *_Nullable error))result;
/// @param crc16 crc
- (void)flashCheckWriteSuccessV0:(JL_ManagerM *)managerM
                          crc16:(uint16_t)crc16
                         Result:(void (^)(BOOL success, NSError *_Nullable error))result;

/// @param crc16 crc
- (void)flashCheckWriteSuccessV1:(JL_ManagerM *)managerM
                           crc16:(uint16_t)crc16
                         isSplit:(BOOL)isSplit
                          Result:(void (^)(BOOL success, uint16_t leftSize, NSError *_Nullable error))result;
/// @param flag flag 0-2
- (void)flashSetUpgradeFlag:(JL_ManagerM *)managerM
                       flag:(uint8_t)flag
                     result:(void (^)(BOOL success, NSError *_Nullable error))result;
- (void)flashGetFileInfo:(JL_ManagerM *)managerM
                filePath:(NSString *)filePath
                  result:(void (^)(uint32_t size, uint16_t crc16, NSError *_Nullable error))result;

- (void)flashGetRemainingSpace:(JL_ManagerM *)managerM
                        result:(void (^)(uint32_t clusterLeftNum, NSError *_Nullable error))result;
- (void)flashRestoreSystem:(JL_ManagerM *)managerM
                    result:(void (^)(BOOL success, NSError *_Nullable error))result;

- (void)flashGetResourceSpace:(JL_ManagerM *)managerM
                       result:(void (^)(uint32_t resSpace, NSError *_Nullable error))result;

@end


NS_ASSUME_NONNULL_END
