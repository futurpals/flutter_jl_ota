//
//  JLPersonInfoModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface JLPersonInfoModel : JLwSettingModel

@property(nonatomic,assign)uint16_t height;
@property(nonatomic,assign)uint16_t weight;
@property(nonatomic,strong)NSDate *birthDay;
@property(nonatomic,assign)uint8_t gender;

-(instancetype)initWith:(NSDate *)birthDay height:(uint16_t)h weight:(uint16_t)w gener:(uint8_t)gender;

-(instancetype)initWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
