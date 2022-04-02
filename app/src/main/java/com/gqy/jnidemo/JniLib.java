package com.gqy.jnidemo;

public class JniLib {

    static {
        System.loadLibrary("jnidemo");
    }

    public native String stringFromJNI();

    public native String jniMethodLx(int len, String flag);

    public static native int calcSum(int left, int cnt);
    public static native int compareStr(String left, String right);
}
