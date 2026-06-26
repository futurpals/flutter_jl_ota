import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

typedef OtaProgressCallback = void Function(int progress, String status);

@immutable
class OtaProgress {
  const OtaProgress({required this.progress, required this.status});

  factory OtaProgress.fromMap(Object? value) {
    if (value is! Map) {
      return const OtaProgress(progress: 0, status: 'UNKNOWN');
    }

    final rawProgress = value['progress'];
    final rawStatus = value['status'];

    return OtaProgress(
      progress:
          rawProgress is num ? rawProgress.round().clamp(0, 100).toInt() : 0,
      status:
          rawStatus is String && rawStatus.trim().isNotEmpty
              ? rawStatus
              : 'UNKNOWN',
    );
  }

  final int progress;
  final String status;

  bool get isCompleted {
    final normalized = status.toUpperCase();
    return progress >= 100 ||
        normalized == 'COMPLETED' ||
        normalized == 'SUCCESS';
  }

  bool get isError {
    final normalized = status.toUpperCase();
    return normalized.startsWith('ERROR') ||
        normalized == 'FAILED' ||
        normalized == 'TIMEOUT';
  }

  @override
  bool operator ==(Object other) {
    return identical(this, other) ||
        other is OtaProgress &&
            runtimeType == other.runtimeType &&
            progress == other.progress &&
            status == other.status;
  }

  @override
  int get hashCode => Object.hash(progress, status);

  @override
  String toString() => 'OtaProgress(progress: $progress, status: $status)';
}

class OtaService {
  static const MethodChannel _channel = MethodChannel('flutter_jl_ota');
  static OtaProgressCallback? _legacyProgressCallback;
  static ValueChanged<OtaProgress>? _typedProgressCallback;
  static bool _isProgressHandlerRegistered = false;

  /// Starts BLE scanning for OTA-capable devices.
  static Future<bool> startScan() async {
    try {
      final result = await _channel.invokeMethod('startScan');
      return result == true;
    } catch (e) {
      debugPrint('Error starting scan: $e');
      return false;
    }
  }

  /// Stops the current BLE scan.
  static Future<bool> stopScan() async {
    try {
      final result = await _channel.invokeMethod('stopScan');
      return result == true;
    } catch (e) {
      debugPrint('Error stopping scan: $e');
      return false;
    }
  }

  /// Connects to a device by iOS UUID or Android MAC address.
  static Future<bool> connectDevice(String uuid, {String? deviceName}) async {
    try {
      final arguments = <String, Object?>{
        'uuid': uuid,
        if (deviceName != null) 'deviceName': deviceName,
      };
      final result = await _channel.invokeMethod('connectDevice', arguments);
      return result == true;
    } catch (e) {
      debugPrint('Error connecting device: $e');
      return false;
    }
  }

  /// Queries OTA device information from the native SDK.
  static Future<bool> getDeviceInfo() async {
    try {
      final result = await _channel.invokeMethod('getDeviceInfo');
      return result == true;
    } catch (e) {
      debugPrint('Error getting device info: $e');
      return false;
    }
  }

  /// Starts an OTA update with a local firmware file path.
  static Future<bool> startOtaUpdate(
    String uuid,
    String filePath, {
    String? deviceName,
  }) async {
    try {
      final arguments = <String, Object?>{
        'uuid': uuid,
        'filePath': filePath,
        if (deviceName != null) 'deviceName': deviceName,
      };
      final result = await _channel.invokeMethod('startOtaUpdate', arguments);
      return result == true;
    } catch (e) {
      debugPrint('Error starting OTA: $e');
      return false;
    }
  }

  /// Returns whether the native SDK is currently running an OTA update.
  static Future<bool> isOtaUpdateInProgress() async {
    try {
      final result = await _channel.invokeMethod('isOta');
      return result == true;
    } catch (e) {
      debugPrint('Error checking OTA state: $e');
      return false;
    }
  }

  /// Returns the native JL OTA SDK version when available.
  static Future<String?> getSdkVersion() async {
    try {
      final result = await _channel.invokeMethod<String>('getSdkVersion');
      return result;
    } catch (e) {
      debugPrint('Error getting SDK version: $e');
      return null;
    }
  }

  /// Requests OTA cancellation.
  static Future<bool> cancelOtaUpdate() async {
    try {
      final result = await _channel.invokeMethod('cancelOtaUpdate');
      return result == true;
    } catch (e) {
      debugPrint('Error cancelling OTA: $e');
      return false;
    }
  }

  /// Registers the legacy OTA progress callback.
  static void listenToOtaProgress(OtaProgressCallback onProgress) {
    _legacyProgressCallback = onProgress;
    _ensureProgressHandler();
  }

  /// Registers the typed OTA progress callback.
  static void listenToOtaProgressUpdates(ValueChanged<OtaProgress> onProgress) {
    _typedProgressCallback = onProgress;
    _ensureProgressHandler();
  }

  @visibleForTesting
  static void clearOtaProgressListener() {
    _legacyProgressCallback = null;
    _typedProgressCallback = null;
    _isProgressHandlerRegistered = false;
    _channel.setMethodCallHandler(null);
  }

  static void _ensureProgressHandler() {
    if (_isProgressHandlerRegistered) return;
    _channel.setMethodCallHandler(_handleMethodCall);
    _isProgressHandlerRegistered = true;
  }

  static Future<void> _handleMethodCall(MethodCall call) async {
    if (call.method != 'otaProgress') return;

    final progress = OtaProgress.fromMap(call.arguments);
    _legacyProgressCallback?.call(progress.progress, progress.status);
    _typedProgressCallback?.call(progress);
  }
}
