import 'ota_service.dart';

class FlutterJlOta {
  /// Starts BLE scanning for OTA-capable devices.
  static Future<bool> startScan() async {
    return OtaService.startScan();
  }

  /// Stops the current BLE scan.
  static Future<bool> stopScan() async {
    return OtaService.stopScan();
  }

  /// Connects to a device by iOS UUID or Android MAC address.
  static Future<bool> connectDevice(String uuid, {String? deviceName}) async {
    return OtaService.connectDevice(uuid, deviceName: deviceName);
  }

  /// Queries OTA device information from the native SDK.
  static Future<bool> getDeviceInfo() async {
    return OtaService.getDeviceInfo();
  }

  /// Starts an OTA update with a local firmware file path.
  ///
  /// The native layer connects to the device when needed before starting the
  /// update.
  static Future<bool> startOtaUpdate(
    String uuid,
    String filePath, {
    String? deviceName,
  }) async {
    return OtaService.startOtaUpdate(uuid, filePath, deviceName: deviceName);
  }

  /// Returns whether the native SDK is currently running an OTA update.
  static Future<bool> isOtaUpdateInProgress() async {
    return OtaService.isOtaUpdateInProgress();
  }

  /// Returns the native JL OTA SDK version when available.
  static Future<String?> getSdkVersion() async {
    return OtaService.getSdkVersion();
  }

  /// Requests OTA cancellation.
  static Future<bool> cancelOtaUpdate() async {
    return OtaService.cancelOtaUpdate();
  }

  /// Registers the legacy OTA progress callback.
  static void listenToOtaProgress(OtaProgressCallback onProgress) {
    OtaService.listenToOtaProgress(onProgress);
  }

  /// Registers the typed OTA progress callback.
  static void listenToOtaProgressUpdates(
    void Function(OtaProgress) onProgress,
  ) {
    OtaService.listenToOtaProgressUpdates(onProgress);
  }
}
