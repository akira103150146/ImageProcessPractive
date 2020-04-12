//
// Created by akira on 2020-03-28.
//

#include <opencv2/imgcodecs.hpp>
#include <utility>
#include "opencv2/opencv.hpp"
#include "Image.h"
#include "chrono"
#include "Helper.h"

using namespace wrap;

Image::Image(const std::string &path) {
    image = imread(path, ImreadModes::IMREAD_COLOR);
}

Image::Image(cv::Mat img) {
    image = std::move(img);
}

Image::~Image() = default;

void Image::showToWindow(const string &windowName) {
    imshow(windowName, image);
}

void Image::printPixels() {
    cout << image;
}

Image &Image::toGrayImage() {
    cvtColor(image, image, COLOR_BGR2GRAY);

    return *this;
}

Image &Image::toZeroOneImage() {
    threshold(image, image, 127, 1, THRESH_BINARY);

    return *this;
}

Image &Image::toBlackWhiteImage() {
    threshold(image, image, 0.5, 255, THRESH_BINARY);

    return *this;
}

void Image::thinning() {
    auto start = chrono::steady_clock::now();
    int count = 0;
    bool hasRemovePixel = false;

    while (true) {
        Mat removeMask1 = Mat::zeros(image.rows, image.cols, CV_8U);
        image.forEach<uchar>([&hasRemovePixel, &removeMask1, this](const uchar &pixel, const int *position) {
            // ONLY REMOVE WHITE PIXEL
            if (pixel == uchar(0)) {
                return;
            }
            /**
             *   P1  P2  P3
             *   P4  P5* P6
             *   P7  P8  P9
             */
            int centerX = position[1];
            int centerY = position[0];

            uchar p1 = getPixel(centerX - 1, centerY - 1);
            uchar p2 = getPixel(centerX, centerY - 1);
            uchar p3 = getPixel(centerX + 1, centerY - 1);
            uchar p4 = getPixel(centerX - 1, centerY);
            uchar p6 = getPixel(centerX + 1, centerY);
            uchar p7 = getPixel(centerX - 1, centerY + 1);
            uchar p8 = getPixel(centerX, centerY + 1);
            uchar p9 = getPixel(centerX + 1, centerY + 1);

            int nonZeroCount = p1 + p2 + p3 + p4 + p6 + p7 + p8 + p9;
            int transformation =
                    (!p1 && p2) +
                    (!p2 && p3) +
                    (!p3 && p6) +
                    (!p6 && p9) +
                    (!p9 && p8) +
                    (!p8 && p7) +
                    (!p7 && p4) +
                    (!p4 && p1);

            int right = p2 && p6 && p8;
            int upper = p2 && p4 && p6;

            if (nonZeroCount >= 2 && nonZeroCount <= 6 && (transformation == 1) && (right == 0) && (upper == 0)) {
                removeMask1.data[centerY * image.cols + centerX] = 1;
                hasRemovePixel = true;
            }

        });
        image.setTo(0, removeMask1);


        Mat removeMask2 = Mat::zeros(image.rows, image.cols, CV_8U);
        image.forEach<uchar>([&hasRemovePixel, &removeMask2, this](const uchar &pixel, const int *position) {
            // ONLY REMOVE WHITE PIXEL
            if (pixel == uchar(0)) {
                return;
            }
            /**
             *   P1  P2  P3
             *   P4  P5* P6
             *   P7  P8  P9
             *
             */
            int centerX = position[1];
            int centerY = position[0];

            uchar p1 = getPixel(centerX - 1, centerY - 1);
            uchar p2 = getPixel(centerX, centerY - 1);
            uchar p3 = getPixel(centerX + 1, centerY - 1);
            uchar p4 = getPixel(centerX - 1, centerY);
            uchar p6 = getPixel(centerX + 1, centerY);
            uchar p7 = getPixel(centerX - 1, centerY + 1);
            uchar p8 = getPixel(centerX, centerY + 1);
            uchar p9 = getPixel(centerX + 1, centerY + 1);

            int nonZeroCount = p1 + p2 + p3 + p4 + p6 + p7 + p8 + p9;
            int transformation =
                    (!p1 && p2) +
                    (!p2 && p3) +
                    (!p3 && p6) +
                    (!p6 && p9) +
                    (!p9 && p8) +
                    (!p8 && p7) +
                    (!p7 && p4) +
                    (!p4 && p1);

            int left = p2 && p4 && p8;
            int down = p4 && p6 && p8;

            if (nonZeroCount >= 2 && nonZeroCount <= 6 && (transformation == 1) && (left == 0) && (down == 0)) {
                removeMask2.data[centerY * image.cols + centerX] = 1;
                hasRemovePixel = true;
            }

        });
        image.setTo(0, removeMask2);

        count++;

        if (!hasRemovePixel) {
            break;
        }

        hasRemovePixel = false;
    }

    auto end = chrono::steady_clock::now();
    cout << "Count: " << count << endl;
    cout << "cost time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() / 1000.0 << "s" << endl;

}

void Image::setPixel(uchar value, int x, int y) const {
    image.data[y * image.cols + x] = value;
}

void Image::setPixel(double value, int x, int y) const {
    image.data[y * image.cols + x] = value;
}

uchar Image::getPixel(int x, int y) const {
    int rows = image.rows;
    int cols = image.cols;
    int index = y * image.cols + x;

    if (index < 0 || index > rows * cols - 1) return uchar(0);

    return image.data[index];
}

Image &Image::gaussianFilter() {
    Mat G = getGaussianMatrix(0.707);
    Image result = Image(Mat::zeros(image.rows, image.cols, CV_8U));

    image.forEach<double>([&G, &result, this](const double &pixel, const int *position) {
        const int x = position[1];
        const int y = position[0];

        Mat neighbor;
        getNeighbor(x, y, 3).convertTo(neighbor, CV_64F);
        const double neighbor_sum = sum(neighbor)[0];

        if (!neighbor.empty()) {
            const double m_sum = sum(neighbor * G)[0];
            result.setPixel(m_sum * (m_sum / neighbor_sum), x, y);
        } else {
            result.setPixel(pixel, x, y);
        }
    });

    result.image.assignTo(image, CV_8U);

    return *this;
}

Mat Image::getNeighbor(int x, int y, int size) const {
    const int rad = size / 2;

    try {
        return image(Rect(x - rad, y - rad, size, size));
    } catch (Exception &e) {
        // ignore out of bound
        return Mat();
    }
}

Image &Image::detectHarrisCorner(double sigma) {
    Mat dst = Mat::zeros(image.size(), CV_64F);

    image.forEach<uchar>([this, &dst, sigma](const uchar &pixel, const int *position) {
        const int x = position[1];
        const int y = position[0];
        /**
         *    p1 p2
         * p3 p4 p5
         *    p6
         */
        const uchar p1 = getPixel(x, y - 1);
        const uchar p2 = getPixel(x + 1, y - 1);
        const uchar p3 = getPixel(x - 1, y);
        const uchar p4 = getPixel(x, y);
        const uchar p5 = getPixel(x + 1, y);
        const uchar p6 = getPixel(x, y + 1);
        const auto A = (double) (p5 + p3 - 2 * p4);
        const auto B = (double) (p1 + p6 - 2 * p4);
        const auto C = (double) (p4 + p2 - p1 - p5);

        Mat M = (Mat_<double>(2, 2) << A, C, C, B);

        double d = determinant(M) - 0.04 * pow(trace(M)[0], 2);
        dst.data[y * dst.cols + x] = d;

        if (d > sigma) {
            circle(
                    dst,
                    Point(x, y),
                    1,
                    Scalar(255),
                    2,
                    LineTypes::LINE_8,
                    0
            );
        }
    });

    dst.assignTo(image, CV_8U);

    return *this;
}

