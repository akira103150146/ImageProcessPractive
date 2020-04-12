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
    makeWindow("Demo");
    makeWindow("Harris");

    auto image = Image("../images/ntust.png");
    image.showToWindow("Demo");
    image
    .toGrayImage()
    .gaussianFilter()
    .detectHarrisCorner(255.0)
    .showToWindow("Harris");
}

int main(int argc, char **argv) {
    runFindCornerPoint();

    waitKey(0);

    return 0;
}
