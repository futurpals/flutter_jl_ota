package com.futurpals.flutter_jl_ota.ble.interfaces;

import android.bluetooth.BluetoothDevice;

import java.util.UUID;

/**
 * Write result callback.
 *
 * @author zqjasonZhong
 * @date 2019/9/25
 */
public interface OnWriteDataCallback {

    /**
     * Reports the BLE write result.
     *
     * @param device             Bluetooth device.
     * @param serviceUUID        Service UUID.
     * @param characteristicUUID Characteristic UUID.
     * @param result             Send result.
     * @param data               Sent data.
     */
    void onBleResult(BluetoothDevice device, UUID serviceUUID, UUID characteristicUUID, boolean result, byte[] data);
}
