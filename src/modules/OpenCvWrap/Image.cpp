//
// Created by akira on 2020-03-28.
//

#include <opencv2/imgcodecs.hpp>
#include <utility>
#include "opencv2/opencv.hpp"
#include "Image.h"
#include "chrono"

using namespace cv;
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

Image Image::toGrayImage() {
    Mat output;
    cvtColor(image, output, COLOR_BGR2GRAY);

    return Image(output);
}

Image Image::toZeroOneImage() {
    Mat output;
    threshold(image, output, 127, 1, THRESH_BINARY);

    return Image(output);
}

Image Image::toBlackWhiteImage() {
    Mat output;
    threshold(image, output, 0.5, 255, THRESH_BINARY);

    return Image(output);
}

void Image::thinning() {
    auto start = chrono::steady_clock::now();
    int count = 0;
    bool hasRemovePixel = false;
    bool removeDirection = true;

    while (true) {
        image.forEach<uchar>([&hasRemovePixel, &removeDirection, this](const uchar &pixel, const int *position) {
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
            int centerX = position[0];
            int centerY = position[1];

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
            int left = p2 && p4 && p8;
            int down = p4 && p6 && p8;


            if (removeDirection) {
                if (nonZeroCount >= 2 && nonZeroCount <= 6 && (transformation == 1) && (right == 0) && (upper == 0)) {
                    setPixel(0, centerX, centerY);
                    hasRemovePixel = true;
                    removeDirection = !removeDirection;
                }
            } else {
                if (nonZeroCount >= 2 && nonZeroCount <= 6 && (transformation == 1) && (left == 0) && (down == 0)) {
                    setPixel(0, centerX, centerY);
                    hasRemovePixel = true;
                    removeDirection = !removeDirection;
                }
            }
        });
        count++;

        if (! hasRemovePixel) {
            break;
        }

        hasRemovePixel = false;
        removeDirection = true;
    }

    auto end = chrono::steady_clock::now();
    cout << "Count: " << count << endl;
    cout << "cost time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() / 1000.0 << "s" << endl;

}

void Image::setPixel(uchar value, int x, int y) const {
    image.data[y * image.cols + x] = value;
}

uchar Image::getPixel(int x, int y) const {
    int rows = image.rows;
    int cols = image.cols;
    int index = y * image.cols + x;

    if (index < 0 || index > rows * cols - 1) return uchar(0);

    return image.data[index];
}

