package com.futurpals.flutter_jl_ota.tool;



import android.annotation.SuppressLint;
import android.content.Context;
import android.content.SharedPreferences;
import androidx.annotation.IntRange;

import com.futurpals.flutter_jl_ota.FlutterJlOtaPlugin;

import io.flutter.Log;


/**
 * Configuration helper.
 *
 * @author zqjasonZhong
 * @since 2022/9/8
 * @email zhongzhuocheng@zh-jieli.com
 */
public class ConfigHelper {
    private static volatile ConfigHelper instance;
    private SharedPreferences preferences;
    private static Context appContext;

    private ConfigHelper(Context context) {
        preferences = context.getSharedPreferences("ota_config_data", Context.MODE_PRIVATE);
    }

    public static ConfigHelper getInstance() {
        if (instance == null) {
            synchronized (ConfigHelper.class) {
                if (instance == null) {
                    if (appContext != null) {
                        instance = new ConfigHelper(appContext);
                    } else {
                        Log.e("ConfigHelper", "Context is null when trying to getInstance()");
                        // Optionally, throw an exception or handle the error more gracefully
                    }
                }
            }
        }
        return instance;
    }

    public static void initialize(Context context) {
        if (appContext == null) {
            appContext = context.getApplicationContext(); // Use application context to avoid memory leaks
        }
    }

    private static final String KEY_COMMUNICATION_WAY = "communication_way";
    private static final String KEY_IS_USE_DEVICE_AUTH = "is_use_device_auth";
    private static final String KEY_IS_HID_DEVICE = "is_hid_device";
    private static final String KEY_USE_CUSTOM_RECONNECT_WAY = "use_custom_reconnect_way";
    private static final String KEY_BLE_MTU_VALUE = "ble_mtu_value";

    private static final String KEY_FAULT_TOLERANT = "fault_tolerant";
    private static final String KEY_FAULT_TOLERANT_COUNT = "fault_tolerant_count";
    private static final String KEY_SCAN_FILTER_STRING = "scan_filter_string";
    private static final String KEY_DEVELOP_MODE = "develop_mode";
    private static final String KEY_BROADCAST_BOX = "broadcast_box_switch";

    @SuppressLint("StaticFieldLeak")




    public boolean isBleWay() {
        return preferences.getInt(KEY_COMMUNICATION_WAY, OtaConstant.CURRENT_PROTOCOL) == OtaConstant.PROTOCOL_BLE;
    }

    public void setBleWay(boolean isBle) {
        int way = isBle ? OtaConstant.PROTOCOL_BLE : OtaConstant.PROTOCOL_SPP;
        preferences.edit().putInt(KEY_COMMUNICATION_WAY, way).apply();
    }

    public boolean isUseDeviceAuth() {
        return preferences.getBoolean(KEY_IS_USE_DEVICE_AUTH, OtaConstant.IS_NEED_DEVICE_AUTH);
    }

    public void setUseDeviceAuth(boolean isAuth) {
        preferences.edit().putBoolean(KEY_IS_USE_DEVICE_AUTH, isAuth).apply();
    }

    public boolean isHidDevice() {
        return preferences.getBoolean(KEY_IS_HID_DEVICE, OtaConstant.HID_DEVICE_WAY);
    }

    public void setHidDevice(boolean isHid) {
        preferences.edit().putBoolean(KEY_IS_HID_DEVICE, isHid).apply();
    }

    public boolean isUseCustomReConnectWay() {
        return preferences.getBoolean(KEY_USE_CUSTOM_RECONNECT_WAY, OtaConstant.NEED_CUSTOM_RECONNECT_WAY);
    }

    public void setUseCustomReConnectWay(boolean isCustom) {
        preferences.edit().putBoolean(KEY_USE_CUSTOM_RECONNECT_WAY, isCustom).apply();
    }

    public int getBleRequestMtu() {
        return preferences.getInt(KEY_BLE_MTU_VALUE, 509);
    }

    public void setBleRequestMtu(@IntRange(from = 20, to = 509) int mtu) {
        preferences.edit().putInt(KEY_BLE_MTU_VALUE, mtu).apply();
    }


    public boolean isFaultTolerant() {
        return preferences.getBoolean(KEY_FAULT_TOLERANT, OtaConstant.AUTO_FAULT_TOLERANT);
    }

    public void setFaultTolerant(boolean isFaultTolerant) {
        preferences.edit().putBoolean(KEY_FAULT_TOLERANT, isFaultTolerant).apply();
    }

    public int getFaultTolerantCount() {
        return preferences.getInt(KEY_FAULT_TOLERANT_COUNT, OtaConstant.AUTO_FAULT_TOLERANT_COUNT);
    }

    public void setFaultTolerantCount(int count) {
        if (!isFaultTolerant()) return;
        preferences.edit().putInt(KEY_FAULT_TOLERANT_COUNT, count).apply();
    }

    public String getScanFilter() {
        return preferences.getString(KEY_SCAN_FILTER_STRING, "");
    }

    public void setScanFilter(String scanFilter) {
        preferences.edit().putString(KEY_SCAN_FILTER_STRING, scanFilter).apply();
    }

    public boolean isDevelopMode() {
        return preferences.getBoolean(KEY_DEVELOP_MODE, false);
    }

    public void setDevelopMode(boolean developMode) {
        preferences.edit().putBoolean(KEY_DEVELOP_MODE, developMode).apply();
    }

    public boolean isEnableBroadcastBox() {
        return preferences.getBoolean(KEY_BROADCAST_BOX, false);
    }

    public void enableBroadcastBox(boolean enable) {
        preferences.edit().putBoolean(KEY_BROADCAST_BOX, enable).apply();
    }
}
