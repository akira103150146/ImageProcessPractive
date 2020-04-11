cmake_minimum_required(VERSION 3.13)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 17)

add_executable(ImageProcessing src/main.cpp include/ProcessMethod.h src/modules/OpenCvWrap/Image.cpp src/modules/OpenCvWrap/Image.h src/modules/OpenCvWrap/Helper.cpp src/modules/OpenCvWrap/Helper.h)
include_directories(include)

set(OpenCV_DIR ${CMAKE_CURRENT_LIST_DIR}/packages/opencv/build)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( ImageProcessing ${OpenCV_LIBS} )
