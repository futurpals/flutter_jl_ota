# flutter_jl_ota

A Flutter plugin for JL/JieLi over-the-air firmware updates. The package wraps
the official JL OTA native SDKs behind a compact MethodChannel API and exposes
scan, connect, update, cancel, SDK version, and progress callback helpers for
Android and iOS.

## Highlights

- Android and iOS OTA support for JL/JieLi chipsets.
- Backward-compatible progress callback plus typed `OtaProgress` events.
- Optional `deviceName` support for native scan and connection filters.
- `stopScan`, `cancelOtaUpdate`, `isOtaUpdateInProgress`, and
  `getSdkVersion` helpers.
- Compatible with apps that already use Flutter BLE packages such as
  `flutter_blue_plus`.

## Platform Support

| Platform | Minimum version | Bundled native SDK |
| --- | --- | --- |
| Android | API 21 | `jl_bt_ota_V1.10.0_10932` |
| iOS | 12.0 | `JL_OTALib 2.3.1`, `JL_BLEKit 1.13.0`, `JL_AdvParse 1.1.1`, `JL_HashPair 1.0.2` |

## Installation

Add the package to your app:

```yaml
dependencies:
  flutter_jl_ota: ^1.0.4
```

Then install dependencies:

```bash
flutter pub get
```

## Platform Setup

### Android

The plugin declares the required Bluetooth and storage permissions in its
Android manifest. Your host app is still responsible for requesting runtime
permissions before scanning or connecting, especially on Android 12 and later:

```dart
await [
  Permission.location,
  Permission.bluetoothScan,
  Permission.bluetoothConnect,
  Permission.bluetoothAdvertise,
].request();
```

### iOS

Add Bluetooth usage descriptions to the host app `Info.plist` if your app does
not already define them:

```xml
<key>NSBluetoothAlwaysUsageDescription</key>
<string>This app uses Bluetooth to update device firmware.</string>
<key>NSBluetoothPeripheralUsageDescription</key>
<string>This app uses Bluetooth to update device firmware.</string>
```

## Quick Start

Register for progress before starting the OTA flow:

```dart
FlutterJlOta.listenToOtaProgressUpdates((event) {
  debugPrint('OTA ${event.progress}% - ${event.status}');

  if (event.isCompleted) {
    debugPrint('OTA completed');
  }

  if (event.isError) {
    debugPrint('OTA failed: ${event.status}');
  }
});
```

Start an update with a device identifier and a local `.ufw` firmware path:

```dart
final started = await FlutterJlOta.startOtaUpdate(
  deviceUuidOrMacAddress,
  firmwarePath,
  deviceName: 'JL_Device',
);

if (!started) {
  debugPrint('OTA did not start');
}
```

You can also run the flow step by step:

```dart
await FlutterJlOta.startScan();
await FlutterJlOta.connectDevice(deviceUuidOrMacAddress);
await FlutterJlOta.getDeviceInfo();
await FlutterJlOta.startOtaUpdate(deviceUuidOrMacAddress, firmwarePath);
```

## API Reference

| API | Returns | Description |
| --- | --- | --- |
| `startScan()` | `Future<bool>` | Starts BLE scanning. |
| `stopScan()` | `Future<bool>` | Stops BLE scanning. |
| `connectDevice(String uuid, {String? deviceName})` | `Future<bool>` | Connects to a device by iOS UUID or Android MAC address. |
| `getDeviceInfo()` | `Future<bool>` | Queries native OTA device information. |
| `startOtaUpdate(String uuid, String filePath, {String? deviceName})` | `Future<bool>` | Connects if needed and starts OTA with a local firmware file. |
| `cancelOtaUpdate()` | `Future<bool>` | Requests OTA cancellation. |
| `isOtaUpdateInProgress()` | `Future<bool>` | Returns the native OTA running state. |
| `getSdkVersion()` | `Future<String?>` | Returns the native JL OTA SDK version when available. |
| `listenToOtaProgress(OtaProgressCallback callback)` | `void` | Registers the legacy `(progress, status)` callback. |
| `listenToOtaProgressUpdates(ValueChanged<OtaProgress> callback)` | `void` | Registers the typed progress callback. |

## Progress Events

`OtaProgress` contains:

```dart
class OtaProgress {
  final int progress;
  final String status;

  bool get isCompleted;
  bool get isError;
}
```

Common statuses include `STARTED`, `DOWNLOADING_LOADER`,
`UPGRADING_FIRMWARE`, `COMPLETED`, `CANCELED`, `ERROR: ...`,
`Preparing`, `Upgrading`, `Prepared`, `Reconnecting`, `Success`, `Failed`,
and `Timeout`.

## Firmware File Handling

The native SDK expects a local firmware file path. If the firmware is bundled
as a Flutter asset, copy it to an app-accessible directory before starting OTA:

```dart
Future<String> prepareFirmwareFile(String assetPath, String fileName) async {
  final data = await rootBundle.load(assetPath);
  final bytes = data.buffer.asUint8List(data.offsetInBytes, data.lengthInBytes);
  final directory = await getTemporaryDirectory();
  final file = File('${directory.path}/$fileName');
  await file.writeAsBytes(bytes);
  return file.path;
}
```

## Troubleshooting

| Symptom | Check |
| --- | --- |
| Scan does not find devices | Confirm runtime Bluetooth permissions and that Bluetooth is enabled. |
| Android connection fails | Use the device MAC address and verify the device advertises over BLE. |
| iOS connection fails | Use the CoreBluetooth UUID returned by discovery or a previously known UUID. |
| OTA starts but never progresses | Confirm the firmware path points to a readable `.ufw` file. |
| Cancellation returns `false` | Some OTA modes can only cancel during specific native SDK states. |

## Official SDK References

- [JieLi Android OTA SDK](https://github.com/Jieli-Tech/Android-JL_OTA)
- [JieLi iOS OTA SDK](https://github.com/Jieli-Tech/iOS-JL_OTA)
- [Official JL_OTA_Flutter package](https://gitee.com/Jieli-Tech/JL_OTA_Flutter)

## License

This package follows the license in [LICENSE](LICENSE). The bundled native SDKs
belong to their respective owners.
