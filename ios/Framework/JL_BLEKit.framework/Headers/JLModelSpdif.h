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
    JLSpdifAudioTypeFO = 0x01,
    JLSpdifAudioTypeCoaxial = 0x02,
};

@interface JLModelSpdif : NSObject

@property(nonatomic,assign)BOOL playStatus;

@property(nonatomic,assign)JLSpdifAudioType audioType;

-(instancetype)initParseData:(NSData *)data;

-(void)updateParseData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
