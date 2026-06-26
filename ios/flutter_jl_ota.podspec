#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html.
# Run `pod lib lint flutter_jl_ota.podspec` to validate before publishing.
#
Pod::Spec.new do |s|
  s.name             = 'flutter_jl_ota'
  s.version          = '1.0.4'
  s.summary          = 'A Flutter plugin for Over-The-Air (OTA) firmware updates targeting JL chipsets.'
  s.description      = <<-DESC
A Flutter plugin for Over-The-Air (OTA) firmware updates targeting JL (JieLi) chipsets. Supports Android and iOS platforms with progress callbacks and error handling.
                       DESC
  s.homepage         = 'https://github.com/futurpals/flutter_jl_ota'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'futurpals' => 'https://github.com/futurpals' }
  s.source           = { :path => '.' }
  s.source_files = 'Classes/**/*.{h,m,swift}'
  s.dependency 'Flutter'
  s.platform = :ios, '12.0'

  s.static_framework = true

  s.framework = 'CoreBluetooth'
  s.resource_bundles = {
    'flutter_jl_ota_privacy' => ['Resources/PrivacyInfo.xcprivacy']
  }

  s.ios.vendored_frameworks = [
    'Framework/JL_OTALib.framework',
    'Framework/JL_AdvParse.framework',
    'Framework/JL_HashPair.framework',
    'Framework/JL_BLEKit.framework',
    'Framework/DFUnits.framework',
    'Framework/JLLogHelper.framework'
  ]

  # Flutter.framework does not contain a i386 slice.
  s.pod_target_xcconfig = { 'DEFINES_MODULE' => 'YES', 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386' }
  s.swift_version = '5.0'
end
