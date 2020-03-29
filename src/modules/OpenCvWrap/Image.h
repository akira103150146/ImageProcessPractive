//
// Created by akira on 2020-03-28.
//

#ifndef IMAGEPROCESSING_IMAGE_H
#define IMAGEPROCESSING_IMAGE_H

#include <opencv2/core/mat.hpp>
#include "string"
#include "Common.h"

using namespace std;
using namespace cv;

namespace wrap {
    typedef void (*WindowFunctor) (const Mat &windowMatrix, const Pixel &centerPixel);

    class Image {
    public:
        explicit Image(const string &path);

        explicit Image(cv::Mat image);

        ~Image();


        void showToWindow(const string &windowName);

        void printPixels();

        Image toGrayImage();

        Image toBlackWhiteImage();

        void iteratorWithWindow(const int &distance, const WindowFunctor &callback);

    private:
        cv::Mat image;
    };

    class WindowIterator {
    private:
        cv::Mat image;
        int distance;

        WindowFunctor callback;
    public:
        WindowIterator(const cv::Mat &image, const int &distance, const WindowFunctor &callback);

        ~WindowIterator();

        void operator()(const Pixel &pixel, const int *position) const;
    };
}

#endif //IMAGEPROCESSING_IMAGE_H
