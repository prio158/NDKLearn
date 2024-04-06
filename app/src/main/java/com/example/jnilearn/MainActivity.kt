package com.example.jnilearn

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.example.jnilearn.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    private val property = 1024

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()

        dynamicNative();
        dynamicNative(123);
        val clazz = GetThis()
        if (clazz == null) {
            Log.e(TAG, "GetThis Fail")
        }

        val tmp = stringFromJNITest("MainActivity-Java-In")
        Log.i(TAG, "Native Return:$tmp")

        Log.i(TAG, "findJavaPropertyFromJNI Before:$property")
        findJavaPropertyFromJNI()
        Log.i(TAG, "findJavaPropertyFromJNI After:$property")

        Log.i(TAG, "findJavaStaticPropertyFromJNI Before:$Property")
        findJavaStaticPropertyFromJNI()
        Log.i(TAG, "findJavaStaticPropertyFromJNI After:$Property")

        callJavaStaticMethod();
    }

    /**
     * A native method that is implemented by the 'jnilearn' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String
    external fun dynamicNative()
    external fun dynamicNative(i: Int): String
    external fun findJavaPropertyFromJNI()
    external fun findJavaStaticPropertyFromJNI()
    external fun callJavaStaticMethod()

    fun callClassMethod(str: String, index: Int) {
        Log.i(TAG, "callClassMethod:${str},${index}")
    }

    companion object {

        private const val TAG = "JNI-->"

        private val Property = 4096

        // Used to load the 'jnilearn' library on application startup.
        init {
            System.loadLibrary("jnilearn")
        }

        external fun stringFromJNITest(str: String): String

        fun GetThis() = runCatching {
            val clazz = Class.forName("com.example.jnilearn.MainActivity")
            Log.i(TAG, "GetThis:${clazz}")
            clazz
        }.getOrNull()

        @JvmStatic
        fun callVoidStaticMethod(str: String, index: Int) {
            Log.i(TAG, "callVoidStaticMethod:${str},${index}")
        }

    }

}