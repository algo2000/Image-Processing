#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int ex01();
int ex02();
int ex03();
int ex04();
int ex05();
int ex06();
int ex07();
int ex08();
int ex09();
int ex10();
int ex10();
int ex11();
int ex12();
int ex13();
int ex14();
int ex15();

string imgFolderLink = "/Users/leo/Documents/학교 문서/영상처리/코드/code/images/";

int main()
{
    ex05();
}

int ex05()
{
    Mat src = imread(imgFolderLink + "lenna.jpg", IMREAD_COLOR);

    Mat dst;
    float weights[9] = {-1,-1,-1,-1,9,-1,-1,-1,-1};
    Mat mask = Mat(3,3,CV_32F,weights);

    filter2D(src,dst,-1,mask,Point(-1,-1),0,BORDER_DEFAULT);
    imshow("src",src);
    imshow("sharpen",dst);

    waitKey(0);
    return 0;
}

int ex04()
{
    Mat src = imread(imgFolderLink + "lenna.jpg",1);
    Mat dst;
    imshow("src",src);

    for (int i = 1; i < 61; i = i + 2)
    {
        GaussianBlur(src,dst,Size(i,i),0,0);
        imshow("Gaussian filter",dst);
        waitKey(1000);
    }
}

int ex03()
{
    Mat src = imread(imgFolderLink + "dog.jpg");
    Mat dst;

    blur(src,dst,Size(31,31));
    imshow("source",src);
    imshow("result",dst);

    waitKey(0);
    return 0;
}

int ex02()
{
    Mat image = imread(imgFolderLink + "lenna.jpg",IMREAD_GRAYSCALE);

    float weights[] = {
            1/9.0F,1/9.0F,1/9.0F,
            1/9.0F,1/9.0F,1/9.0F,
            1/9.0F,1/9.0F,1/9.0F
    };

    Mat mask(3, 3, CV_32F, weights);
    Mat blur;
    filter2D(image,blur,-1,mask);
    blur.convertTo(blur,CV_8U);

    imshow("image",image);
    imshow("blur",blur);

    waitKey(0);
    return 0;
}

int ex01()
{
    Mat src = imread(imgFolderLink + "lenna.jpg",IMREAD_GRAYSCALE);
    Mat dst(src.size(), CV_8U, Scalar(0));
    if(src.empty())
    {
        return -1;
    }

    for (int y = 0; y < src.rows; ++y)
    {
        for (int x = 0; x < src.cols; ++x)
        {
            int sum = 0;
            sum += src.at<uchar>(y - 1,x - 1);
            sum += src.at<uchar>(y,x - 1);
            sum += src.at<uchar>(y + 1,x - 1);
            sum += src.at<uchar>(y - 1,x);
            sum += src.at<uchar>(y,x);
            sum += src.at<uchar>(y + 1,x);
            sum += src.at<uchar>(y - 1,x + 1);
            sum += src.at<uchar>(y,x + 1);
            sum += src.at<uchar>(y + 1,x + 1);
            dst.at<uchar>(y,x) = sum / 9;
        }
    }
    imshow("Original Image", src);
    imshow("New Image",dst);
    waitKey(0);
    return 0;
}