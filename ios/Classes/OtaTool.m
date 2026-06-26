//
//  OtaTool.m
//

#import "OtaTool.h"
#import "JLBleManager.h"

static OtaTool *sharedInstance = nil;

@interface OtaTool () <JLBleManagerOtaDelegate>

@property(nonatomic, copy) NSString *uuid;
@property(nonatomic, copy) NSString *filePath;
@property(nonatomic, copy) void (^otaProgressCallback)(NSInteger progress, NSString *status);
@property(nonatomic, assign) BOOL otaInProgress;

@end

@implementation OtaTool

#pragma mark - 单例实现

+ (instancetype)sharedInstance {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[self alloc] init];
        [sharedInstance setup];
    });
    return sharedInstance;
}

+ (instancetype)allocWithZone:(struct _NSZone *)zone {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [super allocWithZone:zone];
    });
    return sharedInstance;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        [[JLBleManager sharedInstance] addDelegate:self];
    }
    return self;
}

#pragma mark - 公共方法

- (void)startScan {
    [[JLBleManager sharedInstance] startScanBLE];
}

- (void)stopScan {
    [[JLBleManager sharedInstance] stopScanBLE];
}

- (void)connectDeviceWithUUID:(NSString *)uuid {
    self.uuid = uuid;
    [[JLBleManager sharedInstance] connectPeripheralWithUUID:uuid];
}

- (void)getDeviceInfo:(void (^)(BOOL needForcedUpgrade))callback {
    NSLog(@"JLBleManager isConnected: %d", [[JLBleManager sharedInstance] isConnected]);
    [[JLBleManager sharedInstance] getDeviceInfo:^(BOOL needForcedUpgrade) {
        NSLog(@"needForcedUpgrade : %d", needForcedUpgrade);
        if (callback) {
            callback(needForcedUpgrade);
        }
    }];
}

- (void)startOtaWithUuid:(NSString *)uuid filePath:(NSString *)filePath {
    self.uuid = uuid;
    self.filePath = filePath;
    self.otaInProgress = YES;

    if (![[JLBleManager sharedInstance] isConnected]) {
        [[JLBleManager sharedInstance] connectPeripheralWithUUID:uuid];
    } else {
        [self checkDeviceAndStartOta];
    }
}

- (void)cancelOtaUpdate:(void (^)(uint8_t status))completion {
    [[JLBleManager sharedInstance] otaFuncCancel:^(uint8_t status) {
        if (completion) {
            completion(status);
        }
        if (self.otaProgressCallback) {
            self.otaProgressCallback(0, status == 0 ? @"Cancelled" : @"CancelFailed");
        }
        self.otaInProgress = NO;
    }];
}

- (void)setOtaProgressCallback:(void (^)(NSInteger, NSString

*))callback {
    _otaProgressCallback = [callback copy];
}

- (BOOL)isOtaUpdateInProgress {
    return self.otaInProgress;
}

- (NSString *)sdkVersion {
    NSString *sdkVersion = [JL_OTAManager logSDKVersion];
    return sdkVersion ?: @"";
}

#pragma mark - 初始化与通知

- (void)setup {
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(handleBleConnected:)
                                                 name:kFLT_BLE_CONNECTED
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(handleBleDisconnected:)
                                                 name:kFLT_BLE_DISCONNECTED
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(handleBlePaired:)
                                                 name:kFLT_BLE_PAIRED
                                               object:nil];
}

- (void)handleBleConnected:(NSNotification *)notification {
    if ([[JLBleManager sharedInstance] isConnected] && self.filePath) {
        [self checkDeviceAndStartOta];
    }
}

- (void)handleBlePaired:(NSNotification *)notification {
    if ([[JLBleManager sharedInstance] isConnected] && self.filePath) {
        [self checkDeviceAndStartOta];
    }
}

- (void)handleBleDisconnected:(NSNotification *)notification {
    if (self.otaProgressCallback) {
        self.otaProgressCallback(0, @"Disconnected");
    }
}

- (void)checkDeviceAndStartOta {
    [[JLBleManager sharedInstance] getDeviceInfo:^(BOOL needForcedUpgrade) {
        NSLog(@"needForcedUpgrade : %d", needForcedUpgrade);
        [[JLBleManager sharedInstance] otaFuncWithFilePath:self.filePath];
    }];
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [[JLBleManager sharedInstance] removeDelegate:self];
}

#pragma mark - JLBleManagerOtaDelegate

- (void)otaProgressWithOtaResult:(JL_OTAResult)result withProgress:(float)progress {
    if (self.otaProgressCallback) {
        NSInteger intProgress = (NSInteger)(progress * 100);
        NSString * status = [self statusStringForResult:result];

        switch (result) {
            case JL_OTAResultPreparing:
            case JL_OTAResultUpgrading:
                intProgress = MIN(intProgress, 99);
                break;
            case JL_OTAResultSuccess:
                NSLog(@"--->升级成功.");
                intProgress = 100;
                self.otaInProgress = NO;
                break;
            case JL_OTAResultPrepared:
                NSLog(@"---> 检验文件【完成】");
                break;
            case JL_OTAResultReconnect:
                [[JLBleManager sharedInstance] connectPeripheralWithUUID:self.uuid];
                break;
            case JL_OTAResultReconnectWithMacAddr:
                [self handleReconnectByMac];
                break;
            case JL_OTAResultReboot:
                NSLog(@"--->设备重启.");
                break;
            case JL_OTAResultFail:
            case JL_OTAResultFailCmdTimeout:
                self.otaInProgress = NO;
                break;
            case JL_OTAResultCancel:
                self.otaInProgress = NO;
                break;
            default:
                break;
        }

        self.otaProgressCallback(intProgress, status);
    }
}


- (void)handleReconnectByMac {
    JLBleManager *model = [JLBleManager sharedInstance];
    NSLog(@"---> OTA正在通过Mac Addr方式回连设备... %@",
          model.otaManager.bleAddr);
    [JLBleManager sharedInstance].lastBleMacAddress = model.otaManager.bleAddr;
    [[JLBleManager sharedInstance] startScanBLE];
}

- (NSString *)statusStringForResult:(JL_OTAResult)result {
    switch (result) {
        case JL_OTAResultPreparing:
            return @"Preparing";
        case JL_OTAResultUpgrading:
            return @"Upgrading";
        case JL_OTAResultPrepared:
            return @"Prepared";
        case JL_OTAResultReconnect:
            return @"Reconnecting";
        case JL_OTAResultReconnectWithMacAddr:
            return @"ReconnectingWithMac";
        case JL_OTAResultSuccess:
            return @"Success";
        case JL_OTAResultFail:
            return @"Failed";
        case JL_OTAResultReboot:
            return @"Rebooting";
        case JL_OTAResultFailCmdTimeout:
            return @"Timeout";
        default:
            return @"Unknown";
    }
}

@end
