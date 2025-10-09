#pragma once
#include <vector>

namespace ImageProcessor {
    // Produces Android ARGB_8888 ints (A<<24 | R<<16 | G<<8 | B)
    void nv21ToEdgesARGB(const unsigned char* nv21,
                         int width, int height, int rotateDegrees,
                         std::vector<int>& outARGB);
}
