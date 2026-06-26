//
//  TaskChain.h
//  JL_BLEKit
//
//  Created by EzioChan on 2025/3/20.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/*
 JLTaskChain *chain = [[JLTaskChain alloc] init];

 [chain addTask:^(id input, void (^completion)(id, NSError *)) {
     NSLog(@"1");
     dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
         [NSThread sleepForTimeInterval:2];
         NSLog(@"1");
         completion(@"1", nil);
     });
 }];

 [chain addTask:^(id input, void (^completion)(id, NSError *)) {
     NSLog(@"2：%@", input);
     dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
         [NSThread sleepForTimeInterval:2];
         NSLog(@"2");
         NSError *error = [NSError errorWithDomain:@"com.example.task" code:100 userInfo:@{NSLocalizedDescriptionKey:@"2"}];
         completion(nil, error);
     });
 }];

 [chain addTask:^(id input, void (^completion)(id, NSError *)) {
     NSLog(@"3：%@", input);
     dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
         [NSThread sleepForTimeInterval:2];
         NSLog(@"3");
         completion(@"3", nil);
     });
 }];

 [chain runWithInitialInput:nil completion:^(id result, NSError *error) {
     if (error) {
         NSLog(@"，：%@", error.localizedDescription);
     } else {
         NSLog(@"，：%@", result);
     }
 }];
*/


/******************************************************************************************************************************
NSArray *taskList = @[@"A", @"B", @"C"];

 JLTaskChain *chain = [[JLTaskChain alloc] init];

for (NSString *taskName in taskList) {
    [chain addTask:^(id input, void (^completion)(id, NSError *)) {
        NSLog(@"：%@", taskName);
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            [NSThread sleepForTimeInterval:1.0];
            if ([taskName isEqualToString:@"B"]) {
                NSError *error = [NSError errorWithDomain:@"com.example.task" code:100 userInfo:@{NSLocalizedDescriptionKey:@"B "}];
                NSLog(@" %@ ", taskName);
                completion(nil, error);
            } else {
                NSString *result = [NSString stringWithFormat:@"%@ ", taskName];
                NSLog(@"：%@", result);
                completion(result, nil);
            }
        });
    }];
}

[chain runWithInitialInput:nil completion:^(id result, NSError *error) {
    if (error) {
        NSLog(@"，：%@", error.localizedDescription);
    } else {
        NSLog(@"，：%@", result);
    }
}];
 */


@interface JLTaskChain : NSObject

@property (nonatomic, strong) NSMutableArray *taskBlocks;
+ (void)cancelAllTasks;
- (void)addTask:(void (^)(id input, void (^completion)(id _Nullable output, NSError *_Nullable error)))task;
- (void)runWithInitialInput:(id _Nullable)input completion:(void (^ _Nullable)(id _Nullable result, NSError *_Nullable error))completion;
- (void)cancel;
@end

NS_ASSUME_NONNULL_END
