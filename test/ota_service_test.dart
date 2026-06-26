import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_jl_ota/flutter_jl_ota.dart';
import 'package:flutter_jl_ota/ota_service.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  const channel = MethodChannel('flutter_jl_ota');
  final calls = <MethodCall>[];
  late DebugPrintCallback originalDebugPrint;

  setUp(() {
    originalDebugPrint = debugPrint;
    debugPrint = (message, {wrapWidth}) {};
    calls.clear();
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, (call) async {
          calls.add(call);
          switch (call.method) {
            case 'getSdkVersion':
              return 'V1.10.0(10932)';
            case 'isOta':
              return true;
            default:
              return true;
          }
        });
  });

  tearDown(() {
    debugPrint = originalDebugPrint;
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, null);
    OtaService.clearOtaProgressListener();
  });

  test(
    'startOtaUpdate sends uuid file path and optional device name',
    () async {
      final result = await OtaService.startOtaUpdate(
        'AA:BB:CC:DD:EE:FF',
        '/tmp/update.ufw',
        deviceName: 'JL_Device',
      );

      expect(result, isTrue);
      expect(calls.single.method, 'startOtaUpdate');
      expect(calls.single.arguments, {
        'uuid': 'AA:BB:CC:DD:EE:FF',
        'filePath': '/tmp/update.ufw',
        'deviceName': 'JL_Device',
      });
    },
  );

  test('new official-inspired wrappers call matching native methods', () async {
    expect(await OtaService.stopScan(), isTrue);
    expect(await OtaService.isOtaUpdateInProgress(), isTrue);
    expect(await OtaService.getSdkVersion(), 'V1.10.0(10932)');

    expect(calls.map((call) => call.method), [
      'stopScan',
      'isOta',
      'getSdkVersion',
    ]);
  });

  test(
    'typed progress parser is null safe and exposes terminal state helpers',
    () {
      final completed = OtaProgress.fromMap({
        'progress': 100,
        'status': 'COMPLETED',
      });
      final failed = OtaProgress.fromMap({
        'progress': 'bad value',
        'status': null,
      });

      expect(completed.progress, 100);
      expect(completed.status, 'COMPLETED');
      expect(completed.isCompleted, isTrue);
      expect(completed.isError, isFalse);
      expect(failed.progress, 0);
      expect(failed.status, 'UNKNOWN');
    },
  );

  test(
    'legacy and typed progress listeners receive otaProgress callbacks',
    () async {
      final legacyEvents = <String>[];
      final typedEvents = <OtaProgress>[];

      OtaService.listenToOtaProgress((progress, status) {
        legacyEvents.add('$progress:$status');
      });
      OtaService.listenToOtaProgressUpdates(typedEvents.add);

      await TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
          .handlePlatformMessage(
            channel.name,
            channel.codec.encodeMethodCall(
              const MethodCall('otaProgress', {
                'progress': 42,
                'status': 'UPGRADING_FIRMWARE',
              }),
            ),
            (_) {},
          );

      expect(legacyEvents, ['42:UPGRADING_FIRMWARE']);
      expect(typedEvents, [
        const OtaProgress(progress: 42, status: 'UPGRADING_FIRMWARE'),
      ]);
    },
  );

  test('FlutterJlOta facade exposes new methods', () async {
    expect(await FlutterJlOta.stopScan(), isTrue);
    expect(await FlutterJlOta.isOtaUpdateInProgress(), isTrue);
    expect(await FlutterJlOta.getSdkVersion(), 'V1.10.0(10932)');
  });

  test('platform exceptions are converted to safe fallback values', () async {
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, (call) async {
          throw PlatformException(code: 'native_error');
        });

    expect(await OtaService.stopScan(), isFalse);
    expect(await OtaService.isOtaUpdateInProgress(), isFalse);
    expect(await OtaService.getSdkVersion(), isNull);
  });
}
