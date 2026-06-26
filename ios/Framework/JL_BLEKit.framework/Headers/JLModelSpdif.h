//
//  JLModelSpdif.h
//  JL_BLEKit
//
//  Created by EzioChan on 2024/10/15.
//  Copyright © 2024 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, JLSpdifAudioType) {
    /// HDMI
    JLSpdifAudioTypeHDMI = 0x00,
    /// 光纤 Fiber Optics
    JLSpdifAudioTypeFO = 0x01,
    /// 同轴
    JLSpdifAudioTypeCoaxial = 0x02,
};

@interface JLModelSpdif : NSObject

/// 是否正在播放
@property(nonatomic,assign)BOOL playStatus;

/// 音源
@property(nonatomic,assign)JLSpdifAudioType audioType;

-(instancetype)initParseData:(NSData *)data;

/// 更新数据
/// - Parameter data: 数据
-(void)updateParseData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
