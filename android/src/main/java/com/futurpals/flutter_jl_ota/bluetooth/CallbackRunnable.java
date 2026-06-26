package com.futurpals.flutter_jl_ota.bluetooth;

import java.util.ArrayList;
import java.util.List;

/**
 * @author zqjasonZhong
 * @since 2022/9/14
 * @email zhongzhuocheng@zh-jieli.com
 * @desc Callback dispatcher.
 */
public class CallbackRunnable<T> implements Runnable {

    private final List<T> callbacks;
    private final CallbackImpl<T> impl;

    public CallbackRunnable(List<T> callbacks, CallbackImpl<T> impl) {
        this.callbacks = new ArrayList<>(callbacks); // Create a copy of the list
        this.impl = impl;
    }

    @Override
    public void run() {
        if (callbacks.isEmpty() || impl == null) return;
        for (T callback : callbacks) {
            impl.onCallback(callback);
        }
    }
}