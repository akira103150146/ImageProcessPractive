#include <fstream>
#include <filesystem>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "ProcessMethod.h"
#include "modules/OpenCvWrap/Image.h"

using namespace cv;
using namespace std;
using namespace wrap;

void makeWindow(const string &winName) {
    namedWindow(winName, WINDOW_GUI_EXPANDED);
}

void runThinning() {
    Image picture = Image("../images/h.png")
            .toGrayImage()
            .toZeroOneImage();

    picture.thinning();
    picture.toBlackWhiteImage()
            .showToWindow("Demo");
}

void runFindCornerPoint() {
    Image("../images/ntust.png")
    .toGrayImage()
    .gaussianFilter()
    .detectHarrisCorner(100.0)
    .showToWindow("Demo");
}

int main(int argc, char **argv) {
    makeWindow("Demo");
    runFindCornerPoint();

    waitKey(0);

    return 0;
}
