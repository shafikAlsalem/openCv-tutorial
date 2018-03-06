#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/* my tennisBall HSV scalar

Hue :28 -> 43
saturation :47 -> 160
value :47 -> 255

*/

/* hough arguments:

    gray: Input image (grayscale).
    circles: A vector that stores sets of 3 values: xc,yc,r for each detected circle.
    HOUGH_GRADIENT: Define the detection method. Currently this is the only one available in OpenCV.
    dp = 1: The inverse ratio of resolution.
    min_dist = gray.rows/16: Minimum distance between detected centers.
    param_1 = : Upper threshold for the internal Canny edge detector.
    param_2 = *: Threshold for center detection.
    min_radius = 0: Minimum radius to be detected. If unknown, put zero as default.
    max_radius = 0: Maximum radius to be detected. If unknown, put zero as default

    for our application are
       bw, circles, HOUGH_GRADIENT, 1,
                 bw.rows/8,
                 250, 18, 20, 100
    */


Scalar minS=Scalar(28,47,47);
Scalar maxS=Scalar(43,160,255);



int main()
{
    VideoCapture cap;

    cap.open("http://192.168.1.5:8080/video?x.mjpeg");

    if(!cap.isOpened())
    {
        cout<<"sorry baby try again "<<endl;
        return -1;
    }

    namedWindow("ip",CV_WINDOW_AUTOSIZE);
  namedWindow("binary",CV_WINDOW_AUTOSIZE);

namedWindow("HSV",CV_WINDOW_AUTOSIZE);





    Mat frame,hsvImg,bw;


    while(1)
    {

       bool s= cap.read(frame);

       if(!s)
       {
           cout<<"sorry baby i can't read "<<endl;
           break;
       }

       cvtColor(frame,hsvImg,CV_BGR2HSV);

      inRange(hsvImg,minS,maxS,bw);
    GaussianBlur(bw,bw,Size(9,9),2);



    vector<Vec3f> circles;
    HoughCircles(bw, circles, HOUGH_GRADIENT, 1,
                 bw.rows/8,
                 250, 18, 20, 100);

    for(size_t i=0;i<circles.size();i++)
    {
        Vec3i c=circles[i];
        int x,y,r;
        x=c[0];
        y=c[1];
        r=c[2];

        circle(frame,Point(x,y),r,Scalar(0,45,0),3);
        line(frame,Point(x-r,y),Point(x+r,y),Scalar(0,0,215),3);
        line(frame,Point(x,y-r),Point(x,y+r),Scalar(0,0,215),3);
    }


        imshow("ip",frame);
        imshow("HSV",hsvImg);
        imshow("binary",bw);

        if(waitKey(30)==27)
        {
            cout<<"goodBye BABA " <<endl;
            break;
        }

    }

    return 0;
}
