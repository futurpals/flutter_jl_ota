package com.futurpals.flutter_jl_ota.ble;

import static android.os.Build.VERSION_CODES.LOLLIPOP;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.le.BluetoothLeScanner;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.bluetooth.le.ScanSettings;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Build;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.os.SystemClock;
import android.text.TextUtils;
import android.util.Log;

import androidx.annotation.NonNull;

import com.futurpals.flutter_jl_ota.BleConnectedCallBack;

import com.futurpals.flutter_jl_ota.ReConnectHelper;
import com.futurpals.flutter_jl_ota.ble.interfaces.BleEventCallback;
import com.futurpals.flutter_jl_ota.ble.interfaces.OnWriteDataCallback;
import com.futurpals.flutter_jl_ota.ble.model.BleDevice;
import com.futurpals.flutter_jl_ota.ble.model.BleScanInfo;
import com.futurpals.flutter_jl_ota.tool.AppUtil;
//import com.example.jl_ota.tool.ConfigHelper;
import com.futurpals.flutter_jl_ota.tool.ConfigHelper;
import com.jieli.jl_bt_ota.constant.BluetoothConstant;
import com.jieli.jl_bt_ota.util.BluetoothUtil;
import com.jieli.jl_bt_ota.util.CHexConver;
import com.jieli.jl_bt_ota.util.JL_Log;


import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.UUID;


/**
 * BLE connection manager.
 *
 * @author zqjasonZhong
 * @since 2020/7/16
 */
public class BleManager {
    private final static String TAG = BleManager.class.getSimpleName();
    private final Context mContext;
    @SuppressLint("StaticFieldLeak")
    private volatile static BleManager instance;
    private final ConfigHelper configHelper = ConfigHelper.getInstance();

    // Gets the BleManager instance with a Context.
    public static BleManager getInstance(Context context, String m_mac, String d_deviceName) {
        if (instance == null) {
            synchronized (BleManager.class) {
                if (instance == null) {
                    // Pass the Context into the constructor and keep it non-null.
                    if (context == null) {
                        throw new IllegalStateException("Context is required to initialize BleManager");
                    }
                    instance = new BleManager(context.getApplicationContext(), m_mac, d_deviceName); // Use the application Context.
                    JL_Log.w(TAG, "init BleManager.. " + instance);

                }
            }
        }
        return instance;
    }

    public String mac = "";
    public String deviceName = "";

    public BleManager(Context context, String m_mac, String d_deviceNmae) {

        this.mContext = context;
        if (context == null) {
            throw new IllegalArgumentException("Context cannot be null");
        }
        this.mac = m_mac;
        this.deviceName = d_deviceNmae;

        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (Build.VERSION.SDK_INT >= LOLLIPOP && mBluetoothAdapter != null) {
            mBluetoothLeScanner = mBluetoothAdapter.getBluetoothLeScanner();
            Log.e(TAG, "mBluetoothLeScanner==" + mBluetoothLeScanner);

        }
        mReConnectHelper = new ReConnectHelper(context, this);

        registerReceiver();
    }

    private BaseBtAdapterReceiver mAdapterReceiver;
    private final BluetoothAdapter mBluetoothAdapter;
    private BluetoothLeScanner mBluetoothLeScanner;


    private volatile BluetoothDevice mConnectingBtDevice;     // Device being connected.
    private volatile BluetoothDevice mUsingDevice;            // Device currently in use.

    private final Map<String, BleDevice> mConnectedGattMap = new HashMap<>();
    private final List<BluetoothDevice> mDiscoveredBleDevices = new ArrayList<>();
    private final BleEventCallbackManager mCallbackManager = new BleEventCallbackManager();

    private volatile boolean isBleScanning;
    public boolean isConnected = false;
    private NotifyCharacteristicRunnable mNotifyCharacteristicRunnable;

    private int mRetryConnectCount = 0;// Retry count after connection failures.
    private long startConnectTime = 0; // Connection start timestamp.
    private final static int MAX_RETRY_CONNECT_COUNT = 1;// Maximum connection retry count.
    private final static int MIN_CONNECT_TIME = 5 * 1000; // Minimum connection timeout.
    // BLE service UUID.
    public final static UUID BLE_UUID_SERVICE = BluetoothConstant.UUID_SERVICE;
    // BLE write characteristic UUID.
    public final static UUID BLE_UUID_WRITE = BluetoothConstant.UUID_WRITE;
    // BLE notify characteristic UUID.
    public final static UUID BLE_UUID_NOTIFICATION = BluetoothConstant.UUID_NOTIFICATION;
    // BLE notify descriptor UUID.
    public final static UUID BLE_UUID_NOTIFICATION_DESCRIPTOR = UUID.fromString("00002902-0000-1000-8000-00805F9B34FB");

    /**
     * Maximum data send timeout: 8 seconds.
     */
    public final static int SEND_DATA_MAX_TIMEOUT = 8000; //8 s
    private final static int SCAN_BLE_TIMEOUT = 12 * 1000;  // Recommended minimum BLE scan time.
    private final static int CONNECT_BLE_TIMEOUT = 40 * 1000;
    private final ReConnectHelper mReConnectHelper;

    private final static int CALLBACK_TIMEOUT = 6000;
    private final static int RECONNECT_BLE_DELAY = 2000;

    private final static int MSG_SCAN_BLE_TIMEOUT = 0x1010;
    private final static int MSG_CONNECT_BLE_TIMEOUT = 0x1011;
    private final static int MSG_SCAN_HID_DEVICE = 0X1012;
    private final static int MSG_NOTIFY_BLE_TIMEOUT = 0x1013;
    private final static int MSG_CHANGE_BLE_MTU_TIMEOUT = 0x1014;
    private final static int MSG_BLE_DISCOVER_SERVICES_CALLBACK_TIMEOUT = 0x1015;

    private final Handler mHandler = new Handler(Looper.getMainLooper(), new Handler.Callback() {
        @Override
        public boolean handleMessage(@NonNull Message msg) {
            switch (msg.what) {
                case MSG_SCAN_BLE_TIMEOUT:

                    if (isBleScanning) {
                        stopLeScan();
                    }
                    break;
                case MSG_CONNECT_BLE_TIMEOUT: {
                    if (msg.obj instanceof BluetoothDevice) {
                        BluetoothDevice device = (BluetoothDevice) msg.obj;
                        BleDevice bleDevice = getConnectedBle(device);
                        if (null == bleDevice) {
                            handleBleConnection(device, BluetoothProfile.STATE_DISCONNECTED);
                        }
                        setConnectingBtDevice(null);
                    }
                    break;
                }
                case MSG_SCAN_HID_DEVICE: {
                    List<BluetoothDevice> lists = BluetoothUtil.getSystemConnectedBtDeviceList(mContext);
                    if (null != lists && AppUtil.checkHasConnectPermission(mContext)) {
                        for (BluetoothDevice device : lists) {
                            if (device.getType() != BluetoothDevice.DEVICE_TYPE_CLASSIC &&
                                    device.getBondState() == BluetoothDevice.BOND_BONDED) {
                                handleDiscoveryBle(device, null);
                            }
                        }
                    }
                    mHandler.sendEmptyMessageDelayed(MSG_SCAN_HID_DEVICE, 1000);
                    break;
                }
                case MSG_NOTIFY_BLE_TIMEOUT: {
                    if (msg.obj instanceof BluetoothDevice) {
                        BluetoothDevice device = (BluetoothDevice) msg.obj;
                        disconnectBleDevice(device);
                    }
                    break;
                }
                case MSG_CHANGE_BLE_MTU_TIMEOUT: {
                    BluetoothDevice device = (BluetoothDevice) msg.obj;
                    BleDevice bleDevice = getConnectedBle(device);
                    JL_Log.i(TAG, "-MSG_CHANGE_BLE_MTU_TIMEOUT- request mtu timeout, device : " + printDeviceInfo(device) + ", " + bleDevice);
                    if (bleDevice != null) {
                        handleBleConnectedEvent(device);
                    } else {
                        handleBleConnection(device, BluetoothProfile.STATE_DISCONNECTED);
                    }
                    break;
                }
                case MSG_BLE_DISCOVER_SERVICES_CALLBACK_TIMEOUT:
                    if (msg.obj instanceof BluetoothDevice) {
                        BluetoothDevice connectedBleDev = (BluetoothDevice) msg.obj;
                        if (BluetoothUtil.deviceEquals(connectedBleDev, mUsingDevice)) {
                            boolean isNeedDisconnect = true;
                            BleDevice bleDevice = getConnectedBle(connectedBleDev);
                            if (bleDevice != null) {
                                List<BluetoothGattService> services = bleDevice.getGatt().getServices();
                                if (services != null && services.size() > 0) {
                                    mBluetoothGattCallback.onServicesDiscovered(bleDevice.getGatt(), BluetoothGatt.GATT_SUCCESS);
                                    isNeedDisconnect = false;
                                }
                            }
                            if (isNeedDisconnect) {
                                JL_Log.d(TAG, "discover services timeout.");
                                disconnectBleDevice(connectedBleDev);
                                reconnectDevice(connectedBleDev.getAddress(), false);
                            }
                        }
                    }
                    break;
            }
            return false;
        }
    });

    public void reconnectDevice(String address, boolean isUseAdv) {
        JL_Log.d(TAG, "reconnectDevice : address = " + address + ", isUseAdv = " + isUseAdv);
        boolean ret = mReConnectHelper.putParam(new ReConnectHelper.ReconnectParam(address, isUseAdv));
        JL_Log.d(TAG, "reconnectDevice : ret = " + ret);
    }

    /**
     * Gets the connected BLE device list.
     *
     * @param context Android context.
     * @return Connected BLE device list.
     */
    @SuppressLint("MissingPermission")
    public static List<BluetoothDevice> getConnectedBleDeviceList(Context context) {
        if (context == null || !AppUtil.checkHasConnectPermission(context)) return null;
        BluetoothManager mBluetoothManager = (BluetoothManager) context.getSystemService(Context.BLUETOOTH_SERVICE);
        if (mBluetoothManager != null) {
            return mBluetoothManager.getConnectedDevices(BluetoothProfile.GATT);
        }
        return null;
    }

    public void destroy() {
        JL_Log.w(TAG, ">>>>>>>>>>>>>>destroy >>>>>>>>>>>>>>> ");
        unregisterReceiver();

        clearConnectedBleDevices();

        if (isBleScanning()) stopLeScan();
        isBleScanning(false);
        mDiscoveredBleDevices.clear();


        mCallbackManager.release();
        mHandler.removeCallbacksAndMessages(null);

//        instance = null;
    }

    public void registerBleEventCallback(BleEventCallback callback) {
        mCallbackManager.registerBleEventCallback(callback);
    }

    public void unregisterBleEventCallback(BleEventCallback callback) {
        mCallbackManager.unregisterBleEventCallback(callback);
    }

    public boolean isBluetoothEnable() {
        return mBluetoothAdapter != null && mBluetoothAdapter.isEnabled();
    }

    public boolean isBleScanning() {
        return isBleScanning;
    }

    // Gets the connected BLE device.
    @SuppressLint("MissingPermission")
    private List<BluetoothDevice> getConnectedBleDevices() {
        BluetoothManager bluetoothManager = (BluetoothManager) mContext.getSystemService(Context.BLUETOOTH_SERVICE);
        if (bluetoothManager != null) {
            // Gets all connected devices associated with GATT services.
            List<BluetoothDevice> connectedDevices = bluetoothManager.getConnectedDevices(BluetoothProfile.GATT);
            return connectedDevices;
        }
        return null;
    }

    @SuppressLint("MissingPermission")
    public boolean startLeScan(long timeout) {
        String TAG = "startLeScan";
        Log.e(TAG, "null == mBluetoothAdapter");
        if (null == mBluetoothAdapter || !AppUtil.checkHasScanPermission(mContext)) return false;
        Log.e(TAG, "isBluetooth disEnable");

        if (!isBluetoothEnable() || !AppUtil.isHasLocationPermission(mContext)) return false;
        if (timeout <= 0) timeout = SCAN_BLE_TIMEOUT;
        if (isBleScanning) {
            JL_Log.i(TAG, "scanning ble .....");
            if (mBluetoothLeScanner != null) {
                mBluetoothLeScanner.flushPendingScanResults(mScanCallback);
            }
            mDiscoveredBleDevices.clear();
            mHandler.removeMessages(MSG_SCAN_BLE_TIMEOUT);
            mHandler.sendEmptyMessageDelayed(MSG_SCAN_BLE_TIMEOUT, timeout);
            syncSystemBleDevice();
            return true;
        }
        /// Gets the connected device.
        List<BluetoothDevice> connectedDevices = getConnectedBleDevices();
        if (connectedDevices != null && !connectedDevices.isEmpty()) {
            for (BluetoothDevice device : connectedDevices) {
                Log.e(TAG, "Connected device: " + device.getName() + " - " + device.getAddress());
                filterDevice(device, 0, null, true);
            }
        } else {
            Log.e(TAG, "No connected BLE devices found.");
        }
        boolean ret;
        if (Build.VERSION.SDK_INT >= LOLLIPOP && mBluetoothLeScanner != null) {
            ScanSettings scanSettings;
            int scanMode = ScanSettings.SCAN_MODE_BALANCED; // Use balanced BLE scan mode.
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
//                Log.e(TAG, "Scan branch 1"); // TODO: reached this branch.
                scanSettings = new ScanSettings.Builder()
                        .setScanMode(scanMode)
                        .setMatchMode(ScanSettings.MATCH_MODE_AGGRESSIVE)
                        .build();
            } else {
//                Log.e(TAG, "Scan branch 2");

                scanSettings = new ScanSettings.Builder()
                        .setScanMode(scanMode)
                        .build();
            }
            mBluetoothLeScanner.startScan(null, scanSettings, mScanCallback);
            Log.e(TAG, "mDiscoveredBleDevices +" + mDiscoveredBleDevices);
            ret = true;
        } else {
            ret = mBluetoothAdapter.startLeScan(mLeScanCallback);
            mHandler.removeMessages(MSG_SCAN_BLE_TIMEOUT);
            mHandler.sendEmptyMessageDelayed(MSG_SCAN_BLE_TIMEOUT, timeout);
        }
        JL_Log.i(TAG, "startLeScan : " + ret + ", timeout = " + timeout);
        isBleScanning(ret);
        if (ret) {
            mDiscoveredBleDevices.clear();
//            BluetoothDevice device = getBluetoothDeviceById(mac);
            mHandler.removeMessages(MSG_SCAN_BLE_TIMEOUT);
            mHandler.sendEmptyMessageDelayed(MSG_SCAN_BLE_TIMEOUT, timeout);
            syncSystemBleDevice();
//            connectBleDevice(device);

        }
        return ret;
    }
    // Checks whether a Bluetooth device is connected.

    @SuppressLint("MissingPermission")
    private BluetoothDevice getBluetoothDeviceById(String remoteID) {
        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        BluetoothDevice targetDevice = bluetoothAdapter.getRemoteDevice(remoteID);

        // Checks whether the device supports BLE.
        if (targetDevice.getType() == BluetoothDevice.DEVICE_TYPE_LE) {
            // Device supports BLE.
            Log.d("Bluetooth", "Device supports BLE");
        } else {
            // Device does not support BLE.
            Log.d("Bluetooth", "Device does not support BLE");
        }

        return targetDevice;
    }

    @SuppressLint("MissingPermission")
    public void stopLeScan() {
        if (null == mBluetoothAdapter || !isBluetoothEnable() || !AppUtil.checkHasScanPermission(mContext))
            return;
        if (!isBleScanning()) return;
        try {
            if (Build.VERSION.SDK_INT >= LOLLIPOP && mBluetoothLeScanner != null) {
                mBluetoothLeScanner.stopScan(mScanCallback);
            } else {
                mBluetoothAdapter.stopLeScan(mLeScanCallback);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        mHandler.removeMessages(MSG_SCAN_BLE_TIMEOUT);
        mHandler.removeMessages(MSG_SCAN_HID_DEVICE);
        isBleScanning(false);
    }

    public BluetoothDevice getConnectedBtDevice() {
        return mUsingDevice;
    }

    public BluetoothGatt getConnectedBtGatt(BluetoothDevice device) {
        BleDevice bleDevice = getConnectedBle(device);
        if (null == bleDevice) return null;
        return bleDevice.getGatt();
    }

    public BluetoothDevice getConnectedBLEDevice(String address) {
        if (!BluetoothAdapter.checkBluetoothAddress(address)) return null;
        List<BluetoothDevice> devices = getConnectedDeviceList();
        if (devices.isEmpty()) return null;
        for (BluetoothDevice device : devices) {
            if (device.getAddress().equals(address)) {
                return device;
            }
        }
        return null;
    }

    /**
     * Gets the connected device list.
     * <p>
     * Sorted by connection time in descending order.
     * </p>
     *
     * @return Device list.
     */
    public List<BluetoothDevice> getConnectedDeviceList() {
        if (mConnectedGattMap.isEmpty()) return new ArrayList<>();
        List<BleDevice> bleDevices = getSortList();
        List<BluetoothDevice> devices = new ArrayList<>();
        for (BleDevice bleDevice : bleDevices) {
            if (null == bleDevice || null == bleDevice.getGatt().getDevice()) continue;
            devices.add(bleDevice.getGatt().getDevice());
        }
        return devices;
    }


    public int getBleMtu(BluetoothDevice device) {
        BleDevice bleDevice = getConnectedBle(device);
        if (null == bleDevice) return 0;
        return bleDevice.getMtu();
    }

    public boolean isConnecting() {
        return mConnectingBtDevice != null;
    }

    public boolean isConnectingDevice(BluetoothDevice device) {
        return BluetoothUtil.deviceEquals(mConnectingBtDevice, device);
    }

    public boolean isConnectedDevice(BluetoothDevice device) {
        if (null == device) return false;
        return isConnectedDevice(device.getAddress());
    }

    public boolean isConnectedDevice(String address) {
        if (!BluetoothAdapter.checkBluetoothAddress(address)) return false;
        List<BluetoothDevice> devices = getConnectedDeviceList();
        if (devices.isEmpty()) return false;
        for (BluetoothDevice device : devices) {
            if (device.getAddress().equals(address)) {
                return true;
            }
        }
        return false;
    }

    @SuppressLint("MissingPermission")
    public boolean connectBleDevice(BluetoothDevice device) {
//        if (isConnected) return true;
        // TODO: connect device.
        if (null == device || !AppUtil.checkHasConnectPermission(mContext)) return false;
       /* if (mUsingDevice != null) {
            JL_Log.e(TAG, "BleDevice is connected, please call disconnectBleDevice method at first.");
            setReconnectDevAddr(null);
            return false;
        }*/
        if (mConnectingBtDevice != null) {
            JL_Log.e(TAG, "BleDevice is connecting, please wait.");
            return isConnectingDevice(device);
        }
        if (isBleScanning()) {
            stopLeScan();
        }
        BluetoothGatt gatt = null;
        try {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
//                Log.e(TAG, "connectBleDevice1"); // TODO: reached this branch.
                gatt = device.connectGatt(
                        mContext,
                        false,
                        mBluetoothGattCallback,
                        BluetoothDevice.TRANSPORT_LE
                );
                Log.e(TAG, "gatt ==" + gatt);
            } else {
//                Log.e(TAG,"connectBleDevice2");
                gatt = device.connectGatt(
                        mContext,
                        false,
                        mBluetoothGattCallback
                );
            }
        } catch (Exception e) {
            Log.e(TAG, "GATT connection exception: " + e);
//            e.printStackTrace();
        }

        boolean ret = gatt != null;
        if (ret) {
//            putConnectedGattInMap(device.getAddress(), gatt);
            setConnectingBtDevice(device);
//            Log.e(TAG, "set mConnectingBtDevice == " + mConnectingBtDevice + ", device == " + device); // TODO: both values exist.
            handleBleConnection(device, BluetoothProfile.STATE_CONNECTING);
            JL_Log.d(TAG, "connect start...." + printDeviceInfo(mConnectingBtDevice));
        }
        return ret;
    }

    @SuppressLint("MissingPermission")
    public void disconnectBleDevice(BluetoothDevice device) {
        if (null == device || !AppUtil.checkHasConnectPermission(mContext)) return;
        BleDevice bleDevice = removeConnectedBle(device);
        JL_Log.i(TAG, "disconnectBleDevice : " + printDeviceInfo(device) + ", " + bleDevice);
        if (bleDevice != null) {
            if (BluetoothUtil.isBluetoothEnable()) {
                bleDevice.getGatt().disconnect();
//                bleDevice.getGatt().close();
            }
        } else {
            JL_Log.i(TAG, "disconnectBleDevice : It is not a connected device.");
        }
    }

    public void writeDataByBleAsync(BluetoothDevice device, UUID serviceUUID, UUID characteristicUUID, byte[] data, OnWriteDataCallback callback) {
        addSendTask(device, serviceUUID, characteristicUUID, data, callback);
    }

    private void isBleScanning(boolean isScanning) {
        isBleScanning = isScanning;
        mCallbackManager.onDiscoveryBleChange(isScanning);
        if (isBleScanning && configHelper.isHidDevice()) {
            mHandler.sendEmptyMessage(MSG_SCAN_HID_DEVICE);

        }
    }

    private BleDevice getConnectedBle(BluetoothDevice device) {
        if (null == device) return null;
        return mConnectedGattMap.get(device.getAddress());
    }

    private void putConnectedGattInMap(String address, BluetoothGatt gatt) {
        if (!BluetoothAdapter.checkBluetoothAddress(address) || null == gatt) return;
        BleDevice bleDevice = new BleDevice(mContext, gatt);
        bleDevice.setConnectedTime(System.currentTimeMillis());
        mConnectedGattMap.put(address, bleDevice);
        if (mUsingDevice == null) {
            mUsingDevice = gatt.getDevice();
        }

        JL_Log.i(TAG, "putConnectedGattInMap >>>>>>>>>>>>> start");
        for (String addr : mConnectedGattMap.keySet()) {
            JL_Log.d(TAG, "putConnectedGattInMap >>>>>>>>>>>>> " + addr);
        }
        JL_Log.i(TAG, "putConnectedGattInMap >>>>>>>>>>>>> end");
    }

    private BleDevice removeConnectedBle(BluetoothDevice device) {
        if (null == device) return null;
        return removeConnectedBle(device.getAddress());
    }

    private BleDevice removeConnectedBle(String address) {
        if (!BluetoothAdapter.checkBluetoothAddress(address)) return null;
        BleDevice bleDevice = mConnectedGattMap.remove(address);
        if (null != bleDevice) {
            bleDevice.stopSendDataThread();
            if (mConnectedGattMap.isEmpty()) {
                setConnectedBtDevice(null);
            } else if (bleDevice.getGatt().getDevice() != null && BluetoothUtil.deviceEquals(bleDevice.getGatt().getDevice(),
                    getConnectedBtDevice())) {
                List<BleDevice> values = getSortList();
                setConnectedBtDevice(values.get(0).getGatt().getDevice());
            }
        }
        return bleDevice;
    }

    @NonNull
    private List<BleDevice> getSortList() {
        if (mConnectedGattMap.isEmpty()) return new ArrayList<>();
        List<BleDevice> bleDevices = new ArrayList<>(mConnectedGattMap.values());
        Collections.sort(bleDevices, (o1, o2) -> {
            if (null == o1 && null == o2) return 0;
            if (null == o1) return 1;
            if (null == o2) return -1;
            return Long.compare(o2.getConnectedTime(), o1.getConnectedTime());
        });
        return bleDevices;
    }

    private void clearConnectedBleDevices() {
        if (!AppUtil.checkHasConnectPermission(mContext)) return;
        if (!mConnectedGattMap.isEmpty()) {
            Map<String, BleDevice> clone = new HashMap<>(mConnectedGattMap);
            for (String key : clone.keySet()) {
                BleDevice bleDevice = clone.get(key);
                if (null == bleDevice) continue;
                bleDevice.getGatt().disconnect();
                bleDevice.getGatt().close();
            }
            mConnectedGattMap.clear();
        }
    }

    private void startConnectTimeout(BluetoothDevice device) {
        if (!mHandler.hasMessages(MSG_CONNECT_BLE_TIMEOUT)) {
            mHandler.sendMessageDelayed(mHandler.obtainMessage(MSG_CONNECT_BLE_TIMEOUT, device), CONNECT_BLE_TIMEOUT);
        }
    }

    private void stopConnectTimeout() {
        if (mHandler.hasMessages(MSG_CONNECT_BLE_TIMEOUT)) {
            mHandler.removeMessages(MSG_CONNECT_BLE_TIMEOUT);
        }
    }

    private void setConnectingBtDevice(BluetoothDevice mConnectingBtDevice) {
        this.mConnectingBtDevice = mConnectingBtDevice;
    }

    private void setConnectedBtDevice(BluetoothDevice mConnectedBtDevice) {
        this.mUsingDevice = mConnectedBtDevice;
    }


    @SuppressLint("MissingPermission")
    private void filterDevice(BluetoothDevice device, int rssi, byte[] scanRecord,
                              boolean isBleEnableConnect) {

        String TAGG = "filterDevice";
//        Log.e(TAGG," 1 "+device+",2 "+rssi+", 3 "+scanRecord );
        if (AppUtil.checkHasConnectPermission(mContext) && isBluetoothEnable() && !TextUtils.isEmpty(device.getName())
                && !mDiscoveredBleDevices.contains(device)) {
            JL_Log.d(TAG, "notify device : " + printDeviceInfo(device));
            if (device.getAddress().equalsIgnoreCase(mac)) {
                Log.e(TAGG, "Target device found; connecting.");
                if (connectBleDevice(device)) {
                    isConnected = false;
                }
                connectBleDevice(device);
            }
            mDiscoveredBleDevices.add(device);
            handleDiscoveryBle(device, new BleScanInfo().setRawData(scanRecord).setRssi(rssi).setEnableConnect(isBleEnableConnect));
        }
    }


    private void syncSystemBleDevice() {
        List<BluetoothDevice> mSysConnectedBleList = getConnectedBleDeviceList(mContext);
        if (mSysConnectedBleList != null && !mSysConnectedBleList.isEmpty()) {
            for (BluetoothDevice bleDev : mSysConnectedBleList) {
                if (!BluetoothUtil.deviceEquals(bleDev, mUsingDevice)) {
                    if (!mDiscoveredBleDevices.contains(bleDev)) {
                        mDiscoveredBleDevices.add(bleDev);
                        handleDiscoveryBle(bleDev, new BleScanInfo().setEnableConnect(true));
                    }
                }
            }
        }
    }

    private void addSendTask(BluetoothDevice device, UUID serviceUUID, UUID characteristicUUID,
                             byte[] data, OnWriteDataCallback callback) {
        boolean ret = false;
        BleDevice bleDevice = getConnectedBle(device);
        if (bleDevice != null) {
            ret = bleDevice.addSendTask(serviceUUID, characteristicUUID, data, callback);
        }
        if (!ret && callback != null) {
            callback.onBleResult(device, serviceUUID, characteristicUUID, false, data);
        }
    }

    private void wakeupSendThread(BluetoothGatt gatt, UUID serviceUUID, UUID characteristicUUID,
                                  int status, byte[] data) {
        final BleDevice bleDevice = getConnectedBle(gatt.getDevice());
        if (bleDevice != null) {
            SendBleDataThread.BleSendTask task = new SendBleDataThread.BleSendTask(gatt, serviceUUID, characteristicUUID, data, null);
            task.setStatus(status);
            bleDevice.wakeupSendThread(task);
        }
    }

    private void handleDiscoveryBle(BluetoothDevice device, BleScanInfo bleScanInfo) {
        mCallbackManager.onDiscoveryBle(device, bleScanInfo);
    }

    @SuppressLint("MissingPermission")
    private void handleBleConnection(final BluetoothDevice device, final int status) {
        if (status == BluetoothProfile.STATE_DISCONNECTED || status == BluetoothProfile.STATE_CONNECTED) {
            mHandler.removeMessages(MSG_NOTIFY_BLE_TIMEOUT);

            startConnectTime = 0;

        } else if (status == BluetoothProfile.STATE_CONNECTING) {
            startConnectTime = System.currentTimeMillis();
        }
        JL_Log.i(TAG, "handleBleConnection >> device : " + device + ", status : " + status);
        mCallbackManager.onBleConnection(device, status);
    }

    /* ---- BroadcastReceiver Handler ---- */
    private void registerReceiver() {
        if (mAdapterReceiver == null) {
            Log.e(TAG, "registerReceiver");
            mAdapterReceiver = new BaseBtAdapterReceiver();
            IntentFilter intentFilter = new IntentFilter(BluetoothAdapter.ACTION_STATE_CHANGED);
            intentFilter.addAction(BluetoothDevice.ACTION_ACL_CONNECTED);
            intentFilter.addAction(BluetoothDevice.ACTION_ACL_DISCONNECTED);
            mContext.registerReceiver(mAdapterReceiver, intentFilter);
        }
    }

    private void unregisterReceiver() {
        if (mAdapterReceiver != null) {
            Log.e(TAG, "unregisterReceiver");

            mContext.unregisterReceiver(mAdapterReceiver);
            mAdapterReceiver = null;
        }
    }

    /**
     * Enables the BLE notification service.
     *
     * @param gatt               Connected BLE GATT service object.
     * @param serviceUUID        Service UUID.
     * @param characteristicUUID characteristic UUID
     * @return true when the system BLE service callback should be awaited.
     */
    @SuppressLint("MissingPermission")
    private boolean enableBLEDeviceNotification(BluetoothGatt gatt, UUID serviceUUID, UUID
            characteristicUUID) {
        if (null == gatt || !AppUtil.checkHasConnectPermission(mContext)) {
            JL_Log.w(TAG, "Bluetooth gatt is null.");
            return false;
        }
        BluetoothGattService gattService = gatt.getService(serviceUUID);
        if (null == gattService) {
            JL_Log.w(TAG, "BluetoothGattService is null. uuid = " + serviceUUID);
            return false;
        }
        BluetoothGattCharacteristic characteristic = gattService.getCharacteristic(characteristicUUID);
        if (null == characteristic) {
            JL_Log.w(TAG, "BluetoothGattCharacteristic is null. uuid = " + characteristicUUID);
            return false;
        }
        boolean bRet = gatt.setCharacteristicNotification(characteristic, true);
        if (bRet) {
            bRet = false; // Reset the flag.
            List<BluetoothGattDescriptor> descriptors = characteristic.getDescriptors();
            for (BluetoothGattDescriptor descriptor : descriptors) {
                if (!BLE_UUID_NOTIFICATION_DESCRIPTOR.equals(descriptor.getUuid()))
                    continue; // Skip unrelated descriptors.
                bRet = tryToWriteDescriptor(gatt, descriptor, 0, false);
                if (!bRet) {
                    JL_Log.w(TAG, "tryToWriteDescriptor failed....");
                } else { // Usually there is only one descriptor to enable.
                    break;
                }
            }
        } else {
            JL_Log.w(TAG, "setCharacteristicNotification is failed....");
        }
        JL_Log.w(TAG, "enableBLEDeviceNotification ret : " + bRet + ", serviceUUID : " + serviceUUID + ", characteristicUUID : " + characteristicUUID);
        return bRet;
    }

    @SuppressLint("MissingPermission")
    private boolean tryToWriteDescriptor(BluetoothGatt bluetoothGatt, BluetoothGattDescriptor
            descriptor, int retryCount, boolean isSkipSetValue) {
        if (!AppUtil.checkHasConnectPermission(mContext)) return false;
        boolean ret = isSkipSetValue;
        if (!ret) {
            ret = descriptor.setValue(BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE);
            JL_Log.i(TAG, "..descriptor : .setValue  ret : " + ret);
            if (!ret) {
                retryCount++;
                if (retryCount >= 3) {
                    return false;
                } else {
                    JL_Log.i(TAG, "-tryToWriteDescriptor- : retryCount : " + retryCount + ", isSkipSetValue :  false");
                    SystemClock.sleep(50);
                    tryToWriteDescriptor(bluetoothGatt, descriptor, retryCount, false);
                }
            } else {
                retryCount = 0;
            }
        }
        if (ret) {
            ret = bluetoothGatt.writeDescriptor(descriptor);
            JL_Log.i(TAG, "..bluetoothGatt : .writeDescriptor  ret : " + ret);
            if (!ret) {
                retryCount++;
                if (retryCount >= 3) {
                    return false;
                } else {
                    JL_Log.i(TAG, "-tryToWriteDescriptor- 2222 : retryCount : " + retryCount + ", isSkipSetValue :  true");
                    SystemClock.sleep(50);
                    tryToWriteDescriptor(bluetoothGatt, descriptor, retryCount, true);
                }
            }
        }
        return ret;
    }

    // Clears the MTU change timeout task.
    private void stopChangeMtu() {
        mHandler.removeMessages(MSG_CHANGE_BLE_MTU_TIMEOUT);
    }

    // Starts changing the BLE protocol MTU.
    @SuppressLint("MissingPermission")
    private void startChangeMtu(BluetoothGatt gatt, int mtu) {
        if (gatt == null || !AppUtil.checkHasConnectPermission(mContext)) {
            JL_Log.w(TAG, "-startChangeMtu- param is error.");
            return;
        }
        BluetoothDevice device = gatt.getDevice();
        if (device == null) {
            JL_Log.w(TAG, "-startChangeMtu- device is null.");
            return;
        }
        if (mHandler.hasMessages(MSG_CHANGE_BLE_MTU_TIMEOUT)) {
            JL_Log.w(TAG, "-startChangeMtu- Adjusting the MTU for BLE");
            return;
        }
        boolean ret = false;
        if (mtu > BluetoothConstant.BLE_MTU_MIN) {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
                ret = gatt.requestMtu(mtu + 3);
            } else {
                ret = true;
            }
        }
        JL_Log.d(TAG, "-startChangeMtu- ret = " + ret);
        if (ret) { // MTU change succeeded; start timeout task.
            mHandler.sendMessageDelayed(mHandler.obtainMessage(MSG_CHANGE_BLE_MTU_TIMEOUT, device), CALLBACK_TIMEOUT);
        } else {
            handleBleConnectedEvent(device);
        }
    }


    private void handleBleConnectedEvent(final BluetoothDevice device) {
        if (device == null) {
            JL_Log.e(TAG, "-handleBleConnectedEvent- device is null.");
            return;
        }

        BleDevice bleDevice = getConnectedBle(device);
        bleDevice.startSendDataThread();
        handleBleConnection(device, BluetoothProfile.STATE_CONNECTED);
    }

    private String printDeviceInfo(BluetoothDevice device) {
        return BluetoothUtil.printBtDeviceInfo(mContext, device);
    }

    private final BluetoothAdapter.LeScanCallback mLeScanCallback = (device, rssi, scanRecord) -> filterDevice(device, rssi, scanRecord, true);

    private final ScanCallback mScanCallback = new ScanCallback() {
        @Override
        public void onScanResult(int callbackType, ScanResult result) {
            if (result != null && result.getScanRecord() != null) {
                BluetoothDevice device = result.getDevice();

                boolean isBleEnableConnect = true;
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                    isBleEnableConnect = result.isConnectable();
                }
//                JL_Log.i("onScanResult", printDeviceInfo(device));
                filterDevice(device, result.getRssi(), result.getScanRecord().getBytes(), isBleEnableConnect);
            }
        }

        @Override
        public void onBatchScanResults(List<ScanResult> results) {

        }

        @Override
        public void onScanFailed(int errorCode) {
            JL_Log.d(TAG, "onScanFailed : " + errorCode);
            stopLeScan();
        }
    };

    private BleConnectedCallBack bleConnectedCallBack;

    public void setOnConnectionUpdatedListener(BleConnectedCallBack listener) {
        this.bleConnectedCallBack = listener;
    }

    private final BluetoothGattCallback mBluetoothGattCallback = new BluetoothGattCallback() {

        public void onConnectionUpdated(BluetoothGatt gatt, int interval, int latency, int timeout, int status) {
            if (null == gatt) return;
            BluetoothDevice device = gatt.getDevice();
            if (null == device) return;
            JL_Log.e(TAG, "onConnectionUpdated >>> device : " + device + ", interval : "
                    + interval + ", latency : " + latency + ", timeout : " + timeout + ", status : " + status);

            mCallbackManager.onConnectionUpdated(device, interval, latency, timeout, status);
        }

        @SuppressLint("MissingPermission")
        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {
            if (null == gatt || !AppUtil.checkHasConnectPermission(mContext)) return;
            final BluetoothDevice device = gatt.getDevice();
            if (null == device) return;
            JL_Log.i(TAG, String.format(Locale.getDefault(), "onConnectionStateChange : device : %s, status = %d, newState = %d.",
                    device.getName(), status, newState));
            if (newState == BluetoothProfile.STATE_DISCONNECTED || newState == BluetoothProfile.STATE_DISCONNECTING
                    || newState == BluetoothProfile.STATE_CONNECTED) {

                setConnectingBtDevice(null);
                if (newState == BluetoothProfile.STATE_CONNECTED) {  // BLE connected.
                    Log.e(TAG, "BLE connected.");

                    isConnected = true;
                    mRetryConnectCount = 0;
                    boolean ret = gatt.discoverServices();
                    JL_Log.d(TAG, "onConnectionStateChange >> discoverServices : " + ret);
                    putConnectedGattInMap(device.getAddress(), gatt);
//                    setConnectedBtDevice(device);
                    if (ret) {
                        mHandler.removeMessages(MSG_BLE_DISCOVER_SERVICES_CALLBACK_TIMEOUT);
                        mHandler.sendMessageDelayed(mHandler.obtainMessage(MSG_BLE_DISCOVER_SERVICES_CALLBACK_TIMEOUT, device), CALLBACK_TIMEOUT);
                    } else {
                        disconnectBleDevice(device);
                    }
                    return;
                } else {
                    removeConnectedBle(device);
                    AppUtil.refreshBleDeviceCache(mContext, gatt); // Force cache refresh.
                    gatt.close();

                    long usedConnectTime = System.currentTimeMillis() - startConnectTime; // Elapsed connection time.
                    JL_Log.d(TAG, "onConnectionStateChange >> usedConnectTime = " + usedConnectTime + ", limit time = " + MIN_CONNECT_TIME);
                    if (status == 133 && usedConnectTime < MIN_CONNECT_TIME) { // TODO: unexpected disconnect; retry the connection.
                        if (mRetryConnectCount < MAX_RETRY_CONNECT_COUNT) {
                            mRetryConnectCount++;
                            connectBleDevice(device);
                            return;
                        } else {
                            mRetryConnectCount = 0;
                        }
                    }
                }
            }
            handleBleConnection(device, newState);
        }

        @SuppressLint("MissingPermission")
        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {
            if (null == gatt || !AppUtil.checkHasConnectPermission(mContext)) return;
            BluetoothDevice device = gatt.getDevice();
            if (null == device) return;
            mHandler.removeMessages(MSG_BLE_DISCOVER_SERVICES_CALLBACK_TIMEOUT);

            mCallbackManager.onBleServiceDiscovery(device, status, gatt.getServices());
//            JL_Log.i(TAG, "onServicesDiscovered device: " + device+",status:"+status+",services:"+gatt.getServices());  valid

            boolean ret = false;
            if (status == BluetoothGatt.GATT_SUCCESS) {
                AppUtil.printBleGattServices(mContext, device, gatt, status);
                Log.e(TAG, "onServicesDiscovered type = " + device.getType());
                for (BluetoothGattService service : gatt.getServices()) {
                    if (BLE_UUID_SERVICE.equals(service.getUuid()) && null != service.getCharacteristic(BLE_UUID_WRITE)
                            && null != service.getCharacteristic(BLE_UUID_NOTIFICATION)) {
                        JL_Log.i(TAG, "start NotifyCharacteristicRunnable...");
                        mNotifyCharacteristicRunnable = new NotifyCharacteristicRunnable(gatt, BLE_UUID_SERVICE, BLE_UUID_NOTIFICATION);
                        mHandler.post(mNotifyCharacteristicRunnable);

                        ret = true;
                        break;
                    }

                }


            }
            JL_Log.i(TAG, "onServicesDiscovered : " + ret);
            if (bleConnectedCallBack != null) {
                bleConnectedCallBack.onConnectedCB(true);
            }

            if (!ret) {
                disconnectBleDevice(device);
            }
        }

        @SuppressLint("MissingPermission")
        @Override
        public void onCharacteristicChanged(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {
            if (null == gatt || !AppUtil.checkHasConnectPermission(mContext)) return;
            BluetoothDevice device = gatt.getDevice();
            if (null == device || null == characteristic) return;
            UUID serviceUUID = null;
            UUID characteristicUUID = characteristic.getUuid();
            byte[] data = characteristic.getValue();
            BluetoothGattService gattService = characteristic.getService();
            if (gattService != null) {
                serviceUUID = gattService.getUuid();
            }
            JL_Log.d(TAG, String.format(Locale.getDefault(), "onCharacteristicChanged : deice : %s, serviceUuid = %s, characteristicUuid = %s, \ndata : [%s]",
                    printDeviceInfo(device), serviceUUID, characteristicUUID, CHexConver.byte2HexStr(data)));
            mCallbackManager.onBleDataNotification(device, serviceUUID, characteristicUUID, data);
        }

        @SuppressLint("MissingPermission")
        @Override
        public void onCharacteristicWrite(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
            if (null == gatt || null == gatt.getDevice() || null == characteristic
                    || !AppUtil.checkHasConnectPermission(mContext)) return;
            BluetoothDevice device = gatt.getDevice();
            UUID serviceUUID = null;
            UUID characteristicUUID = characteristic.getUuid();
            BluetoothGattService gattService = characteristic.getService();
            if (gattService != null) serviceUUID = gattService.getUuid();
            byte[] data = characteristic.getValue();
            JL_Log.d(TAG, String.format(Locale.getDefault(), "onCharacteristicWrite : device : %s, serviceUuid = %s, characteristicUuid = %s, status = %d, \ndata : [%s]",
                    printDeviceInfo(device), serviceUUID, characteristicUUID, status, CHexConver.byte2HexStr(data)));
            wakeupSendThread(gatt, serviceUUID, characteristicUUID, status, data);
            mCallbackManager.onBleWriteStatus(device, serviceUUID, characteristicUUID, data, status);
        }

        @SuppressLint("MissingPermission")
        @Override
        public void onDescriptorWrite(BluetoothGatt gatt, BluetoothGattDescriptor descriptor, int status) {
            Log.e(TAG, "onDescriptorWrite gatt=" + gatt + ",descriptor==" + descriptor + ",status==" + status);

            Log.e(TAG, "onDescriptorWrite 1");
            if (null == gatt || !AppUtil.checkHasConnectPermission(mContext)) return;
            Log.e(TAG, "onDescriptorWrite 2");

            BluetoothDevice device = gatt.getDevice();
            if (null == device || null == descriptor) return;
            Log.e(TAG, "onDescriptorWrite 3");

            UUID serviceUuid = null;
            UUID characteristicUuid = null;
            BluetoothGattCharacteristic characteristic = descriptor.getCharacteristic();
            if (null != characteristic) {
                characteristicUuid = characteristic.getUuid();
                BluetoothGattService bluetoothGattService = characteristic.getService();
                if (null != bluetoothGattService) {
                    serviceUuid = bluetoothGattService.getUuid();
                }
            }
            JL_Log.i(TAG, String.format(Locale.getDefault(), "onDescriptorWrite : device : %s, serviceUuid = %s, characteristicUuid = %s, descriptor = %s, status = %d",
                    printDeviceInfo(device), serviceUuid, characteristicUuid, descriptor.getUuid(), status));
            mCallbackManager.onBleNotificationStatus(device, serviceUuid, characteristicUuid, status);
            if (mNotifyCharacteristicRunnable != null && BluetoothUtil.deviceEquals(device, mNotifyCharacteristicRunnable.getBleDevice())
                    && serviceUuid != null && serviceUuid.equals(mNotifyCharacteristicRunnable.getServiceUUID())
                    && characteristicUuid != null && characteristicUuid.equals(mNotifyCharacteristicRunnable.getCharacteristicUUID())
                    && descriptor.getUuid() != null && descriptor.getUuid().equals(mNotifyCharacteristicRunnable.mDescriptorUUID)) {
                if (status == BluetoothGatt.GATT_SUCCESS) {
                    mNotifyCharacteristicRunnable = null;
                    // TODO: 2022/6/28 Some phones, such as Xiaomi 11 Lite, cannot use the maximum MTU. Use a smaller MTU when needed.
//                    startChangeMtu(gatt, 128); // Limit MTU to 128.
                    int requestMTU = configHelper.getBleRequestMtu();
                    if (requestMTU > 509) {
                        requestMTU = 509;
                    }
                    startChangeMtu(gatt, requestMTU);
                    Log.e(TAG, "run handleBleConnectedEvent 2");

//                    handleBleConnectedEvent(device);
                } else {
                    int num = mNotifyCharacteristicRunnable.getRetryNum();
                    if (num < 3) {
                        mNotifyCharacteristicRunnable.setRetryNum(++num);
                        mHandler.postDelayed(mNotifyCharacteristicRunnable, 100);

                    } else {
                        disconnectBleDevice(device);
                    }
                }
            }
        }

        @SuppressLint("MissingPermission")
        @Override
        public void onMtuChanged(BluetoothGatt gatt, int mtu, int status) {
            if (null == gatt || !AppUtil.checkHasConnectPermission(mContext)) return;
            BluetoothDevice device = gatt.getDevice();
            if (null == device) return;
            JL_Log.d(TAG, String.format(Locale.getDefault(), "onMtuChanged : device : %s, mtu = %d, status = %d", printDeviceInfo(device), mtu, status));
            mCallbackManager.onBleDataBlockChanged(device, mtu, status);
            BleDevice bleDevice = getConnectedBle(device);
            if (BluetoothGatt.GATT_SUCCESS == status) {
                // Subtract the 3-byte packet header.
                int bleMtu = mtu - 3;
                if (bleDevice != null && mHandler.hasMessages(MSG_CHANGE_BLE_MTU_TIMEOUT)) { // MTU change callback.


                    bleDevice.setMtu(bleMtu);
                    JL_Log.i(TAG, "-onMtuChanged- handleBleConnectedEvent");
                    Log.e(TAG, "run handleBleConnectedEvent 3");

                    handleBleConnectedEvent(device);
                }
            }
        }
    };

    private class BaseBtAdapterReceiver extends BroadcastReceiver {

        @Override
        public void onReceive(Context context, Intent intent) {
            if (intent != null) {
                String action = intent.getAction();
                if (action == null) return;
                switch (action) {
                    case BluetoothAdapter.ACTION_STATE_CHANGED: {
                        int state = intent.getIntExtra(BluetoothAdapter.EXTRA_CONNECTION_STATE, -1);
                        if (mBluetoothAdapter != null && state == -1) {
                            state = mBluetoothAdapter.getState();
                        }
                        if (state == BluetoothAdapter.STATE_OFF) {
                            isBleScanning(false);
                            mDiscoveredBleDevices.clear();
                            mCallbackManager.onDiscoveryBleChange(false);
                            disconnectBleDevice(getConnectedBtDevice());
                            mCallbackManager.onAdapterChange(false);
                        } else if (state == BluetoothAdapter.STATE_ON) {
                            mCallbackManager.onAdapterChange(true);
                        }
                        break;
                    }
                    case BluetoothDevice.ACTION_ACL_CONNECTED: {
                        BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                        JL_Log.i(TAG, "BaseBtAdapterReceiver: ACTION_ACL_CONNECTED, device : "
                                + printDeviceInfo(device));
                        break;
                    }
                    case BluetoothDevice.ACTION_ACL_DISCONNECTED: {
                        BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                        JL_Log.i(TAG, "BaseBtAdapterReceiver: ACTION_ACL_DISCONNECTED, device : "
                                + printDeviceInfo(device));
                        break;
                    }

                }
            }
        }
    }

    private class NotifyCharacteristicRunnable implements Runnable {
        private final BluetoothGatt mGatt;
        private final UUID mServiceUUID;
        private final UUID mCharacteristicUUID;
        public final UUID mDescriptorUUID = BLE_UUID_NOTIFICATION_DESCRIPTOR;
        private int retryNum = 0;

        private NotifyCharacteristicRunnable(BluetoothGatt gatt, UUID serviceUUID, UUID characteristicUUID) {
            this.mGatt = gatt;
            this.mServiceUUID = serviceUUID;
            this.mCharacteristicUUID = characteristicUUID;
//            Log.e("NotifyCharacteristicRunnable","mgatt=="+mGatt+",mSU=="+mServiceUUID+",mCU=="+mCharacteristicUUID);TODO: values are set correctly.
        }

        private void setRetryNum(int retryNum) {
            this.retryNum = retryNum;
        }

        private int getRetryNum() {
            return retryNum;
        }

        private BluetoothDevice getBleDevice() {
            if (mGatt == null) return null;
            return mGatt.getDevice();
        }

        private UUID getServiceUUID() {
            return mServiceUUID;
        }

        private UUID getCharacteristicUUID() {
            return mCharacteristicUUID;
        }

        @Override
        public void run() {
            boolean ret = enableBLEDeviceNotification(mGatt, mServiceUUID, mCharacteristicUUID);
            JL_Log.w(TAG, String.format(Locale.getDefault(), "enableBLEDeviceNotification ===> %s, service uuid = %s, characteristic uuid = %s",
                    ret, mServiceUUID, mCharacteristicUUID));
            if (!ret) {
                if (mGatt != null) {
                    disconnectBleDevice(mGatt.getDevice());
                }
            } else {
                mHandler.removeMessages(MSG_NOTIFY_BLE_TIMEOUT);
                mHandler.sendMessageDelayed(mHandler.obtainMessage(MSG_NOTIFY_BLE_TIMEOUT, mGatt.getDevice()), CALLBACK_TIMEOUT);

            }
        }
    }
}

