package com.futurpals.flutter_jl_ota.ble.interfaces;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGattService;


import com.futurpals.flutter_jl_ota.ble.model.BleScanInfo;

import java.util.List;
import java.util.UUID;

/**
 * BLE event callback.
 *
 * @author zqjasonZhong
 * @since 2020/7/16
 */
public interface IBleEventCallback {

    /**
     * Bluetooth adapter state callback.
     *
     * @param bEnabled Enabled state.
     */
    void onAdapterChange(boolean bEnabled);

    /**
     * Bluetooth scan state callback.
     *
     * @param bStart Scan state.
     */
    void onDiscoveryBleChange(boolean bStart);

    /**
     * Bluetooth device discovery callback.
     *
     * @param device      Bluetooth device.
     * @param bleScanInfo BLE scan data.
     */
    void onDiscoveryBle(BluetoothDevice device, BleScanInfo bleScanInfo);

    /**
     * BLE connection state callback.
     *
     * @param device Bluetooth device.
     * @param status Connection state.
     */
    void onBleConnection(BluetoothDevice device, int status);

    /**
     * BLE service discovery callback.
     *
     * @param device   Bluetooth device.
     * @param status   Status.
     * @param services Service list.
     */
    void onBleServiceDiscovery(BluetoothDevice device, int status, List<BluetoothGattService> services);

    /**
     * BLE characteristic state callback.
     *
     * @param device             Bluetooth device.
     * @param serviceUuid        Service UUID.
     * @param characteristicUuid Characteristic UUID.
     * @param status             Status.
     */
    void onBleNotificationStatus(BluetoothDevice device, UUID serviceUuid, UUID characteristicUuid, int status);

    /**
     * BLE MTU change callback.
     *
     * @param device Bluetooth device.
     * @param block  Negotiated MTU.
     * @param status Status.
     */
    void onBleDataBlockChanged(BluetoothDevice device, int block, int status);

    /**
     * BLE data callback.
     *
     * @param device              Bluetooth device.
     * @param serviceUuid         Service UUID.
     * @param characteristicsUuid Characteristic UUID.
     * @param data                Data.
     */
    void onBleDataNotification(BluetoothDevice device, UUID serviceUuid, UUID characteristicsUuid, byte[] data);

    /**
     * BLE write callback.
     *
     * @param device              Bluetooth device.
     * @param serviceUuid         Service UUID.
     * @param characteristicsUuid Characteristic UUID.
     * @param data                Data.
     * @param status              Status.
     */
    void onBleWriteStatus(BluetoothDevice device, UUID serviceUuid, UUID characteristicsUuid, byte[] data, int status);

    /**
     * BLE connection parameter callback.
     *
     * @param device   Bluetooth device.
     * @param interval Packet interval.
     * @param latency  Latency parameter.
     * @param timeout  Timeout.
     * @param status   Status.
     */
    void onConnectionUpdated(BluetoothDevice device, int interval, int latency, int timeout, int status);
}
