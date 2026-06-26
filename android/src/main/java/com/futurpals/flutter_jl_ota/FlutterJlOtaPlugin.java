package com.futurpals.flutter_jl_ota;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;

import androidx.annotation.NonNull;

import com.futurpals.flutter_jl_ota.tool.ConfigHelper;
import com.jieli.jl_bt_ota.constant.JL_Constant;
import com.jieli.jl_bt_ota.interfaces.IActionCallback;
import com.jieli.jl_bt_ota.interfaces.IUpgradeCallback;
import com.jieli.jl_bt_ota.model.BluetoothOTAConfigure;
import com.jieli.jl_bt_ota.model.base.BaseError;
import com.jieli.jl_bt_ota.model.response.TargetInfoResponse;

import java.util.HashMap;
import java.util.Locale;
import java.util.Map;


import io.flutter.embedding.engine.plugins.FlutterPlugin;
import io.flutter.embedding.engine.plugins.activity.ActivityAware;
import io.flutter.embedding.engine.plugins.activity.ActivityPluginBinding;
import io.flutter.plugin.common.MethodCall;
import io.flutter.plugin.common.MethodChannel;
import io.flutter.plugin.common.MethodChannel.MethodCallHandler;
import io.flutter.plugin.common.MethodChannel.Result;

/**
 * FlutterJlOtaPlugin
 * 改进后的 Flutter 插件，提供完整的 OTA 功能
 */
public class FlutterJlOtaPlugin implements FlutterPlugin, MethodCallHandler, ActivityAware {
    private static final String TAG = "FlutterJlOtaPlugin";
    private MethodChannel channel;
    private Context context;
    private OtaManager otaManager;
    private boolean otaStartRequested = false;

    @Override
    public void onAttachedToEngine(@NonNull FlutterPluginBinding flutterPluginBinding) {
        channel = new MethodChannel(flutterPluginBinding.getBinaryMessenger(), "flutter_jl_ota");
        channel.setMethodCallHandler(this);
        context = flutterPluginBinding.getApplicationContext();
        ConfigHelper.initialize(context); // 初始化 ConfigHelper
    }

    @Override
    public void onAttachedToActivity(@NonNull ActivityPluginBinding binding) {
    }

    @Override
    public void onDetachedFromActivityForConfigChanges() {
    }

    @Override
    public void onReattachedToActivityForConfigChanges(@NonNull ActivityPluginBinding binding) {
    }

    @Override
    public void onDetachedFromActivity() {
    }

    @Override
    public void onDetachedFromEngine(@NonNull FlutterPluginBinding binding) {
        if (otaManager != null) {
            otaManager.release();
            otaManager = null;
        }
        channel.setMethodCallHandler(null);
    }

    @SuppressLint("MissingPermission")
    @Override
    public void onMethodCall(@NonNull MethodCall call, @NonNull Result result) {
        switch (call.method) {
            case "getPlatformVersion":
                result.success("Android " + android.os.Build.VERSION.RELEASE);
                break;

            case "getSdkVersion":
                result.success(String.format(
                        Locale.US,
                        "V%s(%d)",
                        JL_Constant.getLibVersionName(),
                        JL_Constant.getLibVersionCode()
                ));
                break;

            case "isOta":
                result.success(otaManager != null && otaManager.isOTA());
                break;

            case "startScan":
                if (!ensureBluetoothAvailable(result)) return;
                initOtaManagerIfNeeded("", ""); // 初始化时无需特定 UUID 和名称
                otaManager.startLeScan(20 * 1000L); // 20秒超时
                result.success(true);
                break;

            case "stopScan":
                if (otaManager == null) {
                    result.success(false);
                    return;
                }
                otaManager.stopLeScan();
                result.success(true);
                break;

            case "connectDevice":
                if (!ensureBluetoothAvailable(result)) return;
                String uuid = call.argument("uuid");
                String deviceName = call.argument("deviceName");
                if (uuid != null && !uuid.isEmpty()) {
                    initOtaManagerIfNeeded(uuid, deviceName != null ? deviceName : "");
                    BluetoothDevice device = getBluetoothDeviceById(uuid);
                    if (device != null) {
                        otaManager.connectBluetoothDevice(device);
                        result.success(true);
                    } else {
                        result.error("DEVICE_NOT_FOUND", "Device with UUID " + uuid + " not found", null);
                    }
                } else {
                    result.error("INVALID_UUID", "UUID is invalid or empty", null);
                }
                break;

            case "getDeviceInfo":
                if (!ensureBluetoothAvailable(result)) return;
                if (otaManager == null) {
                    result.error("NOT_INITIALIZED", "OTA manager not initialized", null);
                    return;
                }
                otaManager.queryMandatoryUpdate(new IActionCallback<TargetInfoResponse>() {
                    @Override
                    public void onSuccess(TargetInfoResponse response) {
                        Log.d(TAG, "getDeviceInfo success, needForcedUpdate: " + true);
                        result.success(true);
                    }

                    @Override
                    public void onError(BaseError error) {
                        Log.e(TAG, "getDeviceInfo error: " + error.getMessage());
                        result.error("GET_DEVICE_INFO_FAILED", "Error getting device info: " + error.getMessage(), null);
                    }
                });
                break;

            case "startOtaUpdate":
                if (!ensureBluetoothAvailable(result)) return;
                String otaUuid = call.argument("uuid");
                String filePath = call.argument("filePath");
                String otaDeviceName = call.argument("deviceName");
                if (otaUuid != null && !otaUuid.isEmpty() && filePath != null && !filePath.isEmpty()) {
                    initOtaManagerIfNeeded(otaUuid, otaDeviceName != null ? otaDeviceName : "");
                    startOtaUpdate(otaUuid, filePath, result);
                } else {
                    result.error("INVALID_PARAMS", "UUID or filePath is invalid or empty", null);
                }
                break;

            case "cancelOtaUpdate":
                if (!ensureBluetoothAvailable(result)) return;
                if (otaManager == null) {
                    result.error("NOT_INITIALIZED", "OTA manager not initialized", null);
                    return;
                }
                otaManager.cancelOTA();
                result.success(true); // 双备份 OTA 支持取消
                break;

            default:
                result.notImplemented();
                break;
        }
    }

    private boolean ensureBluetoothAvailable(@NonNull Result result) {
        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (bluetoothAdapter == null || !bluetoothAdapter.isEnabled()) {
            result.error("BLUETOOTH_NOT_AVAILABLE", "Bluetooth is not available or not enabled", null);
            return false;
        }
        return true;
    }

    // 初始化 OtaManager，如果尚未初始化或需要更新 UUID
    private void initOtaManagerIfNeeded(String mac, String deviceName) {
        if (otaManager == null) {
            otaManager = new OtaManager(context, mac, deviceName);
            configureOtaManager();
            Log.d(TAG, "OtaManager initialized with mac: " + mac);
        } else if (!mac.isEmpty() && !otaManager.mac.equals(mac)) {
            otaManager.release();
            otaManager = new OtaManager(context, mac, deviceName);
            configureOtaManager();
            Log.d(TAG, "OtaManager reinitialized with new mac: " + mac);
        }
    }

    // 配置 OtaManager 的默认参数
    private void configureOtaManager() {
        BluetoothOTAConfigure config = BluetoothOTAConfigure.createDefault()
                .setPriority(BluetoothOTAConfigure.PREFER_BLE)
                .setUseAuthDevice(true)
                .setBleIntervalMs(500)
                .setTimeoutMs(3000)
                .setMtu(500)
                .setNeedChangeMtu(false)
                .setUseReconnect(true)
                .setFirmwareFilePath("");
        otaManager.configure(config);
    }

    // 开始 OTA 升级
    private void startOtaUpdate(String uuid, String filePath, Result result) {
        otaStartRequested = false;
        otaManager.setOtaStatusCallback(new OtaStatusCallback() {
            @Override
            public void onCanStartOtaChanged(boolean canStartOta) {
                if (!canStartOta || otaStartRequested || otaManager.isOTA()) return;

                otaStartRequested = true;
                Log.d(TAG, "OTA connection is ready, starting upgrade for: " + uuid);
                startOtaWithFile(filePath);

                otaManager.queryMandatoryUpdate(new IActionCallback<TargetInfoResponse>() {
                    @Override
                    public void onSuccess(TargetInfoResponse deviceInfo) {
                        Log.d(TAG, "queryMandatoryUpdate success");
                    }

                    @Override
                    public void onError(BaseError baseError) {
                        Log.e(TAG, "queryMandatoryUpdate error: " + baseError);
                    }
                });
            }
        });
        result.success(true);
    }

    private void startOtaWithFile(String filePath) {
        Log.i(TAG, "Start to Set: " + filePath);
        otaManager.getBluetoothOption().setFirmwareFilePath(filePath);
        otaManager.startOTA(new IUpgradeCallback() {
            @Override
            public void onStartOTA() {
                Log.d(TAG, "OTA started");
                invokeProgress(0, "STARTED");
            }

            @Override
            public void onNeedReconnect(String addr, boolean isNewReconnectWay) {
                if (otaManager.getBluetoothOption().isUseReconnect()) {
                    Log.d(TAG, "Reconnecting to: " + addr + ", new way: " + isNewReconnectWay);
                    otaManager.reConnect(addr, isNewReconnectWay);
                }
            }

            @Override
            public void onProgress(int type, float progress) {
                int progressInt = (int) progress;
                String status = type == 0 ? "DOWNLOADING_LOADER" : "UPGRADING_FIRMWARE";
                Log.d(TAG, "OTA progress: " + progressInt + "%, type: " + type);
                invokeProgress(progressInt, status);
            }

            @Override
            public void onStopOTA() {
                Log.d(TAG, "OTA completed");
                invokeProgress(100, "COMPLETED");
                otaStartRequested = false;
                otaManager.release();
            }

            @Override
            public void onCancelOTA() {
                Log.d(TAG, "OTA canceled");
                if (otaManager.isOTA()) {
                    otaManager.cancelOTA();
                }
                otaStartRequested = false;
                invokeProgress(0, "CANCELED");
            }

            @Override
            public void onError(BaseError error) {
                Log.e(TAG, "OTA error: " + error.getMessage());
                otaStartRequested = false;
                invokeProgress(0, "ERROR: " + error.getMessage());
            }
        });
    }


    // 通过 MethodChannel 发送进度更新
    private void invokeProgress(int progress, String status) {
        new Handler(Looper.getMainLooper()).post(() -> {
            Map<String, Object> response = new HashMap<>();
            response.put("progress", progress);
            response.put("status", status);
            channel.invokeMethod("otaProgress", response);
        });
    }

    @SuppressLint("MissingPermission")
    private BluetoothDevice getBluetoothDeviceById(String remoteID) {
        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        try {
            return bluetoothAdapter.getRemoteDevice(remoteID);
        } catch (IllegalArgumentException e) {
            Log.e(TAG, "Invalid remoteID: " + remoteID, e);
            return null;
        }
    }
}
