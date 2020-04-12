//
// Created by akira on 2020-04-11.
//


#include "Helper.h"
#include "opencv2/opencv.hpp"

cv::Mat getGaussianMatrix(float sigma) {
    const double beta = 2 * pow(sigma, 2);

    cv::Mat G =  (cv::Mat_<double>(3, 3) <<
            exp(-2 / beta), exp(-1 / beta), exp(-2 / beta),
            exp(-1 / beta), exp(0), exp(-1 / beta),
            exp(-2 / beta), exp(-1/ beta), exp(-2 / beta));

    return G / sum(G)[0];
}
