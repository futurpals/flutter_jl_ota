//
//  JLSportDataModel.h
//  Test
//
//  Created by EzioChan on 2021/4/6.
//  Copyright © 2021 Zhuhai Jieli Technology Co.,Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface JLSportDataModel : NSObject

@property(nonatomic,strong)NSString *dev_uuid;

@property(nonatomic,strong)NSData *rqData;

@property(nonatomic,assign)uint32_t funcMask;


@end

NS_ASSUME_NONNULL_END
