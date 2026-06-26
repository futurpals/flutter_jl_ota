# Changelog
## \[1.0.4\]
### Added
- Add `stopScan`, `isOtaUpdateInProgress`, `getSdkVersion`, optional `deviceName`, and typed `OtaProgress` callbacks.
- Add Dart tests for MethodChannel calls and OTA progress parsing.

### Changed
- Sync bundled iOS JL OTA frameworks with the official `JL_OTA_Flutter` package: `JL_OTALib 2.3.1`, `JL_BLEKit 1.13.0`, `JL_AdvParse 1.1.1`, and `JL_HashPair 1.0.2`.
- Keep Android on the local newer `jl_bt_ota_V1.10.0_10932` AAR while adding official-inspired native methods.

### Fixed
- Register the iOS OTA progress callback before starting an update.
- Start Android OTA once the connection becomes ready instead of waiting for a second connection callback.

## \[1.0.3\]
### Fixed
- fix ios bug

## \[1.0.1\]
### Changed
- Android Update 1.10.0 sdk

## \[1.0.0\]
### Changed
- Android Update 1.10.0 sdk

## \[0.1.3\]
### Changed
- Android Update 1.10.0 sdk

## \[0.1.2\]
### Changed
- Clean project

## \[0.1.1\]
### Changed
- Clean project

## \[0.1.0\]
### Added
- Android Upgrade Test Successful

## \[0.0.9\]
### Fixed
- Fix Android Code

## \[0.0.8\]
### Changed
- Update README.md

## \[0.0.7\]
### Changed
- Update README.md

## \[0.0.6\]
### Fixed
- Fix Android Code

## \[0.0.5\]
### Added
- Ios Upgrade Test Successful

## \[0.0.4\]
### Fixed
- Fix Invoke error

## \[0.0.3\]
### Fixed
- Fix Invoke error

## \[0.0.2\]
### Fixed
- Fix Invoke error

## \[0.0.1\]
### Added
- Flutter JL OTA Initial Release
