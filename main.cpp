#include <iostream>
#include "Buff.h"

using namespace std;
using namespace cv;

int main() {
    VideoCapture wind_video;
    wind_video.open("/home/yons/CLionProjects/HDU_Buff/wind.mp4");
    Detect detect;
    Mat srcimg;
    Point2f center(0,0);
    int status;


    Point2f offset_tmp;

    while (1)
    {
        wind_video>>srcimg;
        imshow("origin",srcimg);
        //detect.detect(srcimg,7,center,status);
        //detect.getArmorCenter_new(srcimg,3,detect.,offset_tmp);
        detect.detect_new(srcimg);
//        cout<<"侦测到的符文中心为: "<<center<<endl;
        waitKey();
    }
    return 0;
}
