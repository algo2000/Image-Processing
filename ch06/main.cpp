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
    ex09();
}

int stretch(int x, int r1, int s1, int r2, int s2)
{
    float result;
    if (0 <= x && x <= r1)
    {
        result = s1 / r1 * x;
    }
    else if (r1 < x && x <= r2)
    {
        result = ((s2 - s1) / (r2 - r1)) * (x - r1) + s1;
    }
    else if (r2 < x && x <= 255)
    {
        result = ((255 - s2) / (255 - r2)) * (x - r2) + s2;
    }
    return (int)result;
}
int ex09()
{
    int r1, s1, r2, s2;
    cout << "r1를 입력하시오: " ;
    cin >> r1;
    cout << "r2를 입력하시오: ";
    cin >> r2;
    cout << "s1를 입력하시오: " ;
    cin >> s1;
    cout << "s2를 입력하시오: " ;
    cin >> s2;

    Mat image = imread(imgFolderLink + "card.jpg",IMREAD_GRAYSCALE);
    Mat image2 = image.clone();

    for (int y = 0; y < image.rows; ++y)
    {
        for (int x = 0; x < image.cols; ++x)
        {
            int output = stretch(image.at<uchar>(y,x),r1,s1,r2,s2);
            image2.at<uchar>(y,x) = saturate_cast<uchar>(output);
        }
    }
    imshow("1",image);
    imshow("2",image2);
    waitKey(0);
    return 0;
}

void drawHist(int histogram[])
{
    int hist_w = 512; // 히스토그램 영상의 폭
    int hist_h=400; //히스토그램영상의높이
    int bin_w = cvRound((double) hist_w / 256); // 빈의 폭
    // 히스토그램이 그려지는 영상(컬러로 정의)
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    // 히스토그램에서 최대값을 찾는다.
    int max = histogram[0];
    for (int i = 1; i < 256; i++)
    {
        if (max < histogram[i])
        {
            max = histogram[i];
        }
    }
    for (int i = 0; i < 255; i++)
    {
        histogram[i] = floor(((double)histogram[i] / max)*histImage.rows);
    }
    for (int i = 0; i < 255; i++)
    {
        line(histImage, Point(bin_w*(i), hist_h), Point(bin_w*(i), hist_h - histogram[i]), Scalar(0, 0, 255));
    }
    imshow("Histogram", histImage);
}

int ex08()
{
    Mat image = imread(imgFolderLink + "card.jpg",IMREAD_GRAYSCALE);
    int histogram[256] = {0};
    for (int y = 0; y < image.rows; ++y)
    {
        for (int x = 0; x < image.cols; ++x)
        {
            histogram[(int)image.at<uchar>(y,x)]++;
        }
    }
    drawHist(histogram);
    waitKey(0);
    return 0;
}

int ex07()
{
    Mat image = imread(imgFolderLink + "lenna.jpg",1);
    imshow("원본이미지",image);
    waitKey(0);

    GaussianBlur(image, image, Size(3, 3), 0, 0, BORDER_DEFAULT);
    imshow("가우시안블러 적용시",image);
    waitKey(0);

    Sobel(image, image,CV_8U,2,0,1,1,0,BORDER_DEFAULT);
    imshow("원본이미지 sobel operation", image);
    waitKey(0);
}

int ex06()
{
    Mat src;
    Mat grad;
    int scale = 1;
    int delta = 0;
    src = imread(imgFolderLink + "lenna.jpg", IMREAD_GRAYSCALE);
    if (src.empty())
    {
        return -1;
    }

    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    Sobel(src,grad_x,CV_16S,1,0,3,scale,delta,BORDER_DEFAULT);
    Sobel(src,grad_y,CV_16S,1,0,3,scale,delta,BORDER_DEFAULT);

    convertScaleAbs(grad_x,abs_grad_x);
    convertScaleAbs(grad_y,abs_grad_y);

    addWeighted(abs_grad_x,0.5,abs_grad_y,0.5,0,grad);

    imshow("Image",src);
    imshow("Sobel",grad);

    waitKey(0);
    return 0;
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