//
//  JLAutoConfigAnc.h
//  JL_BLEKit
//
//  Created by EzioChan on 2022/10/28.
//  Copyright © 2022 www.zh-jieli.com. All rights reserved.
//


#import "ECOneToMorePtl.h"

NS_ASSUME_NONNULL_BEGIN

@class JL_ManagerM;

typedef void(^AutoConfigResult)(BOOL status);

@protocol JLAutoConfigAncPtl <NSObject>


-(void)autoConfigDidConfiging;
-(void)autoConfigDidFailed;
-(void)autoConfigDidSucceed;
-(void)autoConfigDidClose;

@end


@interface JLAutoConfigAnc : ECOneToMorePtl

@property (assign,nonatomic)BOOL status;

/**
 interface testView : UIView<JLAutoConfigAncPtl>
 
 @end
 
 -(void)initData{
    JLAutoConfigAnc *anc = [[JLAutoConfigAnc alloc] init];
    [anc addDelegate:self];
 }
 
 -(void)autoConfigDidFailed{
 }
 -(void)autoConfigDidSucceed{
 }
 -(void)autoConfigDidClose{
 }
*/
/// - Parameter manager: manager
-(void)atAncStartAutoConfigWithManager:(JL_ManagerM*)manager;


/// - Parameter manager: manager
-(void)atAncOpenAutoConfigResult:(JL_CMD_RESPOND)result Manager:(JL_ManagerM*)manager;

/// - Parameter manager: manager
-(void)atAncCloseAutoConfigResult:(JL_CMD_RESPOND)result Manager:(JL_ManagerM*)manager;

/// - Parameter manager: manager
-(void)atAncGetAutoConfigResult:(AutoConfigResult)result Manager:(JL_ManagerM*)manager;

          
@end
          

NS_ASSUME_NONNULL_END
