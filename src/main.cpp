#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "ProcessMethod.h"
#include "modules/OpenCvWrap/Image.h"

using namespace cv;
using namespace std;
using namespace wrap;

int main(int argc, char **argv) {
    Image picture = Image("../images/horse.png")
            .toGrayImage()
            .toZeroOneImage();

    picture.thinning();

//    const char *winName = "Demo";
//    namedWindow(winName, WINDOW_GUI_EXPANDED);
//
//    picture.toBlackWhiteImage()
//            .showToWindow("Demo");
//
//    waitKey(0);

    return 0;

}
