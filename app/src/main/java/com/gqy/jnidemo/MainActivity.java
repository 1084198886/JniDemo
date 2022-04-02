package com.gqy.jnidemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    String TAG = "Native-Jni";
    JniLib jniLib = new JniLib();
    public static int N = 11;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tvMsg = findViewById(R.id.tv_msg);
        tvMsg.setText(jniLib.stringFromJNI());
        findViewById(R.id.btn_javaT).setOnClickListener(v -> {
            tvMsg.setText(javaCalcTest(10, 1000000000) + "ms");
        });
        findViewById(R.id.btn_jniT).setOnClickListener(v -> {
            tvMsg.setText(JniLib.calcSum(10, 1000000000) + "ms");
        });
        findViewById(R.id.btn_compareStr).setOnClickListener(v -> {
            int ret = JniLib.compareStr("a", "a");
            if (ret == 0) {
                tvMsg.setText("相等");
            } else {
                tvMsg.setText("不等");
            }
        });
    }

    private long javaCalcTest(int left, int cnt) {
        long startTime = System.currentTimeMillis();
        Log.i(TAG, "startTime=" + startTime);
        int sum = left;
        for (int i = 0; i < cnt; i++) {
            sum += i;
        }
        long endTime = System.currentTimeMillis();
        long distance = endTime - startTime;
        Log.i(TAG, "endTime=" + endTime);
        Log.i(TAG, "distance=" + distance);
        return distance;
    }
}