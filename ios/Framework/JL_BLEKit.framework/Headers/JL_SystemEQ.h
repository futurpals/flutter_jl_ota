//
//  JL_SystemEQ.h
//  JL_BLEKit
//
//  Created by Jieli Technology on 2021/12/20.
//  Modify by EzioChan on 2023/09/22
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_FunctionBaseManager.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JL_Tools.h>


NS_ASSUME_NONNULL_BEGIN
@class JL_SystemEQ;
typedef void(^JLSystemEQResult)(JL_CMDStatus status,JL_SystemEQ * _Nullable model);

@interface JL_SystemEQ : JL_FunctionBaseManager

@property (assign,nonatomic) JL_EQMode eqMode;

@property (assign,nonatomic) JL_EQType eqType;

@property (strong,  nonatomic) NSArray *eqArray;

@property (strong,  nonatomic) NSArray *eqCustomArray;

@property (strong,  nonatomic) NSArray *eqFrequencyArray;

@property (strong,nonatomic) NSArray <JLModel_EQ*> *eqDefaultArray;


/// - Parameters:
-(void)cmdSetSystemEQ:(JL_EQMode)eqMode Params:(NSArray* __nullable)params;

-(void)cmdGetSystemEQ:(JLSystemEQResult)result;


@end

NS_ASSUME_NONNULL_END
