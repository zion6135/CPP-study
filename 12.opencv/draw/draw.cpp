//编译步骤： mkdir build 
// cd build
// sudo cmake ..
// sudo make
// ./draw
// 运行----点击任意非ESC按键----鼠标开始框选
#include<iostream>
#include <cstdio>
#include <cstdlib>
#include <opencv2/opencv.hpp>

#define WINDOW_NAME "program_window"

using namespace cv;
using namespace std;

void on_MouseHandle(int event, int x, int y, int flags, void* param); //对鼠标触发事件进行判断处理
void DrawRectangle(cv::Mat& img, cv::Rect box); //画出矩形

int cnt;
Rect g_rectangle;           
bool g_bDrawingBox = false;//是否进行绘制
RNG g_rng(12345);          //Scalar格式

int main(int argc, char **argv)
{
        // [1]初始化参数
    cnt = 0;
    g_rectangle = Rect(-1, -1, 0, 0);  

    Mat srcImage = cv::imread("/home/zion/CPP-study/12.opencv/draw/lufei.jpeg");
    Mat tempImage;

    imshow("L7256",srcImage);
    //waitKey()是OpenCV中的内置函数，语句waitKey(0);表示“暂停程序，等待一个按键输入”！也就是说，当程序执行到waitKey(0);时，程序被暂停运行，只有当你输入一个按键时，它才会继续运行。
    waitKey(0);

    if ( !srcImage.data ) printf("read image fail!\n");

    srcImage.copyTo(tempImage);

//  g_rectangle = Rect(-1, -1, 0, 0);
//  srcImage = Scalar::all(0);       
        // [2]设置鼠标操作回调函数
    namedWindow(WINDOW_NAME);
    setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&srcImage);

        // [3]开始判断是否进行绘制操作
    while(1) {
        srcImage.copyTo(tempImage); //复制源图到临时变量
        if( g_bDrawingBox ) DrawRectangle( tempImage, g_rectangle);

        imshow(WINDOW_NAME, tempImage);
        if (waitKey(10) == 27) break; //按下ESC键，程序退出
    }

    return 0;
}

//  鼠标回调函数，根据不同的鼠标事件进行不同的操作 
void on_MouseHandle(int event, int x, int y, int flags, void* param) {
    Mat& image = *(cv::Mat*) param;
    // printf("----------<x,y>-----------\n");
    // printf("cnt = %d, <%d %d>\n", ++cnt, x, y);
    //     printf("----------<x,y>-----------\n");
    switch( event ) {
            // 鼠标移动消息     
        case EVENT_MOUSEMOVE:{
                                 if (g_bDrawingBox) { 
                                  //绘制标识为真，则记录下长和宽到RECT变量中
                                     g_rectangle.width = x - g_rectangle.x;
                                     g_rectangle.height = y - g_rectangle.y;
                                 }
                             }
                             break;
        //左键按下消息
       case EVENT_LBUTTONDOWN:{ 
                                    g_bDrawingBox = true;
                                    g_rectangle = Rect(x, y, 0, 0);
                                    printf("start post: x = %d, y = %d\n", x, y );
                              }
                              break;
        //左键抬起消息
      case EVENT_LBUTTONUP: {
                                g_bDrawingBox = false;
                                if (g_rectangle.width < 0) {
                                    g_rectangle.x += g_rectangle.width;
                                    g_rectangle.width *= -1;
                                }

                                if (g_rectangle.height < 0) {
                                    g_rectangle.y += g_rectangle.height;
                                    g_rectangle.height *= -1;
                                }

                                DrawRectangle(image, g_rectangle );
                                printf("x       = %d\n", g_rectangle.x );
                                printf("y       = %d\n", g_rectangle.y );
                                printf("width   = %d\n", g_rectangle.width );
                                printf("height  = %d\n", g_rectangle.height );
                            }
                            break;
     default: printf("error!\n");
    }
}

//自定义的矩形绘制函数
void DrawRectangle(cv::Mat& img, cv::Rect box){
    rectangle(img, box.tl(), box.br(), Scalar(0,255,255), 2, 1, 0);
}

