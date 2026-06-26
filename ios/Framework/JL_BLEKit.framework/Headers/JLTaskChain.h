//
//  TaskChain.h
//  JL_BLEKit
//
//  Created by EzioChan on 2025/3/20.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/*
 // 创建 TaskChain 实例
 JLTaskChain *chain = [[JLTaskChain alloc] init];

 // 添加第一个任务：模拟耗时操作返回结果
 [chain addTask:^(id input, void (^completion)(id, NSError *)) {
     NSLog(@"任务1开始执行");
     dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
         [NSThread sleepForTimeInterval:2];
         NSLog(@"任务1执行完毕");
         completion(@"结果1", nil);
     });
 }];

 // 添加第二个任务：接收任务1的结果，模拟错误情况
 [chain addTask:^(id input, void (^completion)(id, NSError *)) {
     NSLog(@"任务2接收到结果：%@", input);
     dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
         [NSThread sleepForTimeInterval:2];
         NSLog(@"任务2发生错误");
         NSError *error = [NSError errorWithDomain:@"com.example.task" code:100 userInfo:@{NSLocalizedDescriptionKey:@"任务2失败"}];
         completion(nil, error);
     });
 }];

 // 添加第三个任务：如果前面的任务成功则执行，否则不会被执行
 [chain addTask:^(id input, void (^completion)(id, NSError *)) {
     NSLog(@"任务3接收到结果：%@", input);
     dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
         [NSThread sleepForTimeInterval:2];
         NSLog(@"任务3执行完毕");
         completion(@"结果3", nil);
     });
 }];

 // 启动任务链，并传入初始输入
 [chain runWithInitialInput:nil completion:^(id result, NSError *error) {
     if (error) {
         NSLog(@"任务链执行中断，错误：%@", error.localizedDescription);
     } else {
         NSLog(@"任务链全部执行完毕，最终结果：%@", result);
     }
 }];
*/


/******************************************************************************************************************************
// 假设 JLTaskChain 和 TaskOperation 已经定义好
// 模拟一个任务链处理一个字符串列表
NSArray *taskList = @[@"任务A", @"任务B", @"任务C"];

 JLTaskChain *chain = [[JLTaskChain alloc] init];

// 遍历列表，为每个元素添加一个任务
for (NSString *taskName in taskList) {
    [chain addTask:^(id input, void (^completion)(id, NSError *)) {
        NSLog(@"开始处理：%@", taskName);
        // 模拟异步耗时操作
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            [NSThread sleepForTimeInterval:1.0];
            // 模拟：如果任务名称为“任务B”，产生错误，后续任务不再执行
            if ([taskName isEqualToString:@"任务B"]) {
                NSError *error = [NSError errorWithDomain:@"com.example.task" code:100 userInfo:@{NSLocalizedDescriptionKey:@"任务B 执行失败"}];
                NSLog(@"处理 %@ 时发生错误", taskName);
                completion(nil, error);
            } else {
                // 模拟正常处理，返回结果
                NSString *result = [NSString stringWithFormat:@"%@ 已处理", taskName];
                NSLog(@"处理完成：%@", result);
                completion(result, nil);
            }
        });
    }];
}

// 启动任务链，初始输入可以为 nil（或者根据需求传递其他数据）
[chain runWithInitialInput:nil completion:^(id result, NSError *error) {
    if (error) {
        NSLog(@"任务链中断，错误信息：%@", error.localizedDescription);
    } else {
        NSLog(@"所有任务完成，最终结果：%@", result);
    }
}];
 */


@interface JLTaskChain : NSObject

// 任务块数组，每个任务块的签名：^(id input, void(^completion)(id output, NSError *error))
@property (nonatomic, strong) NSMutableArray *taskBlocks;
+ (void)cancelAllTasks;
- (void)addTask:(void (^)(id input, void (^completion)(id _Nullable output, NSError *_Nullable error)))task;
- (void)runWithInitialInput:(id _Nullable)input completion:(void (^ _Nullable)(id _Nullable result, NSError *_Nullable error))completion;
- (void)cancel;
@end

NS_ASSUME_NONNULL_END
