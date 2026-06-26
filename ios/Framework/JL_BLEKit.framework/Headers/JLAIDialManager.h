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

/// - Parameters:
///   - manager: ai dial manager
-(void)aiDialManager:(JLAIDialManager *)manager didAiDialStatusChange:(uint8_t)status;

/// - Parameter manager: ai dial manager
-(void)aiDialdidStartCreateManager:(JLAIDialManager *)manager;

/// - Parameter manager: ai dial manager
-(void)aiDialdidRestartRecordManager:(JLAIDialManager *)manager;

/// - Parameter manager: ai dial manager
-(void)aiDialdidStartInstallManager:(JLAIDialManager *)manager;


/// - Parameter manager: ai dial manager
-(void)aiDialdidReCreateManager:(JLAIDialManager *)manager;

@end



/// ai dial manager
@interface JLAIDialManager : NSObject

@property (nonatomic, assign) BOOL isCreateing;

/// scale zoom size default 200*200
@property (nonatomic, strong) JLDialSize *scaleZoomSize;


@property (nonatomic, weak) id<JLAIDialManagerDelegate> delegate;


-(void)aiDialSetManager:(JL_ManagerM *)manager AiStyle:(NSString *)style Result:(JL_CMD_RESPOND)result;


-(void)aiDialSendThumbAiImageTo:(JL_ManagerM *)manager withPath:(NSString *)path Result:(JL_CMD_RESPOND)result;

@end

NS_ASSUME_NONNULL_END
