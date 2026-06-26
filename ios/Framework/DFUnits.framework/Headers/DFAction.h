//
//  DFAction.h
//  DFUnits
//
//  Created by DFung on 16/1/25.
//

#import <Foundation/Foundation.h>



typedef void(^Action)(void);

@interface DFAction : NSObject

/**
 *  @how:Execution block on Asynchronous thread.
 */
+(void)subTask:(Action)block;

/**
 *  @how:Execution block on Synchronization thread.
 */
+(void)mainTask:(Action)block;

/**
 *  @how:Execution some blocks asynchronousily and make a summary.
 *  @tasks  block Array
 *  @block  final block
 */
+(void)subTasks:(NSArray*)tasks Final:(Action)block;

/**
 *  @how:Execution block after a few seconds.
 */
+(void)delay:(double)sec Task:(Action)block;

/**
 *  @how:Execution block only once.
 */
+(void)taskOnce:(Action)block;

/**
 *  @how:Execution block N times.
 */
+(void)task:(Action)block Times:(int)times;

/**
 */
+(BOOL)setMinExecutionGap:(NSTimeInterval)gap;

/**
 */
+(NSTimer*)timingStart:(SEL)sel target:(id)objc Time:(NSTimeInterval)sec;

/**
 */
+(void)timingPause:(__weak NSTimer*)timer;
/**
 */
+(void)timingContinue:(__weak NSTimer*)timer;
/**
 */
+(void)timingStop:(__weak NSTimer*)timer;

@end
