package com.example.jnilearn

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.example.jnilearn.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()

        dynamicNative();
        dynamicNative(123);
    }

    /**
     * A native method that is implemented by the 'jnilearn' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String
    external fun dynamicNative();
    external fun dynamicNative(i: Int): String

    companion object {
        // Used to load the 'jnilearn' library on application startup.
        init {
            System.loadLibrary("jnilearn")
        }
    }
}