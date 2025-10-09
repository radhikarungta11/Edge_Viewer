package gl

import android.opengl.GLES20
import android.opengl.GLSurfaceView
import java.nio.*
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class GLRenderer : GLSurfaceView.Renderer {
    private var program = 0
    private var texId = 0
    private var posLoc = 0
    private var texLoc = 0
    private var samplerLoc = 0

    private val quad: FloatBuffer = ByteBuffer.allocateDirect(4*4*4)
        .order(ByteOrder.nativeOrder()).asFloatBuffer().apply {
            put(floatArrayOf(
                -1f,-1f, 0f,1f,
                 1f,-1f, 1f,1f,
                -1f, 1f, 0f,0f,
                 1f, 1f, 1f,0f
            ))
            position(0)
        }

    @Volatile private var pixels: ByteBuffer? = null
    @Volatile var width = 0; @Volatile var height = 0

    fun updatePixels(buf: ByteBuffer, w: Int, h: Int) {
        width = w; height = h; buf.rewind(); pixels = buf
    }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        val v = ShaderUtils.load("""
            attribute vec4 aPos;
            attribute vec2 aTex;
            varying vec2 vTex;
            void main(){ gl_Position=aPos; vTex=aTex; }
        """.trimIndent(), GLES20.GL_VERTEX_SHADER)

        val f = ShaderUtils.load("""
            precision mediump float;
            varying vec2 vTex;
            uniform sampler2D uTex;
            void main(){ gl_FragColor = texture2D(uTex, vTex); }
        """.trimIndent(), GLES20.GL_FRAGMENT_SHADER)

        program = ShaderUtils.link(v, f)
        posLoc = GLES20.glGetAttribLocation(program, "aPos")
        texLoc = GLES20.glGetAttribLocation(program, "aTex")
        samplerLoc = GLES20.glGetUniformLocation(program, "uTex")

        val ids = IntArray(1)
        GLES20.glGenTextures(1, ids, 0)
        texId = ids[0]
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, texId)
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR)
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR)
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_CLAMP_TO_EDGE)
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_CLAMP_TO_EDGE)
    }

    override fun onSurfaceChanged(gl: GL10?, w: Int, h: Int) {
        GLES20.glViewport(0,0,w,h)
    }

    override fun onDrawFrame(gl: GL10?) {
        GLES20.glClearColor(0f,0f,0f,1f)
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT)

        val px = pixels ?: return
        if (width <= 0 || height <= 0) return

        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, texId)
        px.rewind()
        GLES20.glTexImage2D(
            GLES20.GL_TEXTURE_2D, 0, GLES20.GL_RGBA,
            width, height, 0, GLES20.GL_RGBA, GLES20.GL_UNSIGNED_BYTE, px
        )

        GLES20.glUseProgram(program)
        quad.position(0)
        GLES20.glVertexAttribPointer(posLoc, 2, GLES20.GL_FLOAT, false, 16, quad)
        GLES20.glEnableVertexAttribArray(posLoc)
        quad.position(2)
        GLES20.glVertexAttribPointer(texLoc, 2, GLES20.GL_FLOAT, false, 16, quad)
        GLES20.glEnableVertexAttribArray(texLoc)
        GLES20.glUniform1i(samplerLoc, 0)
        GLES20.glDrawArrays(GLES20.GL_TRIANGLE_STRIP, 0, 4)
    }
}
