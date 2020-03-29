//
// Created by akira on 2020-03-28.
//

#include <opencv2/imgcodecs.hpp>
#include <utility>
#include "opencv2/opencv.hpp"
#include "Image.h"


using namespace cv;
using namespace wrap;

Image::Image(const std::string &path) {
    this->image = imread(path, ImreadModes::IMREAD_COLOR);
}

Image::Image(cv::Mat image) {
    this->image = std::move(image);
}

Image::~Image() = default;

void Image::showToWindow(const string &windowName) {
    imshow(windowName, this->image);
}

void Image::printPixels() {
    cout << this->image;
}

Image Image::toGrayImage() {
    Mat output;
    cvtColor(this->image, output, COLOR_BGR2GRAY);

    return Image(output);
}

Image Image::toBlackWhiteImage() {
    Mat output;
    threshold(this->image, output, 127, 255, THRESH_BINARY);

    return Image(output);
}

void Image::iteratorWithWindow(const int &distance, const WindowFunctor &callback) {
    this->image.forEach<Pixel>(WindowIterator(this->image, distance, callback));
}

WindowIterator::WindowIterator(const cv::Mat &image, const int &distance, const WindowFunctor &callback) {
    this->image = image;
    this->distance = distance;
    this->callback = callback;
}

WindowIterator::~WindowIterator() = default;

void WindowIterator::operator()(const Pixel &pixel, const int *position) const {
    int centerX = position[0];
    int centerY = position[1];
    int windowSize = this->distance * 2 + 1;
    Mat windowMat;

//    for (int y = centerY - windowSize; y <= centerY + windowSize; ++y) {
//        for (int x = centerX - windowSize; x <= centerX + windowSize; ++x) {
//            windowMat.this->image.at<Pixel>(y, x);
//        }
//    }
//    cout<<this->image.at<float>(centerY, centerX);


    this->callback(windowMat, pixel);
//            cout << cv::format("[%d,%d]= %d \n", position[0], position[1], (int) pixel.z);
}
