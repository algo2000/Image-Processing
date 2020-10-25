#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int ex05();
int ex06();
int ex07();
int ex08();
int ex09();
int ex10();
int ex11();
int ex12();
int ex13();
int ex14();

Mat img,roi;
int mx1,my1,mx2,my2;
bool cropping = false;

int main()
{
    ex14();
}

void ex14_onMouse(int event,int x, int y, int flags, void* param)
{
    if(event == EVENT_LBUTTONDOWN)
    {
        mx1 = x;
        my1 = y;
        cropping = true;
    }
    else if(event == EVENT_LBUTTONUP)
    {
        mx2 = x;
        my2 = y;
        cropping = false;
        rectangle(img, Rect(mx1,my1,mx2-mx1,my2-my1),Scalar(0,255,0),2);
        imshow("image",img);
    }
}

int ex14()
{
    img = imread("/Users/leo/Documents/학교 문서/영상처리/코드/code/ch03/Lenna.jpg");
    imshow("image",img);
    Mat clone=img.clone();

    setMouseCallback("image",ex14_onMouse);

    while (1)
    {
        int key = waitKey(100);
        if (key == 'q')
        {
            break;
        }
        else if (key == 'c')
        {
            try {
                roi = clone(Rect(mx1,my1,mx2-mx1,my2-my1));
                imwrite("/Users/leo/Documents/학교 문서/영상처리/코드/code/ch03/result.jpg",roi);
            }
            catch (cv::Exception) {

            }
        }
    }
}

int ex13()
{
    Mat LoadedImage = imread("/Users/leo/Documents/학교 문서/영상처리/코드/code/ch03/Lenna.jpg", IMREAD_COLOR);
    imshow("Original Image", LoadedImage);

    resize(LoadedImage,LoadedImage,Size(100,100));
    imshow("New Image",LoadedImage);

    waitKey(0);

    return 0;
}

int ex12()
{
    Mat img = imread("/Users/leo/Documents/학교 문서/영상처리/코드/code/ch03/Lenna.jpg");
    Mat roi(img,Rect(10,10,2,2));

    cout << "행의 수 = " <<roi.rows <<endl;
    cout << "열의 수 = " << roi.cols << endl;
    cout << "roi="<<endl<<roi<<endl<<endl;

    Rect r(10,10,2,2);
    Mat D = img(r);
    D = Scalar (0,0,0);
    imshow("img",img);
    waitKey(0);
    return 0;
}

int ex11()
{
    Mat A;
    A = imread("/Users/leo/Documents/학교 문서/영상처리/코드/code/ch03/Lenna.jpg",IMREAD_COLOR);
    Rect r(10,10,100,100);
    Mat D = A(r);
    D = Scalar(0,0,0);
    imshow("src",A);
    waitKey();
    return 0;
}

void ex10_sub(Mat img)
{
    img = Scalar(0,0,0);
}

int ex10()
{
    Mat A;
    A = imread("/Users/leo/Documents/학교 문서/영상처리/코드/code/ch03/Lenna.jpg",IMREAD_COLOR);

    imshow("before",A);
    ex10_sub(A);
    imshow("after",A);

    waitKey(0);
    return 0;
}

int ex09()
{
    Mat A;
    //메모리 할당사
    A = imread("/Users/leo/Documents/학교 문서/영상처리/코드/code/ch03/Lenna.jpg",IMREAD_COLOR);

    //clone 메소드를 이용한 깊은 복시 다른 메모리 풀에 할당
    Mat B = A.clone();
}

int ex08()
{
    Mat A;
    //메모리 할당
    A = imread("/Users/leo/Documents/학교 문서/영상처리/코드/code/ch03/Lenna.jpg",IMREAD_COLOR);

    //대입연사자를 통한 얕은 복사 수
    Mat B = A;
}

int ex07()
{
    Mat R = Mat(400,600,CV_8UC3);
    randu(R, Scalar::all(0),Scalar::all(255));
    imshow("img",R);
    waitKey(0);

    return 0;
}

int ex06()
{
    Mat C = (Mat_<double>(3,3) << 0,-1,0,-1,5,-1,0,-1,0);
    cout << "C = " <<endl << C <<endl<<endl;
}

int ex05()
{
    Mat E = Mat::eye(4,4,CV_64F);
    cout << "E" << endl << "" << E << endl << endl;

    Mat O = Mat::ones(2,2,CV_32F);
    cout << "O" << endl << "" << O << endl << endl;

    Mat Z = Mat::zeros(3,3,CV_8UC1);
    cout << "Z" << endl << "" << Z << endl << endl;
    return 0;
}