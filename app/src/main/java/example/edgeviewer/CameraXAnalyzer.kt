package com.example.edgeviewer

import android.graphics.ImageFormat
import androidx.camera.core.ImageAnalysis
import androidx.camera.core.ImageProxy
import java.nio.ByteBuffer

class CameraXAnalyzer(
    private val outRgba: ByteBuffer,
    private val onFrameDone: (Int, Int) -> Unit,
    var doCanny: Boolean
) : ImageAnalysis.Analyzer {
    override fun analyze(image: ImageProxy) {
        try {
            if (image.format != ImageFormat.YUV_420_888) { image.close(); return }
            val y = image.planes[0]
            NativeBridge.processYToRgba(
                y.buffer, image.width, image.height, y.rowStride, doCanny, outRgba
            )
            onFrameDone(image.width, image.height)
        } finally { image.close() }
    }
}
