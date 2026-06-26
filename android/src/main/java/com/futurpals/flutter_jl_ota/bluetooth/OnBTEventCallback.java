package com.futurpals.flutter_jl_ota.bluetooth;
import android.bluetooth.BluetoothDevice;

import com.futurpals.flutter_jl_ota.ble.model.BleScanInfo;

import java.util.UUID;

/**
 * @author zqjasonZhong
 * @since 2022/9/14
 * @email zhongzhuocheng@zh-jieli.com
 * @desc Bluetooth event callback.
 */
public class OnBTEventCallback {

    public void onAdapterChange(boolean bEnabled) {
        // Default implementation (empty)
    }

    public void onDiscoveryChange(boolean bStart, int scanType) {
        // Default implementation (empty)
    }

    public void onDiscovery(BluetoothDevice device, BleScanInfo bleScanMessage) {
        // Default implementation (empty)
    }

    public void onDeviceConnection(BluetoothDevice device, int way, int status) {
        // Default implementation (empty)
    }

    public void onReceiveData(BluetoothDevice device, int way, UUID uuid, byte[] data) {
        // Default implementation (empty)
    }

    public void onBleMtuChange(BluetoothDevice device, int mtu, int status) {
        // Default implementation (empty)
    }
}