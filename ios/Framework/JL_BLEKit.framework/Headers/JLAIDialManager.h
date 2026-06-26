//
//  JLAIDialManager.h
//  JL_BLEKit
//
//  Created by EzioChan on 2023/10/12.
//  Copyright © 2023 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JL_FileManager.h>
#import <JL_BLEKit/JLAiManager.h>

NS_ASSUME_NONNULL_BEGIN
@class JL_ManagerM;
@class JLAIDialManager;

@protocol JLAIDialManagerDelegate <NSObject>

/// 设备通知App AI表盘界面变化
/// - Parameters:
///   - manager: ai dial manager
///   - status:0x00: 退出AI表盘功能  0x01: 进入AI表盘功能
-(void)aiDialManager:(JLAIDialManager *)manager didAiDialStatusChange:(uint8_t)status;

/// 开始AI生成表盘
/// - Parameter manager: ai dial manager
-(void)aiDialdidStartCreateManager:(JLAIDialManager *)manager;

/// 重新录音
/// - Parameter manager: ai dial manager
-(void)aiDialdidRestartRecordManager:(JLAIDialManager *)manager;

/// AI表盘开始安装
/// - Parameter manager: ai dial manager
-(void)aiDialdidStartInstallManager:(JLAIDialManager *)manager;


/// 重新生成表盘
/// - Parameter manager: ai dial manager
-(void)aiDialdidReCreateManager:(JLAIDialManager *)manager;

@end



/// ai dial manager
@interface JLAIDialManager : NSObject

/// 进入/退出AI表盘
@property (nonatomic, assign) BOOL isCreateing;

/// 缩略图尺寸 默认 200*200
/// scale zoom size default 200*200
@property (nonatomic, strong) JLDialSize *scaleZoomSize;


/// 代理
@property (nonatomic, weak) id<JLAIDialManagerDelegate> delegate;


/// AI 表盘风格显示设置
/// - Parameter manager: 设备对象
/// - Parameter style: 风格类型
/// - Parameter result: 回调对象
-(void)aiDialSetManager:(JL_ManagerM *)manager AiStyle:(NSString *)style Result:(JL_CMD_RESPOND)result;


/// AI表盘告诉设备缩略图发送完毕
/// - Parameter manager: 设备对象
/// - Parameter path: 目标缩略图路径(设备端的位置）默认 "/VIE_THUMB"
/// - Parameter result: 回调对象
-(void)aiDialSendThumbAiImageTo:(JL_ManagerM *)manager withPath:(NSString *)path Result:(JL_CMD_RESPOND)result;

@end

NS_ASSUME_NONNULL_END
