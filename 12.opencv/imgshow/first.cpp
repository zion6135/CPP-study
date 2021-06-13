// mkdir build 
// cd build
// sudo cmake ..
// sudo make
// ./imgshow

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat srcImage = imread("/home/ts-ly/CPP-study/12.opencv/imgshow/opencv-logo.png");

    imshow("L7256",srcImage);

    //waitKey()是OpenCV中的内置函数，语句waitKey(0);表示“暂停程序，等待一个按键输入”！也就是说，当程序执行到waitKey(0);时，程序被暂停运行，只有当你输入一个按键时，它才会继续运行。
    waitKey(0);

    return 0;
}
