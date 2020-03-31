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

    private:
        cv::Mat image;
    };

    class ThinningStrategyA {
    private:
        [[nodiscard]] inline uchar getPixel(int x, int y) const;

        inline void setPixel(uchar value, int x, int y) const;

        mutable cv::Mat inputSrc;

        mutable bool hasRemovePixel;

        mutable bool removeDirection;
    public:
        explicit ThinningStrategyA(cv::Mat &src);

        ~ThinningStrategyA();

        void operator()(const uchar &pixel, const int *position) const;

        inline bool isDone() const;

        inline void setImg(cv::Mat &src) const;

        inline void resetStatus() const;
    };
}

#endif //IMAGEPROCESSING_IMAGE_H
