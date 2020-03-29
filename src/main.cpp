#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "ProcessMethod.h"
#include "modules/OpenCvWrap/Image.h"

using namespace cv;
using namespace std;
using namespace wrap;

int main(int argc, char **argv) {
    Image picture = Image("../images/images.png")
            .toGrayImage()
            .toBlackWhiteImage();

    //create a gui window:
//    const char *winName = "Demo";
//    namedWindow(winName, WINDOW_GUI_EXPANDED);

//    picture.printPixels();
    picture.iteratorWithWindow(1, [](const Mat &windowMatrix, const Pixel &centerPixel) {
        cout << format("[%d]", (int) centerPixel.z);
    });

//    //display the image:0
//    picture.showToWindow("Demo");
//    picture.printPixels();

    //wait for the user to press any key:
//    waitKey(0);

    return 0;

}
