
package com.example.edgeviewer
import java.nio.ByteBuffer

object NativeBridge {
    init { System.loadLibrary("image_processor") }

    external fun processYToRgba(
        yPlane: ByteBuffer,
        width: Int,
        height: Int,
        rowStride: Int,
        doCanny: Boolean,
        outRgba: ByteBuffer
    )
}
