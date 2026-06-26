#import "FlutterJlOtaPlugin.h"
#import "OtaTool.h"

@interface FlutterJlOtaPlugin ()
@property(nonatomic, strong) FlutterMethodChannel *channel;
@end

@implementation FlutterJlOtaPlugin
+ (void)registerWithRegistrar:(NSObject <FlutterPluginRegistrar> *)registrar {
    FlutterMethodChannel *channel = [FlutterMethodChannel
            methodChannelWithName:@"flutter_jl_ota"
                  binaryMessenger:[registrar messenger]];
    FlutterJlOtaPlugin *instance = [[FlutterJlOtaPlugin alloc] init];
    [registrar addMethodCallDelegate:instance channel:channel];
    instance.channel = channel;
}

- (void)handleMethodCall:(FlutterMethodCall *)call result:(FlutterResult)result {
    if ([@"getPlatformVersion" isEqualToString:call.method]) {
        result([@"iOS " stringByAppendingString:[[UIDevice currentDevice] systemVersion]]);
    } else if ([@"getSdkVersion" isEqualToString:call.method]) {
        result([[OtaTool sharedInstance] sdkVersion]);
    } else if ([@"isOta" isEqualToString:call.method]) {
        result(@([[OtaTool sharedInstance] isOtaUpdateInProgress]));
    } else if ([@"startScan" isEqualToString:call.method]) {
        [[OtaTool sharedInstance] startScan];
        result(@YES);
    } else if ([@"stopScan" isEqualToString:call.method]) {
        [[OtaTool sharedInstance] stopScan];
        result(@YES);
    } else if ([@"connectDevice" isEqualToString:call.method]) {
        NSString *uuid = call.arguments[@"uuid"];
        if ([uuid isKindOfClass:[NSString class]] && uuid.length > 0) {
            [[OtaTool sharedInstance] connectDeviceWithUUID:uuid];
            result(@YES);
        } else {
            result([FlutterError errorWithCode:@"INVALID_UUID" message:@"UUID is invalid" details:nil]);
        }
    } else if ([@"getDeviceInfo" isEqualToString:call.method]) {
        [[OtaTool sharedInstance] getDeviceInfo:^(BOOL needForcedUpgrade) {
            result(@(needForcedUpgrade));
        }];
    } else if ([@"startOtaUpdate" isEqualToString:call.method]) {
        NSDictionary *params = call.arguments;
        if ([params isKindOfClass:[NSDictionary class]]) {
            NSString *uuid = params[@"uuid"];
            NSString *filePath = params[@"filePath"];
            if ([uuid isKindOfClass:[NSString class]] && uuid.length > 0 &&
                [filePath isKindOfClass:[NSString class]] && filePath.length > 0) {
                __weak typeof(self) weakSelf = self;
                [[OtaTool sharedInstance] setOtaProgressCallback:^(NSInteger progress, NSString *status) {
                    NSDictionary *response = @{
                            @"progress": @(progress),
                            @"status": status ?: @""
                    };
                    dispatch_async(dispatch_get_main_queue(), ^{
                        [weakSelf.channel invokeMethod:@"otaProgress" arguments:response];
                    });
                }];

                [[OtaTool sharedInstance] startOtaWithUuid:uuid filePath:filePath];
                result(@YES);
            } else {
                result([FlutterError errorWithCode:@"INVALID_PARAMS"
                                           message:@"UUID or filePath is invalid"
                                           details:nil]);
            }
        } else {
            result([FlutterError errorWithCode:@"INVALID_ARGUMENTS"
                                       message:@"Arguments must be a dictionary"
                                       details:nil]);
        }
    } else if ([@"cancelOtaUpdate" isEqualToString:call.method]) {
        [[OtaTool sharedInstance] cancelOtaUpdate:^(uint8_t status) {
            result(@(status == 0)); // status == 0 indicates success.
        }];
    } else {
        result(FlutterMethodNotImplemented);
    }
}

@end
