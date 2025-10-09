# 🧠 EdgeViewer 

A **Real-time edge detection viewer** demonstrating full-stack integration across:

- 📌Android Camera feed (Camera2 / TextureView)
- 📌Native C++ processing via OpenCV
- 📌OpenGL ES 2.0 rendering
- 📌TypeScript web viewer for visual debug

  > Build with Android + OpenCV (C++) + OpenGL ES + Web (TypeScript)

---
  
   ## 🚀 Overview

**EdgeViewer** captures live camera frames, processes them in native C++ through **OpenCV**, applies **Canny edge detection**, and renders the processed frames in real-time using **OpenGL ES 2.0**.  
> A lightweight **TypeScript web viewer** displays a sample processed frame and FPS/resolution overlay.

<img width="1536" height="1024" alt="8eb3b412-ad07-431d-b861-3380b9a12ed4" src="https://github.com/user-attachments/assets/1e6ee9d3-a23b-4d15-baf0-bc52b4187432" />

---

## 🧩 Architecture

root
├── app/ # Android (Kotlin/Java) layer
│ ├── MainActivity.kt # Camera setup & TextureView
│ └── CameraUtils.kt # Camera2 helper methods

│
├── jni/ # Native C++ OpenCV processing
│ ├── image_processor.cpp
│ ├── image_processor.h
│ └── CMakeLists.txt

│
├── gl/ # OpenGL ES renderer
│ ├── GLRenderer.cpp
│ ├── GLRenderer.h
│ └── shaders/
│ ├── vertex_shader.glsl
│ └── fragment_shader.glsl
│

└── web/ # TypeScript web viewer
├── index.html
├── main.ts
├── tsconfig.json
└── dist/

---

### 🔄 Data Flow

1. **Camera2** → captures frame into `SurfaceTexture`
2. **JNI bridge** → passes frame buffer to native code
3. **OpenCV (C++)** → applies edge detection / grayscale filter
4. **OpenGL ES 2.0** → renders processed frame as texture

---


## ⚙️ Setup Instructions

### 📱 Android Project Setup

#### Requirements

- ✅Android Studio Giraffe+ / Koala
-✅Android NDK r26+
- ✅OpenCV Android SDK (4.8.0+)
-✅CMake, LLDB
- ✅Minimum SDK 24, Target SDK 34

#### Steps
1. Clone this repository:

  -git clone https://github.com/<your-username>/EdgeViewer.git
  - cd EdgeViewer
   
2. Extract and place OpenCV SDK under:
   
  - <project-root>/opencv/

 4. Add this to your local.properties:
    
 -sdk.dir=C:\\Users\\<you>\\AppData\\Local\\Android\\Sdk
-ndk.dir=C:\\Users\\<you>\\AppData\\Local\\Android\\Sdk\\ndk\\26.1.10909125

5. Sync and build:
   
-File → Sync Project with Gradle Files
-Build → Rebuild Project

 #✅Run 

-Connect an Android device → tap Run ▶
-You should see a live camera feed with edge-detected output.


 # ✅ JNI Flow:

-Java calls nativeProcessFrame(Mat input, Mat output)
-C++ applies OpenCV filters
-Output frame returned for OpenGL rendering

# 🎨 Rendering with OpenGL ES

The GLRenderer:

-✅Initializes vertex/fragment shaders
-✅Binds texture from processed image
-✅Draws frame using glDrawArrays(GL_TRIANGLE_STRIP, …)
-✅Ensures ≥ 15 FPS on mid-range devices

# 🌐 Web Viewer (TypeScript)

Located in /web/ — demonstrates the ability to visualize the processed frame on a browser.

# Features

-Displays a static sample image (Base64 / PNG)
-Shows FPS and resolution overlay
-Built with TypeScript, compiled via tsc

 # ✅Run

cd web
npm install
npm run build
npx serve dist


✅ Features Implemented

-Android Camera Feed (Camera2 / TextureView)	✅
-JNI Bridge (Java ↔ C++)	✅
-OpenCV Canny Edge Detection	✅
-OpenGL ES 2.0 Texture Rendering	✅
-TypeScript Web Viewer	✅


# 🧠 Architecture Summary

>Core Pipeline:

Camera Feed → JNI → OpenCV (C++) → OpenGL Renderer → Display
                                     ↓
                             Export → Web Viewer (TS)

-✅Android (Kotlin): Camera feed, JNI bridge, UI controls
-✅C++ (NDK): Image processing with OpenCV
-✅OpenGL ES: Efficient texture rendering
-✅TypeScript (Web): Visualization & debug interface


# 🧠 Author

RADHIKA RUNGTA

📧 radhikarungta61@gmail.com 
🌐 https://github.com/radhikarungta11

Built with ❤️ using Android Studio, NDK, OpenCV, OpenGL ES, and TypeScript.



