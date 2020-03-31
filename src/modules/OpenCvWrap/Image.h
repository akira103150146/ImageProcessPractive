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
    class Image {
    public:
        explicit Image(const string &path);

        explicit Image(cv::Mat image);

        ~Image();

        void showToWindow(const string &windowName);

        void printPixels();

        Image toGrayImage();

        Image toZeroOneImage();

        Image toBlackWhiteImage();

        void thinning();

        [[nodiscard]] inline uchar getPixel(int x, int y) const;

        inline void setPixel(uchar value, int x, int y) const;

    private:
        cv::Mat image;
    };
}

#endif //IMAGEPROCESSING_IMAGE_H
