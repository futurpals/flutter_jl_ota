package com.futurpals.flutter_jl_ota.tool;

import android.Manifest;
import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothProfile;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Environment;
import android.os.ParcelUuid;
import android.text.TextUtils;
import android.util.Log;

import androidx.core.app.ActivityCompat;

import com.futurpals.flutter_jl_ota.FlutterJlOtaPlugin;
import com.jieli.jl_bt_ota.constant.StateCode;
import com.jieli.jl_bt_ota.util.BluetoothUtil;
import com.jieli.jl_bt_ota.util.CHexConver;
import com.jieli.jl_bt_ota.util.JL_Log;


import java.io.File;
import java.lang.reflect.Method;
import java.util.Date;
import java.util.List;
import java.util.Locale;
import java.util.UUID;

/**
 * @author zqjasonZhong
 * @since 2020/7/16
 */
public class AppUtil {


    /**
     * Checks whether location permission is granted.
     *
     * @param context Android context.
     * @return true when permission is granted.
     */
    public static boolean isHasLocationPermission(Context context) {
        return isHasPermission(context, Manifest.permission.ACCESS_COARSE_LOCATION);
    }

    /**
     * Checks whether storage permission is granted.
     *
     * @param context Android context.
     * @return true when permission is granted.
     */
    public static boolean isHasStoragePermission(Context context) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            return isHasPermission(context, Manifest.permission.READ_EXTERNAL_STORAGE);
        }
        return isHasPermission(context, Manifest.permission.WRITE_EXTERNAL_STORAGE)
                && isHasPermission(context, Manifest.permission.READ_EXTERNAL_STORAGE);
    }

    /**
     * Checks whether Bluetooth connect permission is granted.
     *
     * @param context Android context.
     * @return true when permission is granted.
     */
    public static boolean checkHasConnectPermission(Context context) {
        if (Build.VERSION.SDK_INT >= 31) {
            return isHasPermission(context, "android.permission.BLUETOOTH_CONNECT");
        }
        return true;
    }

    /**
     * Checks whether Bluetooth scan permission is granted.
     *
     * @param context Android context.
     * @return true when permission is granted.
     */
    public static boolean checkHasScanPermission(Context context) {
        if (Build.VERSION.SDK_INT >= 31) {
            return isHasPermission(context, "android.permission.BLUETOOTH_SCAN");
        }
        return true;
    }

    /**
     * Checks whether the requested permission is granted.
     *
     * @param context    Android context.
     * @param permission Permission name. See {@link Manifest.permission}.
     * @return true when permission is granted.
     */
    public static boolean isHasPermission(Context context, String permission) {
        return context != null && ActivityCompat.checkSelfPermission(context, permission) == PackageManager.PERMISSION_GRANTED;
    }

    private static long lastClickTime = 0;
    private final static long DOUBLE_CLICK_INTERVAL = 2000; //2 s

    public static boolean isFastDoubleClick() {
        return isFastDoubleClick(DOUBLE_CLICK_INTERVAL);
    }

    public static boolean isFastDoubleClick(long interval) {
        boolean isDoubleClick = false;
        long currentTime = new Date().getTime();
        if (currentTime - lastClickTime <= interval) {
            isDoubleClick = true;
        }
        lastClickTime = currentTime;
        return isDoubleClick;
    }

    private static int clickCount = 0;

    public static int isFastContinuousClick() {
        return isFastContinuousClick(DOUBLE_CLICK_INTERVAL);
    }

    public static int isFastContinuousClick(long interval) {
        Log.d("ZHM", "isFastContinuousClick: " + clickCount);
        long currentTime = new Date().getTime();
        if (currentTime - lastClickTime <= interval) {
            clickCount++;
        } else { // The click interval is not continuous with the previous click.
            clickCount = 1;
        }
        lastClickTime = currentTime;
        return clickCount;
    }

    private static long theLastClickTime = 0;
    private static int theClickCount = 0;

    public static boolean isFastContinuousClick(long interval, int times) {
        long currentTime = new Date().getTime();
        if (currentTime - theLastClickTime <= interval) {
            theClickCount++;
        } else { // The click interval is not continuous with the previous click.
            theClickCount = 1;
        }
        theLastClickTime = currentTime;
        boolean state = theClickCount == times;
        if (state) {
            theLastClickTime = 0;
            theClickCount = 0;
        }
        return state;
    }

    @SuppressLint("MissingPermission")
    public static boolean enableBluetooth(Context context) {
        if (!checkHasConnectPermission(context)) return false;
        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (null == bluetoothAdapter) return false;
        boolean ret = bluetoothAdapter.isEnabled();
        if (!ret) {
            ret = bluetoothAdapter.enable();
        }
        return ret;
    }

    /**
     * Clears cached BLE device data.
     *
     * <p>Call this after the device disconnects and before resources are released.</p>
     *
     * @param bluetoothGatt Bluetooth GATT controller.
     * @return true when the cache refresh succeeds.
     */
    @SuppressLint("MissingPermission")
    public static boolean refreshBleDeviceCache(Context context, BluetoothGatt bluetoothGatt) {
        if (bluetoothGatt == null || !checkHasConnectPermission(context)) return false;
        try {
            Class<?> bluetoothGattClazz = bluetoothGatt.getClass();
            Method refreshMethod = bluetoothGattClazz.getMethod("refresh");
            return refreshMethod.invoke(bluetoothGatt) == Boolean.TRUE;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    @SuppressLint("MissingPermission")
    public static boolean deviceHasProfile(Context context, BluetoothDevice device, UUID uuid) {
        if (!BluetoothUtil.isBluetoothEnable() || null == device || null == uuid || TextUtils.isEmpty(uuid.toString())
                || !checkHasConnectPermission(context)) {
            return false;
        }
        ParcelUuid[] uuids = device.getUuids();
        if (uuids == null || uuids.length == 0) return false;
        for (ParcelUuid uid : uuids) {
            if (uuid.toString().toLowerCase(Locale.getDefault()).equalsIgnoreCase(uid.toString())) {
                return true;
            }
        }
        return false;
    }

    /**
     * Gets the device name.
     *
     * @param context Android context.
     * @param device  Bluetooth device.
     * @return Device name.
     */
    @SuppressLint("MissingPermission")
    public static String getDeviceName(Context context, BluetoothDevice device) {
        if (null == device || !checkHasConnectPermission(context)) return "N/A";
        String name = device.getName();
        if (TextUtils.isEmpty(name)) name = "N/A";
        return name;
    }

    /**
     * Gets the device type.
     *
     * @param context Android context.
     * @param device  Bluetooth device.
     * @return Device type.
     */
    @SuppressLint("MissingPermission")
    public static int getDeviceType(Context context, BluetoothDevice device) {
        if (null == device || !checkHasConnectPermission(context))
            return BluetoothDevice.DEVICE_TYPE_UNKNOWN;
        return device.getType();
    }

//    public static String printBtDeviceInfo(BluetoothDevice device) {
//        return BluetoothUtil.printBtDeviceInfo(FlutterJlOtaPlugin.getInstance().getContext(), device);
//    }

    /**
     * Prints BLE GATT service information.
     *
     * @param device BLE device.
     * @param gatt   GATT manager.
     * @param status Discovery status.
     */
    @SuppressLint("MissingPermission")
    public static void printBleGattServices(Context context, BluetoothDevice device, BluetoothGatt gatt, int status) {
        if (device == null || gatt == null || !checkHasConnectPermission(context))
            return;
        String TAG = "ble";
        if (JL_Log.isIsLog()) {
            JL_Log.d(TAG, String.format(Locale.getDefault(), "[[============================Bluetooth[%s], " +
                    "Discovery Services status[%d]=================================]]\n", BluetoothUtil.printBtDeviceInfo(context, device), status));
            List<BluetoothGattService> services = gatt.getServices();
            if (null != services) {
                JL_Log.d(TAG, "[[======Service Size:" + services.size() + "======================\n");
                for (BluetoothGattService service : services) {
                    if (null != service) {
                        JL_Log.d(TAG, "[[======Service:" + service.getUuid() + "======================\n");
                        List<BluetoothGattCharacteristic> characteristics = service.getCharacteristics();
                        if (null != characteristics) {
                            JL_Log.d(TAG, "[[[[=============characteristics Size:" + characteristics.size() + "======================\n");
                            for (BluetoothGattCharacteristic characteristic : characteristics) {
                                if (null != characteristic) {
                                    JL_Log.d(TAG, "[[[[=============characteristic:" + characteristic.getUuid()
                                            + ",write type : " + characteristic.getWriteType() + "======================\n");
                                    List<BluetoothGattDescriptor> descriptors = characteristic.getDescriptors();
                                    if (null != descriptors) {
                                        JL_Log.d(TAG, "[[[[[[=============descriptors Size:" + descriptors.size() + "======================\n");
                                        for (BluetoothGattDescriptor descriptor : descriptors) {
                                            if (null != descriptor) {
                                                JL_Log.d(TAG, "[[[[[[=============descriptor:" + descriptor.getUuid() + ",permission:" + descriptor.getPermissions()
                                                        + "\nvalue : " + CHexConver.byte2HexStr(descriptor.getValue()) + "======================\n");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            JL_Log.d(TAG, "[[============================Bluetooth[" + BluetoothUtil.printBtDeviceInfo(context, device) + "] Services show End=================================]]\n");
        }
    }

    /**
     * Converts Android connection states to OTA SDK connection states.
     *
     * @param status Android connection state.
     * @return OTA SDK connection state.
     */
    public static int changeConnectStatus(int status) {
        int changeStatus = StateCode.CONNECTION_DISCONNECT;
        switch (status) {
            case BluetoothProfile.STATE_CONNECTED: {
                changeStatus = StateCode.CONNECTION_OK;
                break;
            }
            case BluetoothProfile.STATE_CONNECTING: {
                changeStatus = StateCode.CONNECTION_CONNECTING;
                break;
            }
        }
        return changeStatus;
    }


}
