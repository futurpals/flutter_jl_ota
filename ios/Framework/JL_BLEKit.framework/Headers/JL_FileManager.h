//
//  JL_FileManager.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/12/13.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JLModel_File.h>
#import <JL_BLEKit/JL_FunctionBaseManager.h>
#import <JL_BLEKit/JL_Tools.h>

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(UInt8, JL_FileOperationEnvironmentType) {
    JL_FileOperationEnvironmentTypeBigFileTransmission      = 0x00,
    JL_FileOperationEnvironmentTypeDeleteFile               = 0x01,
    JL_FileOperationEnvironmentTypeFormatting               = 0x02,
    JL_FileOperationEnvironmentTypeFatfsTransmission        = 0x03,
};
typedef NS_ENUM(UInt8, JL_DeleteFileLastType) {
    JL_DeleteFileLastTypeIsNotLast                  = 0x00,
    JL_DeleteFileLastTypeIsLast                     = 0x01,
};
typedef NS_ENUM(UInt8, JL_BrowseReason) {
    JL_BrowseReasonCommandEnd       = 0,
    JL_BrowseReasonFolderEnd        = 1,
    JL_BrowseReasonPlaySuccess      = 2,
    JL_BrowseReasonBusy             = 3,
    JL_BrowseReasonDataFail         = 4,
    JL_BrowseReasonReading          = 0x0f,
    JL_BrowseReasonUnknown,
};
typedef NS_ENUM(UInt8, JL_FileContentResult) {
    JL_FileContentResultStart       = 0x00,
    JL_FileContentResultReading     = 0x01,
    JL_FileContentResultEnd         = 0x02,
    JL_FileContentResultCancel      = 0x03,
    JL_FileContentResultFail        = 0x04,
    JL_FileContentResultNull        = 0x05,
    JL_FileContentResultDataError   = 0x06,
    JL_FileContentResultCrcFail     = 0x07,
};
typedef NS_ENUM(UInt8, JL_FileDataType) {
    JL_FileDataTypeDo               = 0,
    JL_FileDataTypeDone             = 1,
    JL_FileDataTypeDoing            = 2,
    JL_FileDataTypeCancel           = 3,
    JL_FileDataTypeError            = 4,
    JL_FileDataTypeUnknown,
};
typedef NS_ENUM(UInt8, JL_BigFileTransferCode) {
    JL_BigFileTransferCodeSuccess       = 0x00,
    JL_BigFileTransferCodeFail          = 0x01,
    JL_BigFileTransferCodeOutOfRange    = 0x02,
    JL_BigFileTransferCodeCrcFail       = 0x03,
    JL_BigFileTransferCodeOutOfMemory   = 0x04,
};
typedef NS_ENUM(UInt8, JL_BigFileResult) {
    JL_BigFileTransferStart         = 0x00,
    JL_BigFileTransferDownload      = 0x01,
    JL_BigFileTransferEnd           = 0x02,
    JL_BigFileTransferOutOfRange    = 0x03,
    JL_BigFileTransferFail          = 0x04,
    JL_BigFileCrcError              = 0x05,
    JL_BigFileOutOfMemory           = 0x06,
    JL_BigFileTransferCancel        = 0x07,
    JL_BigFileTransferNoResponse    = 0xF1,
};


typedef void(^JL_FILE_BK)(NSArray* __nullable array,JL_BrowseReason reason);
typedef void(^JL_FILE_CONTENT_BK)(JL_FileContentResult result, uint32_t size, NSData* __nullable data, float progress);
typedef void(^JL_FILE_DATA_BK)(NSData* __nullable data, NSString* __nullable path, uint16_t size, JL_FileDataType type);
typedef void(^JL_BIGFILE_BK)(NSArray* __nullable array);
typedef void(^JL_BIGFILE_RT)(JL_BigFileResult result, float progress);


@interface JL_FileManager : JL_FunctionBaseManager

@property(nonatomic,assign)NSInteger maxTimeout;

///Default：false
///Other: true
@property(nonatomic,assign)BOOL isOtherEncode;

/// default :NSUTF16LittleEndianStringEncoding
@property(nonatomic,assign)NSStringEncoding encodeType;

- (void)closeTimer;



/// - Parameters:
-(void)cmdBrowseModel:(JLModel_File*)model
               Number:(uint8_t)number
               Result:(JL_CMD_RESPOND __nullable)result;

-(void)cmdBrowseMonitorResult:(JL_FILE_BK __nullable)result;




-(BOOL)cmdDeleteFileModels:(NSArray*)array;

-(void)cmdDeleteFile:(JLModel_File*)model
             IsLast:(JL_DeleteFileLastType)last
             Result:(JL_CMD_RESPOND __nullable)result;

/// - Parameters:
-(void)cmdFileDeleteWithName:(NSString*)name Result:(JL_CMD_RESPOND __nullable)result;



-(void)cmdDeviceFormat:(NSString*)handle Result:(JL_CMD_RESPOND __nullable)result;

-(void)cmdCleanCacheType:(JL_CardType)type;



- (void)setCurrentFileHandleType:(JL_FileHandleType)currentFileHandleType;

- (JL_FileHandleType)getCurrentFileHandleType;

- (NSData *)currentDeviceHandleData;

-(void)cmdSetDeviceStorage:(NSData *)devHandle Result:(JL_CMD_RESPOND)result;



-(void)cmdFileDataMonitorResult:(JL_FILE_DATA_BK __nullable)result __attribute__((deprecated("This method is deprecated. Use newMethod cmdFileReadContentWithName:(NSString*)name Result:(JL_FILE_CONTENT_BK __nullable)result")));

-(void)cmdAllowFileData __attribute__((deprecated("This method is deprecated. Use newMethod cmdFileReadContentWithName:(NSString*)name Result:(JL_FILE_CONTENT_BK __nullable)result")));

-(void)cmdRejectFileData __attribute__((deprecated("This method is deprecated. Use newMethod cmdFileReadContentWithName:(NSString*)name Result:(JL_FILE_CONTENT_BK __nullable)result")));

-(void)cmdStopFileData __attribute__((deprecated("This method is deprecated. Use newMethod cmdFileReadContentCancel")));

/// - Parameters:
-(void)cmdFileReadContentWithName:(NSString*)name Result:(JL_FILE_CONTENT_BK __nullable)result;

/// - Parameters:
- (void)cmdFileReadContentWithFileClus:(uint32_t)fileClus Result:(JL_FILE_CONTENT_BK __nullable)result;

-(void)cmdFileReadContentCancel;



/// - Parameters:
-(void)cmdFileDataSize:(uint8_t)size
              SavePath:(NSString*)path __attribute__((deprecated("This method is deprecated. Use newMethod cmdBigFileData:(NSString *)path WithFileName:(NSString *)fileName                                                                 Result:(JL_BIGFILE_RT __nullable)result")));


-(void)cmdPushFileData:(NSData*)data __attribute__((deprecated("This method is deprecated. Use newMethod cmdBigFileData:(NSString *)path WithFileName:(NSString *)fileName                                                               Result:(JL_BIGFILE_RT __nullable)result")));


/// - Parameters:
-(void)cmdBigFileData:(NSString *)path WithFileName:(NSString *)fileName
               Result:(JL_BIGFILE_RT __nullable)result;

-(void)cmdStopBigFileData;

/// - Parameters:
///   - environment: 
-(void)cmdPreEnvironment:(JL_FileOperationEnvironmentType)environment Result:(JL_CMD_RESPOND __nullable)result;



@end

NS_ASSUME_NONNULL_END
