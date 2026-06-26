//
//  OtaTool.h
//

#import <Foundation/Foundation.h>
#import "JLBleManager.h"

NS_ASSUME_NONNULL_BEGIN

@interface OtaTool : NSObject

+ (instancetype)sharedInstance;

- (void)startScan;
- (void)stopScan;
- (void)connectDeviceWithUUID:(NSString *)uuid;
- (void)getDeviceInfo:(void (^)(BOOL needForcedUpgrade))callback;
- (void)startOtaWithUuid:(NSString *)uuid filePath:(NSString *)filePath;
- (void)cancelOtaUpdate:(void (^)(uint8_t status))completion;
- (void)setOtaProgressCallback:(void (^)(NSInteger progress, NSString *status))callback;
- (BOOL)isOtaUpdateInProgress;
- (NSString *)sdkVersion;

@end

NS_ASSUME_NONNULL_END
