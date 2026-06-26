import 'ota_service.dart';

class FlutterJlOta {
  ///  开始扫描设备
  static Future<bool> startScan() async {
    return OtaService.startScan();
  }

  /// 停止扫描设备
  static Future<bool> stopScan() async {
    return OtaService.stopScan();
  }

  /// 连接设备
  static Future<bool> connectDevice(String uuid, {String? deviceName}) async {
    return OtaService.connectDevice(uuid, deviceName: deviceName);
  }

  /// 获取设备信息
  static Future<bool> getDeviceInfo() async {
    return OtaService.getDeviceInfo();
  }

  /// 开始 OTA 升级
  /// 可以直接执行该方法，会自动连接设备并更新
  static Future<bool> startOtaUpdate(
    String uuid,
    String filePath, {
    String? deviceName,
  }) async {
    return OtaService.startOtaUpdate(uuid, filePath, deviceName: deviceName);
  }

  /// 是否正在 OTA 升级
  static Future<bool> isOtaUpdateInProgress() async {
    return OtaService.isOtaUpdateInProgress();
  }

  /// 获取原生 JL OTA SDK 版本
  static Future<String?> getSdkVersion() async {
    return OtaService.getSdkVersion();
  }

  /// 取消 OTA 升级
  static Future<bool> cancelOtaUpdate() async {
    return OtaService.cancelOtaUpdate();
  }

  /// 监听 OTA 进度和状态
  static void listenToOtaProgress(OtaProgressCallback onProgress) {
    OtaService.listenToOtaProgress(onProgress);
  }

  /// 监听结构化 OTA 进度和状态
  static void listenToOtaProgressUpdates(
    void Function(OtaProgress) onProgress,
  ) {
    OtaService.listenToOtaProgressUpdates(onProgress);
  }
}
