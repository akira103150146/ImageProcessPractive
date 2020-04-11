//
// Created by akira on 2020-04-11.
//


#include "Helper.h"
#include "opencv2/opencv.hpp"

cv::Mat getGaussianMatrix(float sigma) {
     cv::Mat temp = (cv::Mat_<double>(3, 3) <<
             exp(-2), exp(-1), exp(-2),
             exp(-1), 1.0, exp(-1),
             exp(-2), exp(-1), exp(-2));

     double div = cv::sum(temp)[0];

     return temp / div;
}
