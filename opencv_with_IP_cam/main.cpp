#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//HELLO SHAFIKOO
int main()
{
    VideoCapture cap;

    cap.open("http://192.168.1.3:8080/video?x.mjpeg");

    if(!cap.isOpened())
    {
        cout<<"sorry baby try again "<<endl;
        return -1;
    }

    namedWindow("ip",CV_WINDOW_AUTOSIZE);

    Mat frame;

    while(1)
    {

       bool s= cap.read(frame);

       if(!s)
       {
           cout<<"sorry baby i can't read "<<endl;
           break;
       }

        imshow("ip",frame);

        if(waitKey(30)==27)
        {
            cout<<"goodBye BABA " <<endl;
            break;
        }

    }

    return 0;
}
