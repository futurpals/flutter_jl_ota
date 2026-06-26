**Languages:**

[![Chinese](https://img.shields.io/badge/Language-Chinese-blueviolet?style=for-the-badge)](README.md)
[![English](https://img.shields.io/badge/Language-English-blueviolet?style=for-the-badge)](README.en.md)

# JL OTA Update Plugin for Flutter

A Flutter plugin for OTA firmware updates targeting JL (JieLi) chipsets. Supports
Android and iOS platforms with progress callbacks and error handling.

|             | Android | iOS   |
|-------------|---------|-------|
| **Support** | SDK 21+ | 12.0+ |

---

## Setup

Integrated with the latest JL OTA plugin package

* Android SDK `jl_bt_ota_V1.10.0_10932`
* iOS SDK `JL_OTALib 2.3.1` / `JL_BLEKit 1.13.0` / `JL_AdvParse 1.1.1` / `JL_HashPair 1.0.2`

[Jieli OTA Android Official GitHub repository](https://github.com/Jieli-Tech/Android-JL_OTA)
[Jieli OTA IOS Official GitHub repository](https://github.com/Jieli-Tech/iOS-JL_OTA)

---

## Installation

```yaml
dependencies:
  flutter_jl_ota: ^1.0.4
```

## API

```dart
await FlutterJlOta.startScan();
await FlutterJlOta.stopScan();
await FlutterJlOta.connectDevice(deviceUuid, deviceName: 'JL_Device');
await FlutterJlOta.startOtaUpdate(deviceUuid, ufwPath, deviceName: 'JL_Device');
await FlutterJlOta.cancelOtaUpdate();

final isUpdating = await FlutterJlOta.isOtaUpdateInProgress();
final sdkVersion = await FlutterJlOta.getSdkVersion();
```

The legacy progress callback is still supported:

```dart
FlutterJlOta.listenToOtaProgress((progress, status) {
  print('OTA Progress: $progress%, Status: $status');
});
```

You can also use the structured progress object:

```dart
FlutterJlOta.listenToOtaProgressUpdates((event) {
  print('OTA Progress: ${event.progress}%, Status: ${event.status}');
  if (event.isCompleted || event.isError) {
    // Handle completion or failure.
  }
});
```

## Example

* Place your UFW firmware in the assets directory
* Replace the device Uuid with your actual device Uuid

<?code-excerpt "basic.dart (basic-example)"?>

```dart
void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  // String _platformVersion = 'Unknown';
  final otaPlugin = FlutterJlOta();

  @override
  void initState() {
    super.initState();
    initPlatformState();
  }

  // Platform messages are asynchronous, so we initialize in an async method.
  Future<void> initPlatformState() async {
    if (!mounted) return;
    PermissionUtil.preRequestPermissions([
      Permission.location,
      Permission.bluetoothScan,
      Permission.bluetoothConnect,
      Permission.bluetoothAdvertise
    ], onAllowed: (result) async {});
  }

  void startOta() async {
    String deviceUuid = '2B3681AF-B077-297D-D291-FA4A908CE06A'; // Replace with the actual UUID
    print("flutter_ota_log => ${'startOta 执行了'}");
    String ufwPath = await moveFileToLib();
    await OtaService.startOtaUpdate(deviceUuid, ufwPath);

    // Listen for progress and state.
    OtaService.listenToOtaProgressUpdates((event) {
      print('OTA Progress: ${event.progress}%, Status: ${event.status}');
      if (event.isCompleted || event.isError) {
        // Optionally stop listening or run follow-up logic.
      }
    });
  }

  /// Debug helper.
  static moveFileToLib() async {
    String fileName = 'update.ufw';

    String filePath = 'assets/$fileName';
    final ByteData data = await rootBundle.load(filePath);
    final List<int> bytes =
    data.buffer.asUint8List(data.offsetInBytes, data.lengthInBytes);
    String libPath = await OtaPathUtil.getFilePath(fileName);
    File file = File(libPath);
    await file.writeAsBytes(bytes);
    print("该文件bytes大小为 ${bytes.length}");
    return libPath;
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            // Center(
            //   child: Text('Running on: $_platformVersion\n'),
            // ),
            Center(
              child: ElevatedButton(
                onPressed: () {
                  startOta();
                },
                child: const Text("upgrade"),
              ),
            )
          ],
        ),
      ),
    );
  }
}

```
