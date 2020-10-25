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
    ex06();
}

int ex06()
{
    Mat src,dst;

    src = imread(imgFolderLink + "plane.jpg",IMREAD_GRAYSCALE);
    imshow("Image",src);
    if (!src.data)
    {
        return -1;
    }

    Mat threshold_image;
    threshold(src,threshold_image,100,255,THRESH_BINARY);
    imshow("Thresholded Image",threshold_image);
    waitKey(0);
    return 0;
}

int ex02_drawHist(int histogram[]);

int ex05()
{
    Mat src = imread(imgFolderLink + "crayfish.jpg", IMREAD_GRAYSCALE);
    if (src.empty())
    {
        return -1;
    }

    int histogram[256] = {0};

    for (int y = 0; y < src.rows; ++y)
    {
        for (int x = 0; x < src.cols; ++x)
        {
            histogram[(int)src.at<uchar>(y,x)]++;
        }
    }
    ex02_drawHist(histogram);

    Mat dst;
    equalizeHist(src,dst);

//    histogram[256] = {0};
//
//    for (int y = 0; y < dst.rows; ++y)
//    {
//        for (int x = 0; x < dst.cols; ++x)
//        {
//            histogram[(int)dst.at<uchar>(y,x)]++;
//        }
//    }
//    ex02_drawHist(histogram);

    imshow("Image",src);
    imshow("Equalized",dst);
    waitKey(0);
    return 0;
}

int ex04_stretch(int x, int r1, int s1, int r2, int s2)
{
    float result;
    if (0 <= x && x<= r1)
    {
        result = s1/r1 * x;
    }
    else if (r1 < x && x <= r2)
    {
        result = ((s2-s1) / (r2-r1)) * (x - r1) + s1;
    }
    else if (r2 < x && x <= 255)
    {
        result = ((255-s2) / (255 - r2)) * (x - r2) + s2;
    }

    return (int)result;
}

int ex04()
{
    Mat image = imread(imgFolderLink + "crayfish.jpg");
    Mat new_image = image.clone();

    int r1,s1,r2,s2;
    cout << "r1를 입력하시오 : ";
    cin >> r1;
    cout << "s1를 입력하시오 : ";
    cin >> s1;
    cout << "r2를 입력하시오 : ";
    cin >> r2;
    cout << "s2를 입력하시오 : ";
    cin >> s2;

    for (int y = 0; y < image.rows; ++y)
    {
        for (int x = 0; x < image.cols; ++x)
        {
            for (int c = 0; c < 3; ++c)
            {
                int output = ex04_stretch(image.at<Vec3b>(y,x)[c], r1,s1,r2,s2);
                new_image.at<Vec3b>(y,x)[c] = saturate_cast<uchar>(output);
            }
        }
    }
    imshow("Input Image",image);
    imshow("Output Image",new_image);
    waitKey(0);
    return 0;
}

int ex03()
{
    Mat src = imread(imgFolderLink + "lenna.jpg",IMREAD_COLOR);
    if (src.empty())
    {
        return -1;
    }

    vector<Mat> bgr_planes; // 영상들의 벡터
    split(src, bgr_planes); //입력 영상을 색상별로 분리
    int histSize = 256;
    float range[] = {0,256}; //화소값의 범위
    const float* histRange = {range};
    bool uniform = true, accumulate = false;
    Mat b_hist,g_hist,r_hist;

    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist,1,&histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist,1,&histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist,1,&histSize, &histRange, uniform, accumulate);

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w/histSize);
    Mat histImage(hist_h,hist_w,CV_8UC3,Scalar(0,0,0));

    normalize(b_hist,b_hist, 0, histImage.rows,NORM_MINMAX, -1,Mat());
    normalize(g_hist,g_hist, 0, histImage.rows,NORM_MINMAX, -1,Mat());
    normalize(r_hist,r_hist, 0, histImage.rows,NORM_MINMAX, -1,Mat());

    for (int i = 0; i < 255; ++i)
    {
        line(histImage,Point(bin_w * (i),hist_h), Point(bin_w * (i),hist_h-b_hist.at<float>(i)),Scalar(255,0,0));
        line(histImage,Point(bin_w * (i),hist_h), Point(bin_w * (i),hist_h-r_hist.at<float>(i)),Scalar(0,255,0));
        line(histImage,Point(bin_w * (i),hist_h), Point(bin_w * (i),hist_h-g_hist.at<float>(i)),Scalar(0,0,255));
    }

    imshow("Input Image",src);
    imshow("Color Histogram",histImage);
    waitKey();
    return 0;
}

int ex02_drawHist(int histogram[])
{
    int hist_w = 512;
    int hist_h = 400;
    int bin_w = cvRound((double)hist_w/256); //빈의 폭

    Mat histImage(hist_h,hist_w,CV_8UC3,Scalar(255,255,255));

    int max = histogram[0];
    for (int i = 1; i < 256; ++i)
    {
        if (max < histogram[i])
        {
            max = histogram[i];
        }
    }
    for (int i = 0; i < 255; ++i)
    {
        histogram[i] = floor(((double)histogram[i] / max) * histImage.rows);
    }

    for (int i = 0; i < 255; ++i)
    {
        line(histImage,Point(bin_w * (i),hist_h), Point(bin_w * (i),hist_h-histogram[i]),Scalar(0,0,255));
    }
    imshow("Histogram",histImage);
}

int ex02()
{
    Mat src = imread(imgFolderLink + "lenna.jpg",IMREAD_GRAYSCALE);
    imshow("Input Image",src);
    int histogram[256] = {0};

    for (int y = 0; y < src.rows; ++y)
    {
        for (int x = 0; x < src.cols; ++x)
        {
            histogram[(int)src.at<uchar>(y,x)]++;
        }
    }
    ex02_drawHist(histogram);
    waitKey(0);
    return 0;
}

int ex01()
{
    Mat src = imread(imgFolderLink + "lenna.jpg",IMREAD_GRAYSCALE);
    imshow("Input Image",src);

    int histogram[256] = {0};

    for (int y = 0; y < src.rows; ++y)
    {
        for (int x = 0; x < src.cols; ++x)
        {
            histogram[(int)src.at<uchar>(y,x)]++;
        }
    }

    for (int count : histogram)
    {
        cout << count << ",";
    }
    waitKey(0);

    return 0;
}