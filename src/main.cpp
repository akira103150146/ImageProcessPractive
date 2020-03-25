#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "ProcessMethod.h"

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
    auto img = imread("../images/images.png", IMREAD_COLOR);
    //create a gui window:
    const char *winName = "Demo";
    namedWindow(winName, WINDOW_GUI_EXPANDED);
    resizeWindow(winName, 800, 600);
    //display the image:0
//    imshow("Output", img);

    //wait for the user to press any key:
    waitKey(0);

    return 0;

}
