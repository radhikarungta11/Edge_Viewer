#include "image_processor.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>


using namespace cv;

static void nv21ToBgr(const unsigned char* nv21, int width, int height, cv::Mat& bgr) {
    Mat yuv(height + height/2, width, CV_8UC1, (void*)nv21);
    cv::cvtColor(yuv, bgr, cv::COLOR_YUV2BGR_NV21);
}

namespace ImageProcessor {

void nv21ToEdgesARGB(const unsigned char* nv21,
                     int width, int height, int rotateDegrees,
                     std::vector<int>& outARGB) {
    Mat bgr;
    nv21ToBgr(nv21, width, height, bgr);

    // Handle rotation from camera metadata
    if (rotateDegrees == 90) {
        cv::rotate(bgr, bgr, cv::ROTATE_90_CLOCKWISE);
    } else if (rotateDegrees == 180) {
        cv::rotate(bgr, bgr, cv::ROTATE_180);
    } else if (rotateDegrees == 270) {
        cv::rotate(bgr, bgr, cv::ROTATE_90_COUNTERCLOCKWISE);
    }

    Mat gray, blurred, edges;
    cv::cvtColor(bgr, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, blurred, Size(5,5), 1.5);
    cv::Canny(blurred, edges, 80, 160);

    // RGBA image: white edges on black
    Mat rgba(edges.size(), CV_8UC4, Scalar(0,0,0,255));
    rgba.setTo(Scalar(0,0,0,255));
    rgba.setTo(Scalar(255,255,255,255), edges);

    // Pack into Android ARGB_8888 ints
    outARGB.resize(rgba.rows * rgba.cols);
    for (int y = 0; y < rgba.rows; ++y) {
        const Vec4b* row = rgba.ptr<Vec4b>(y); // RGBA
        for (int x = 0; x < rgba.cols; ++x) {
            const Vec4b& p = row[x];
            int a = p[3], r = p[0], g = p[1], b = p[2];
            outARGB[y*rgba.cols + x] = (a<<24) | (r<<16) | (g<<8) | b;
        }
    }
}

} // namespace ImageProcessor
