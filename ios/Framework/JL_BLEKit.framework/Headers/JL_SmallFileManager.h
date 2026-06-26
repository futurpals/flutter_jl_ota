//
//  JL_SmallFileManager.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/12/13.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <JL_BLEKit/JL_FunctionBaseManager.h>
#import <JL_BLEKit/JLModel_SmallFile.h>
#import <JL_BLEKit/JL_Tools.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_SmallFileOperate) {
    JL_SmallFileOperateFail        = 0x00,
    JL_SmallFileOperateDoing       = 0x01,
    JL_SmallFileOperateSuceess     = 0x02,
    JL_SmallFileOperateUnknown     = 0x03,
    JL_SmallFileOperateExcess      = 0x04,
    JL_SmallFileOperateCrcError    = 0x05,
    JL_SmallFileOperateTimeout     = 0x06,
};
typedef void(^JL_SMALLFILE_DEL)(JL_SmallFileOperate status);
typedef void(^JL_SMALLFILE_READ)(JL_SmallFileOperate status,
                                 float progress, NSData* __nullable data);
typedef void(^JL_SMALLFILE_NEW)(JL_SmallFileOperate status,
                                 float progress, uint16_t fileID);
typedef void(^JL_SMALLFILE_UPDATE)(JL_SmallFileOperate status,
                                 float progress);
typedef void(^JL_SMALLFILE_LIST)(NSArray <JLModel_SmallFile*>* __nullable array);
typedef void(^JL_SMALLFILE_RT)(uint8_t flag, uint16_t fileID,NSData* __nullable data);

@interface JL_SmallFileManager : JL_FunctionBaseManager

#pragma mark - Vendor SDK

-(void)cmdSmallFileQueryType:(JL_SmallFileType)type
                      Result:(JL_SMALLFILE_LIST __nullable)result;

#pragma mark - Vendor SDK

-(void)cmdSmallFileDelete:(JLModel_SmallFile*)file Result:(JL_SMALLFILE_DEL)result;

#pragma mark - Vendor SDK

-(void)cmdSmallFileRead:(JLModel_SmallFile*)file
                 Result:(JL_SMALLFILE_READ)result;

-(void)cmdSmallFileReadSync:(JLModel_SmallFile*)file
                     Result:(JL_SMALLFILE_READ)result;

#pragma mark - Vendor SDK

-(void)cmdSmallFileNew:(NSData*)data
                  Type:(JL_SmallFileType)type
                Result:(JL_SMALLFILE_NEW)result;

-(void)cmdSmallFileNewSync:(NSData*)data
                      Type:(JL_SmallFileType)type
                    Result:(JL_SMALLFILE_NEW)result;

#pragma mark - Vendor SDK

-(void)cmdSmallFileUpdate:(JLModel_SmallFile*)file
                     Data:(NSData*)data
                   Result:(JL_SMALLFILE_UPDATE)result;

-(void)cmdSmallFileUpdateSync:(JLModel_SmallFile*)file
                         Data:(NSData*)data
                       Result:(JL_SMALLFILE_UPDATE)result;

#pragma mark - Vendor SDK

-(void)cmdSmallFileReadType:(uint8_t)type
                     FileID:(uint16_t)fileId
                     Offset:(uint16_t)offset
                   FileSize:(uint16_t)fileSize
                       Flag:(uint8_t)flag
                     Result:(JL_SMALLFILE_RT __nullable)result;


-(void)cmdSmallFileNewType:(uint8_t)type
                    Offset:(uint16_t)offset
                  FileSize:(uint16_t)fileSize
                     Crc16:(uint16_t)crc16
                  FileData:(NSData*)data
                    Result:(JL_SMALLFILE_RT __nullable)result;

-(void)cmdSmallFileUpdateType:(uint8_t)type
                       FileID:(uint16_t)fileId
                       Offset:(uint16_t)offset
                     FileSize:(uint16_t)fileSize
                        Crc16:(uint16_t)crc16
                     FileData:(NSData*)data
                       Result:(JL_SMALLFILE_RT __nullable)result;

-(void)cmdSmallFileDeleteType:(uint8_t)type
                       FileID:(uint16_t)fileId
                       Result:(JL_SMALLFILE_RT __nullable)result;

-(void)closeTimer;
@end

NS_ASSUME_NONNULL_END
