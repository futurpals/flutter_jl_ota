package com.futurpals.flutter_jl_ota.ble.interfaces;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGattService;


import com.futurpals.flutter_jl_ota.ble.model.BleScanInfo;

import java.util.List;
import java.util.UUID;

/**
 * BLE event callback base class.
 *
 * @author zqjasonZhong
 * @since 2020/7/16
 */
public abstract class BleEventCallback implements IBleEventCallback {

    @Override
    public void onAdapterChange(boolean bEnabled) {

    }

    @Override
    public void onDiscoveryBleChange(boolean bStart) {

    }

    @Override
    public void onDiscoveryBle(BluetoothDevice device, BleScanInfo bleScanMessage) {

    }

    @Override
    public void onBleConnection(BluetoothDevice device, int status) {

    }

    @Override
    public void onBleServiceDiscovery(BluetoothDevice device, int status, List<BluetoothGattService> services) {

    }

    @Override
    public void onBleNotificationStatus(BluetoothDevice device, UUID serviceUuid, UUID characteristicUuid, int status) {

    }

    @Override
    public void onBleDataBlockChanged(BluetoothDevice device, int block, int status) {

    }

    @Override
    public void onBleDataNotification(BluetoothDevice device, UUID serviceUuid, UUID characteristicsUuid, byte[] data) {

    }

    @Override
    public void onBleWriteStatus(BluetoothDevice device, UUID serviceUuid, UUID characteristicsUuid, byte[] data, int status) {

    }

    @Override
    public void onConnectionUpdated(BluetoothDevice device, int interval, int latency, int timeout, int status) {

    }
}
