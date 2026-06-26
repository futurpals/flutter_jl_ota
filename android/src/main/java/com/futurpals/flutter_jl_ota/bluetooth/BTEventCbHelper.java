package com.futurpals.flutter_jl_ota.bluetooth;

import android.bluetooth.BluetoothDevice;
import android.os.Handler;
import android.os.Looper;

import com.futurpals.flutter_jl_ota.ble.model.BleScanInfo;
import com.futurpals.flutter_jl_ota.bluetooth.OnBTEventCallback;


import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

/**
 * @author zqjasonZhong
 * @since 2022/9/14
 * @email zhongzhuocheng@zh-jieli.com
 * @desc Bluetooth event callback helper.
 */
public class BTEventCbHelper extends OnBTEventCallback {
    private final List<OnBTEventCallback> callbacks = new ArrayList<>();
    private final Handler uiHandler = new Handler(Looper.getMainLooper());

    public void registerCallback(OnBTEventCallback callback) {
        if (!callbacks.contains(callback)) {
            callbacks.add(callback);
        }
    }

    public void unregisterCallback(OnBTEventCallback callback) {
        callbacks.remove(callback);
    }

    public void release() {
        callbacks.clear();
        uiHandler.removeCallbacksAndMessages(null);
    }

    @Override
    public void onAdapterChange(boolean bEnabled) {
        callbackEvent(new CallbackImpl<OnBTEventCallback>() {
            @Override
            public void onCallback(OnBTEventCallback callback) {
                callback.onAdapterChange(bEnabled);
            }
        });
    }

    @Override
    public void onDiscoveryChange(boolean bStart, int scanType) {
        callbackEvent(new CallbackImpl<OnBTEventCallback>() {
            @Override
            public void onCallback(OnBTEventCallback callback) {
                callback.onDiscoveryChange(bStart, scanType);
            }
        });
    }

    @Override
    public void onDiscovery(BluetoothDevice device, BleScanInfo bleScanMessage) {
        callbackEvent(new CallbackImpl<OnBTEventCallback>() {
            @Override
            public void onCallback(OnBTEventCallback callback) {
                callback.onDiscovery(device, bleScanMessage);
            }
        });
    }

    @Override
    public void onDeviceConnection(BluetoothDevice device, int way, int status) {
        callbackEvent(new CallbackImpl<OnBTEventCallback>() {
            @Override
            public void onCallback(OnBTEventCallback callback) {
                callback.onDeviceConnection(device, way, status);
            }
        });
    }

    @Override
    public void onReceiveData(BluetoothDevice device, int way, UUID uuid, byte[] data) {
        callbackEvent(new CallbackImpl<OnBTEventCallback>() {
            @Override
            public void onCallback(OnBTEventCallback callback) {
                callback.onReceiveData(device, way, uuid, data);
            }
        });
    }

    @Override
    public void onBleMtuChange(BluetoothDevice device, int mtu, int status) {
        callbackEvent(new CallbackImpl<OnBTEventCallback>() {
            @Override
            public void onCallback(OnBTEventCallback callback) {
                callback.onBleMtuChange(device, mtu, status);
            }
        });
    }

    private void callbackEvent(CallbackImpl<OnBTEventCallback> impl) {
        if (impl == null) return;
        CallbackRunnable runnable = new CallbackRunnable(callbacks, impl);
        if (Thread.currentThread().getId() == Looper.getMainLooper().getThread().getId()) {
            runnable.run();
        } else {
            uiHandler.post(runnable);
        }
    }

    private interface CallbackImpl<T> {
        void onCallback(T callback);
    }

    private static class CallbackRunnable implements Runnable {
        private final List<OnBTEventCallback> callbacks;
        private final CallbackImpl<OnBTEventCallback> impl;

        CallbackRunnable(List<OnBTEventCallback> callbacks, CallbackImpl<OnBTEventCallback> impl) {
            this.callbacks = callbacks;
            this.impl = impl;
        }

        @Override
        public void run() {
            for (OnBTEventCallback callback : callbacks) {
                impl.onCallback(callback);
            }
        }
    }
}
