package com.futurpals.flutter_jl_ota.ble.model;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.content.Context;

import androidx.annotation.NonNull;

import com.futurpals.flutter_jl_ota.ble.SendBleDataThread;
import com.futurpals.flutter_jl_ota.ble.interfaces.IBleOp;
import com.futurpals.flutter_jl_ota.ble.interfaces.OnThreadStateListener;
import com.futurpals.flutter_jl_ota.ble.interfaces.OnWriteDataCallback;
import com.futurpals.flutter_jl_ota.tool.AppUtil;
import com.jieli.jl_bt_ota.constant.BluetoothConstant;
import com.jieli.jl_bt_ota.util.CHexConver;
import com.jieli.jl_bt_ota.util.JL_Log;

import java.util.UUID;

/**
 * @author zqjasonZhong
 * @email zhongzhuocheng@zh-jieli.com
 * @desc BLE device.
 * @since 2022/12/5
 */
public class BleDevice {
    private final String tag = "BleManager";
    private final Context context;                    // Context.
    private final BluetoothGatt gatt;                 // BLE GATT controller.
    private int mtu = BluetoothConstant.BLE_MTU_MIN;  //MTU
    private long connectedTime;                       // Connection timestamp.

    private SendBleDataThread sendDataThread;         // Data sending thread.

    public BleDevice(@NonNull Context context, @NonNull BluetoothGatt gatt) {
        this.context = context;
        this.gatt = gatt;
    }

    @NonNull
    public BluetoothGatt getGatt() {
        return gatt;
    }

    public int getMtu() {
        int realMtu = mtu;
        if (realMtu > 128) {
            realMtu -= 6;
        }
        return realMtu;
    }

    public void setMtu(int mtu) {
        this.mtu = mtu;
    }

    public long getConnectedTime() {
        return connectedTime;
    }

    public void setConnectedTime(long connectedTime) {
        this.connectedTime = connectedTime;
    }

    public void startSendDataThread() {
        if (sendDataThread == null || !sendDataThread.isRunning()) {
            sendDataThread = new SendBleDataThread(new IBleOp() {
                @Override
                public int getBleMtu() {
                    return getMtu();
                }

                @Override
                public boolean writeDataByBle(BluetoothGatt gatt, UUID serviceUUID, UUID characteristicUUID, byte[] data) {
                    return writeDataToDeviceByBle(gatt, serviceUUID, characteristicUUID, data);
                }
            }, new OnThreadStateListener() {
                @Override
                public void onStart(long id, String name) {

                }

                @Override
                public void onEnd(long id, String name) {
                    if (sendDataThread != null && sendDataThread.getId() == id) {
                        sendDataThread = null;
                    }
                }
            });
            sendDataThread.start();
        }
    }

    public void stopSendDataThread() {
        if (sendDataThread != null) {
            sendDataThread.stopThread();
        }
    }

    public void wakeupSendThread(SendBleDataThread.BleSendTask task) {
        if (sendDataThread != null && task != null && gatt.equals(task.getBleGatt())) {
            sendDataThread.wakeupSendThread(task);
        }
    }

    public boolean addSendTask(UUID serviceUUID, UUID characteristicUUID, byte[] data, OnWriteDataCallback callback) {
        boolean ret = false;
        if (sendDataThread != null && sendDataThread.isRunning()) {
            ret = sendDataThread.addSendTask(gatt, serviceUUID, characteristicUUID, data, callback);
        }
        return ret;
    }

    @SuppressLint("MissingPermission")
    private boolean writeDataToDeviceByBle(BluetoothGatt gatt, UUID serviceUUID, UUID characteristicUUID, byte[] data) {
        if (gatt == null || null == serviceUUID || null == characteristicUUID || null == data || data.length == 0
                || !AppUtil.checkHasConnectPermission(this.context)) {
            JL_Log.d(tag, "writeDataByBle : param is invalid.");
            return false;
        }
        BluetoothGattService gattService = gatt.getService(serviceUUID);
        if (null == gattService) {
            JL_Log.d(tag, "writeDataByBle : service is null.");
            return false;
        }
        BluetoothGattCharacteristic gattCharacteristic = gattService.getCharacteristic(characteristicUUID);
        if (null == gattCharacteristic) {
            JL_Log.d(tag, "writeDataByBle : characteristic is null");
            return false;
        }
        boolean ret = false;
        try {
            gattCharacteristic.setValue(data);
            ret = gatt.writeCharacteristic(gattCharacteristic);
        } catch (Exception e) {
            e.printStackTrace();
        }
        JL_Log.d(tag, "writeDataByBle : send ret : " + ret + ", data = " + CHexConver.byte2HexStr(data));
        return ret;
    }

    @Override
    public String toString() {
        return "BleDevice{" +
                "context=" + context +
                ", gatt=" + gatt +
                ", mtu=" + mtu +
                ", connectedTime=" + connectedTime +
                ", sendDataThread=" + sendDataThread +
                '}';
    }
}
