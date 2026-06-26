package com.futurpals.flutter_jl_ota;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothProfile;
import android.content.Context;
import android.util.Log;

import com.futurpals.flutter_jl_ota.ble.BleManager;
import com.futurpals.flutter_jl_ota.ble.interfaces.BleEventCallback;
import com.futurpals.flutter_jl_ota.ble.interfaces.OnWriteDataCallback;
import com.jieli.jl_bt_ota.constant.StateCode;
import com.jieli.jl_bt_ota.impl.BluetoothOTAManager;
import com.jieli.jl_bt_ota.util.JL_Log;

import java.util.UUID;

public class OtaManager extends BluetoothOTAManager {
    private static final String TAG = "OtaManager";
    private static final long SCAN_TIMEOUT = 20 * 1000L; // 20秒扫描超时

    private final Context context;
    private final BleManager bleManager;
    public String mac;
    public String deviceName;
    private OtaStatusCallback otaStatusCallback;
    private boolean canStartOta = false;

    public OtaManager(Context context, String mac, String deviceName) {
        super(context);
        if (context == null) {
            throw new IllegalStateException("Context is required to initialize OtaManager");
        }
        this.context = context;
        this.mac = mac;
        this.deviceName = deviceName != null ? deviceName : "";
        this.bleManager = new BleManager(context, mac, this.deviceName);
        Log.d(TAG, "Initialized with mac: " + mac + ", deviceName: " + deviceName);

        // 启动扫描
        startLeScan(SCAN_TIMEOUT);

        // 注册 BLE 事件回调
        registerBleEventCallback();
    }

    // 启动 BLE 扫描
    public void startLeScan(long timeout) {
        try {
            bleManager.startLeScan(timeout);
            Log.d(TAG, "Started BLE scan with timeout: " + timeout + "ms");
        } catch (Exception e) {
            Log.e(TAG, "Failed to start BLE scan: " + e.getMessage(), e);
        }
    }

    public void stopLeScan() {
        try {
            bleManager.stopLeScan();
            Log.d(TAG, "Stopped BLE scan");
        } catch (Exception e) {
            Log.e(TAG, "Failed to stop BLE scan: " + e.getMessage(), e);
        }
    }

    // 注册 BLE 事件回调
    private void registerBleEventCallback() {
        bleManager.registerBleEventCallback(new BleEventCallback() {
            @Override
            public void onBleConnection(BluetoothDevice device, int status) {
                int connectStatus = changeConnectStatus(status);
                JL_Log.d(TAG, "onBleConnection - device: " + device.getAddress() + ", status: " + connectStatus);

                // 传递设备连接状态
                onBtDeviceConnection(device, connectStatus);

                // 更新 OTA 可开始状态
                if (connectStatus == StateCode.CONNECTION_OK) {
                    setCanStartOta(true);
                } else if (connectStatus == StateCode.CONNECTION_DISCONNECT) {
                    setCanStartOta(false);
                }
            }

            @Override
            public void onBleDataNotification(BluetoothDevice device, UUID serviceUuid, UUID characteristicsUuid, byte[] data) {
                Log.d(TAG, "onBleDataNotification - device: " + device.getAddress() + ", data length: " + (data != null ? data.length : 0));
                onReceiveDeviceData(device, data);
            }

            @Override
            public void onBleDataBlockChanged(BluetoothDevice device, int block, int status) {
                Log.d(TAG, "onBleDataBlockChanged - device: " + device.getAddress() + ", block: " + block + ", status: " + status);
                onMtuChanged(getConnectedBluetoothGatt(), block, status);
            }
        });
    }

    // 设置 OTA 可开始状态
    private void setCanStartOta(boolean canStart) {
        if (this.canStartOta != canStart) {
            this.canStartOta = canStart;
            Log.d(TAG, "OTA canStart updated: " + canStart);
            if (otaStatusCallback != null) {
                otaStatusCallback.onCanStartOtaChanged(canStart);
            }
        }
    }

    // 设置 OTA 状态回调
    public void setOtaStatusCallback(OtaStatusCallback callback) {
        this.otaStatusCallback = callback;
        // 初始化时立即通知当前状态
        if (callback != null) {
            callback.onCanStartOtaChanged(canStartOta);
        }
    }

    @Override
    public BluetoothDevice getConnectedDevice() {
        BluetoothDevice device = bleManager.getConnectedBtDevice();
        Log.d(TAG, "getConnectedDevice: " + (device != null ? device.getAddress() : "null"));
        return device;
    }

    @Override
    public BluetoothGatt getConnectedBluetoothGatt() {
        BluetoothDevice device = getConnectedDevice();
        BluetoothGatt gatt = device != null ? bleManager.getConnectedBtGatt(device) : null;
        Log.d(TAG, "getConnectedBluetoothGatt: " + (gatt != null ? "available" : "null"));
        return gatt;
    }

    @Override
    public void connectBluetoothDevice(BluetoothDevice device) {
        if (device == null) {
            Log.w(TAG, "connectBluetoothDevice: device is null");
            return;
        }
        try {
            boolean success = bleManager.connectBleDevice(device);
            Log.d(TAG, "connectBluetoothDevice - device: " + device.getAddress() + ", success: " + success);
        } catch (Exception e) {
            Log.e(TAG, "Failed to connect device: " + device.getAddress() + ", error: " + e.getMessage(), e);
        }
    }

    public void reConnect(String address, boolean isUseAdv) {
        if (address == null || address.isEmpty()) {
            Log.w(TAG, "reConnect: address is invalid");
            return;
        }
        try {
            bleManager.reconnectDevice(address, isUseAdv);
        } catch (Exception e) {
            Log.e(TAG, "Failed to reconnect: " + e.getMessage(), e);
        }
    }

    @Override
    public void disconnectBluetoothDevice(BluetoothDevice device) {
        if (device == null) {
            Log.w(TAG, "disconnectBluetoothDevice: device is null");
            return;
        }
        try {
            bleManager.disconnectBleDevice(device);
            Log.d(TAG, "disconnectBluetoothDevice - device: " + device.getAddress());
        } catch (Exception e) {
            Log.e(TAG, "Failed to disconnect device: " + device.getAddress() + ", error: " + e.getMessage(), e);
        }
    }

    @Override
    public boolean sendDataToDevice(BluetoothDevice device, byte[] data) {
        if (device == null || data == null || data.length == 0) {
            Log.w(TAG, "sendDataToDevice: invalid parameters - device: " + device + ", data length: " + (data != null ? data.length : 0));
            return false;
        }
        try {
            bleManager.writeDataByBleAsync(device, BleManager.BLE_UUID_SERVICE, BleManager.BLE_UUID_WRITE, data, new OnWriteDataCallback() {
                @Override
                public void onBleResult(BluetoothDevice device, UUID serviceUUID, UUID characteristicUUID, boolean result, byte[] data) {
                    Log.d(TAG, "sendDataToDevice result - device: " + device.getAddress() + ", success: " + result);
                }
            });
            return true;
        } catch (Exception e) {
            Log.e(TAG, "Failed to send data to device: " + device.getAddress() + ", error: " + e.getMessage(), e);
            return false;
        }
    }

    @Override
    public void release() {
        super.release();
        try {
            bleManager.destroy();
            canStartOta = false;
            mac = "";
            deviceName = "";
            otaStatusCallback = null;
            Log.d(TAG, "Resources released");
        } catch (Exception e) {
            Log.e(TAG, "Failed to release resources: " + e.getMessage(), e);
        }
    }

    private int changeConnectStatus(int status) {
        switch (status) {
            case BluetoothProfile.STATE_CONNECTED:
                return StateCode.CONNECTION_OK;
            case BluetoothProfile.STATE_CONNECTING:
                return StateCode.CONNECTION_CONNECTING;
            case BluetoothProfile.STATE_DISCONNECTED:
            case BluetoothProfile.STATE_DISCONNECTING:
            default:
                return StateCode.CONNECTION_DISCONNECT;
        }
    }
}
