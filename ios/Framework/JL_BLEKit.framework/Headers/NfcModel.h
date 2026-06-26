//
//  NfcModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/8/3.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


@interface NfcModel : NSObject

@property(nonatomic,assign)UInt16 idCard;

@property(nonatomic,strong)NSData *reserver;

@property(nonatomic,strong)NSData *devHandler;

@property(nonatomic,strong)NSDate *updateTime;

@property(nonatomic,strong)NSString *nfcFileName;

@property(nonatomic,strong)NSString *nickName;

@property(nonatomic,assign)UInt16 variableLength;

@property(nonatomic,strong)NSData   *crc;

@property(nonatomic,strong)NSData   *nfc_id;


+(NfcModel *)initMsgModel:(NSData *)data;

+(NSArray<NfcModel *> *)initMSGModels:(NSData *)basicData;

@end

NS_ASSUME_NONNULL_END





@interface NfcFileModel : NfcModel

@property(nonatomic,strong)NSData * _Nonnull nfcData;
@property(nonatomic,assign,readonly)UInt32  length;
+(NfcFileModel *_Nonnull)initFileModel:(NSData *_Nonnull)data;

@end




