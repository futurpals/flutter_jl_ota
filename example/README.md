# flutter_jl_ota example

This example app demonstrates the basic OTA flow:

1. Request Bluetooth runtime permissions.
2. Copy a bundled `.ufw` firmware file to an app-accessible path.
3. Start an OTA update by device identifier.
4. Listen for progress callbacks.

Before running the example, replace the sample device identifiers in
`lib/main.dart` and place your firmware file under `assets/`.

```bash
cd example
flutter pub get
flutter run
```
