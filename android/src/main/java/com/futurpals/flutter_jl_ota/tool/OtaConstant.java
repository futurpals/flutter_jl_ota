package com.futurpals.flutter_jl_ota.tool;

import java.util.UUID;

/**
 * Constant declarations.
 *
 * @author zqjasonZhong
 * @date 2019/12/30
 */
public class OtaConstant {

    public static final UUID UUID_A2DP = UUID.fromString("0000110b-0000-1000-8000-00805f9b34fb");
    public static final UUID UUID_SPP = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");

    // BLE protocol.
    public static final int PROTOCOL_BLE = 0;
    // SPP protocol.
    public static final int PROTOCOL_SPP = 1;

    public static final int CURRENT_PROTOCOL = PROTOCOL_BLE;

    // Whether device authentication is required.
    public static final boolean IS_NEED_DEVICE_AUTH = true;

    // Whether HID device connection is used.
    public static final boolean HID_DEVICE_WAY = false;

    // Whether a custom reconnect flow is required.
    public static final boolean NEED_CUSTOM_RECONNECT_WAY = false;

    // Whether SPP multi-channel connection is used.
    public static final boolean USE_SPP_MULTIPLE_CHANNEL = false;

    // Whether automated OTA testing is enabled.
    public static final boolean AUTO_TEST_OTA = false;
    // Automated OTA test count.
    public static final int AUTO_TEST_COUNT = 30;

    // Whether automated testing allows fault tolerance.
    public static final boolean AUTO_FAULT_TOLERANT = false;
    // Fault tolerance retry count.
    public static final int AUTO_FAULT_TOLERANT_COUNT = 1;

    // dir
    public static final String DIR_ROOT = "JieLiOTA";
    public static final String DIR_UPGRADE = "upgrade";
    public static final String DIR_LOGCAT = "logcat";

    public static final long SCAN_TIMEOUT = 16 * 1000L;
}
