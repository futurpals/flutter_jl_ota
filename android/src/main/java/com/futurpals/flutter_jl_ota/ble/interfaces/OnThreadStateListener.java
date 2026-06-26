package com.futurpals.flutter_jl_ota.ble.interfaces;

/**
 * Thread lifecycle listener.
 *
 * @author zqjasonZhong
 * @date 2019/9/20
 */
public interface OnThreadStateListener {

    void onStart(long id, String name);

    void onEnd(long id, String name);
}
