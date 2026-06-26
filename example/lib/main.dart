import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_jl_ota/flutter_jl_ota.dart';
import 'package:permission_handler/permission_handler.dart';

import 'ota_path_util.dart';
import 'permission_util.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  static const String sampleIosDeviceUuid =
      '2B3681AF-B077-297D-D291-FA4A908CE06A';
  static const String sampleAndroidDeviceAddress = '00:00:00:55:FB:D4';

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
      Permission.bluetoothAdvertise,
    ], onAllowed: (result) async {});
  }

  void startOta() async {
    String deviceUuid = sampleIosDeviceUuid; // Replace with the actual UUID.
    if (Platform.isAndroid) {
      deviceUuid = sampleAndroidDeviceAddress;
    }
    debugPrint('flutter_ota_log => startOta started');
    String ufwPath = await moveFileToLib();
    await FlutterJlOta.startOtaUpdate(deviceUuid, ufwPath);

    // Listen for progress and state changes.
    FlutterJlOta.listenToOtaProgressUpdates((event) {
      debugPrint('OTA Progress: ${event.progress}%, Status: ${event.status}');
      if (event.isCompleted || event.isError) {
        // Optionally stop listening or run follow-up logic.
      }
    });
  }

  /// Copies the bundled firmware asset to a writable local path.
  static Future<String> moveFileToLib() async {
    String fileName = 'update_20250401.ufw';

    String filePath = 'assets/$fileName';
    final ByteData data = await rootBundle.load(filePath);
    final List<int> bytes = data.buffer.asUint8List(
      data.offsetInBytes,
      data.lengthInBytes,
    );
    String libPath = await OtaPathUtil.getFilePath(fileName);
    File file = File(libPath);
    await file.writeAsBytes(bytes);
    debugPrint('Firmware size: ${bytes.length} bytes');
    return libPath;
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(title: const Text('Plugin example app')),
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
                child: const Text('Upgrade'),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
