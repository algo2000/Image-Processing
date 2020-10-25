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
int ex11();
int ex12();
int ex13();
int ex14();
int ex15();
int ex16();
int ex17();
int ex18();
int ex19();

string imgLink = "/Users/leo/Documents/학교 문서/영상처리/코드/code/ch04/Lenna.jpg";
string imgFolderLink = "/Users/leo/Documents/학교 문서/영상처리/코드/code/ch04/images/";

int main()
{
    ex16();
}

int ex16()
{
    Mat img1,mask;

    img1 = imread(imgFolderLink + "scene.jpg", IMREAD_COLOR);
    if (img1.empty())
    {
        cout << "영상1을 로드할 수 없습니다." <<endl;
        return -1;
    }
    mask = imread(imgFolderLink + "mask.png", IMREAD_COLOR);
    if (mask.empty())
    {
        cout << "영상2을 로드할 수 없습니다." <<endl;
        return -1;
    }

    Mat dst = img1.clone();
    imshow("img1", img1);
    imshow("mask", mask);

    bitwise_and(img1,mask,dst);
    imshow("dst",dst);
    waitKey(0);
    return 0;
}

int ex15()
{
    double alpha = 0.5;
    double beta;
    double input;

    Mat src1,src2,dst;

    cout << "알파 값을 입력하시오 [0.0 ~ 1.0] : ";
    cin >> input;

    src1 = imread(imgFolderLink + "test1.jpg");
    src2 = imread(imgFolderLink + "test2.jpg");

    if (src1.empty())
    {
        cout << "영상1을 로드할 수 없습니다." <<endl;
        return -1;
    }
    if (src2.empty())
    {
        cout << "영상2을 로드할 수 없습니다." <<endl;
        return -1;
    }

    beta = 1.0 - alpha;
    addWeighted(src1,alpha,src2,beta,0.0,dst);
    imshow("Original Image1",src1);
    imshow("Original Image2",src2);
    imshow("New Image",dst);
    waitKey(0);
    return 0;
}

int ex14()
{
    Mat src1 = imread(imgFolderLink + "test1.jpg");
    Mat src2 = imread(imgFolderLink + "test2.jpg");

    Mat dst;
    dst = src1 + src2;

    imshow("Oreignal Image1",src1);
    imshow("Oreignal Image2",src2);
    imshow("New Image",dst);
    waitKey(0);
    return 0;
}

int ex13()
{
    Mat src1,dst;
    double gamma = 0.5;

    src1 = imread(imgLink);
    if (src1.empty())
    {
        cout<<"영상을 읽을 수 없습니다." << endl;
        return -1;
    }

    Mat table(1,256,CV_8U);

    uchar *p = table.ptr();
    for (int i = 0; i < 256; ++i)
    {
        p[i] = saturate_cast<uchar>(pow(i/255.0,gamma)*255.0);
    }

    LUT(src1,table,dst);
    imshow("src1",src1);
    imshow("dst",dst);
    waitKey(0);
}

int ex12()
{
    Mat img1 = imread(imgLink,IMREAD_GRAYSCALE);
    imshow("Original Image",img1);

    Mat table(1,256,CV_8U);

    uchar *p = table.ptr();
    for (int i = 0; i < 256; ++i)
    {
        p[i] = 255-i;
    }

    Mat img2;
    LUT(img1,table,img2);

    imshow("New Image",img2);
    waitKey(0);

    return 0;
}

int ex11()
{
    Mat image = imread(imgLink,IMREAD_GRAYSCALE);
    Mat dst;
    int threshold_value = 127;

    threshold(image,dst,threshold_value,255,THRESH_BINARY);
    imshow("Original Image", image);
    imshow("New Image", dst);

    waitKey(0);
    return 0;
}

int ex10()
{
    Mat src = imread(imgLink,IMREAD_GRAYSCALE);
    imshow("Original Image",src);

    Mat dst;
    dst = 255 - src;
    imshow("Changed Image", dst);

    waitKey(0);
    return 0;
}

int ex09_contrastEnh(int input, int x1, int y1, int x2, int y2)
{
    double output;
    if (0 <= input && input <= x1)
    {
        output = y1/x1 * input;
    }
    else if (x1 < input && input <= x2)
    {
        output = ((y2-y1)/(x2-x1)) * (input-x1)+y1;
    }
    else if (x2 < input && input <= 255)
    {
        output=((255-y2)/(255-x2)) * (input - x2) + y2;
    }
    return (int) output;
}

int ex09()
{
    Mat image = imread(imgLink);
    Mat oimage = image.clone();
    int x1,y1,x2,y2;
    cout << "x1 값을 입력하시오 : ";
    cin >> x1;
    cout << "y1 값을 입력하시오 : ";
    cin >> y1;
    cout << "x2 값을 입력하시오 : ";
    cin >> x2;
    cout << "y2 값을 입력하시오 : ";
    cin >> y2;

    for (int r = 0; r < image.rows; ++r)
    {
        for (int c = 0; c < image.cols; ++c)
        {
            for (int ch = 0; ch < 3; ++ch)
            {
                int output = ex09_contrastEnh(image.at<Vec3b>(r,c)[ch],x1,y1,x2,y2);
                oimage.at<Vec3b>(r,c)[ch] = saturate_cast<uchar>(output);
            }
        }
    }

    imshow("Original Image",image);
    imshow("New Image",oimage);
    waitKey();
    return 0;
}

int ex08()
{
    double alpha = 1.0;
    int beta = 0;

    Mat image = imread(imgLink);
    Mat oimage;

    cout << "알파값을 입력하시오 : [1.0 ~ 3.0] : ";
    cin >> alpha;
    cout << "베타값을 입력하시오 : [0 ~ 100] : ";
    cin >> beta;

    oimage = image * alpha + beta;

    imshow("Original Image",image);
    imshow("New Image",oimage);

    waitKey();
    return 0;

}

int ex07()
{
    double alpha = 1.0;
    int beta = 0;
    Mat image = imread(imgLink);
    Mat oimage;

    cout << "알파값을 입력하시오 : [1.0 ~ 3.0] : ";
    cin >> alpha;
    cout << "베타값을 입력하시오 : [0 ~ 100] : ";
    cin >> beta;

    image.convertTo(oimage,-1,alpha,beta);

    imshow("Original Image",image);
    imshow("New Image",oimage);

    waitKey();
    return 0;

}

int ex06()
{
    double alpha = 1.0;
    int beta = 0;

    Mat image = imread(imgLink);
    Mat oimage = Mat::zeros(image.size(),image.type());
    cout << "알파값을 입력하시오 : [1.0 ~ 3.0] : ";
    cin >> alpha;
    cout << "베타값을 입력하시오 : [0 ~ 100] : ";
    cin >> beta;

    for (int y = 0; y < image.rows; ++y)
    {
        for (int x = 0; x < image.cols; ++x)
        {
            for (int c = 0; c < 3; ++c)
            {
                oimage.at<Vec3b>(y,x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y,x)[c])+beta);
            }
        }
    }

    imshow("Original Image",image);
    imshow("New Image",oimage);
    waitKey();
    return 0;
}

void brighten(Mat& img, int value)
{
    for (int r = 0; r < img.rows; ++r)
    {
        for (int c = 0; c < img.cols; ++c)
        {
            img.at<uchar>(r,c) = saturate_cast<uchar>(img.at<uchar>(r,c)+value);
        }
    }
}

int ex05()
{
    Mat img = imread(imgLink,IMREAD_GRAYSCALE);
    imshow("Original Image",img);

    brighten(img,30);
    imshow("New Image", img);
    waitKey(0);

    return 0;
}

int ex04()
{
    Mat img = imread(imgLink,IMREAD_GRAYSCALE);
    imshow("Origin Image",img);

    Mat oiMage;

    //대상 행렬, 음수면 출력 입력 같은 타입, 곱할 값, 더할 값
    img.convertTo(oiMage,-1,1,30);

    imshow("New Image",oiMage);
    waitKey(0);
    return 0;
}

int ex03()
{
    Mat img = imread("/Users/leo/Documents/학교 문서/영상처리/코드/code/ch04/Lenna.jpg",IMREAD_GRAYSCALE);
    imshow("Original Image", img);

    for (int r = 0; r < img.rows; ++r)
    {
        uchar *p = img.ptr<uchar>(r);
        for (int c = 0; c < img.cols; ++c)
        {
            p[c] = saturate_cast<uchar>(p[c]+30);
        }
    }
    imshow("New Image",img);
    waitKey(0);

    return 0;
}

int ex02()
{
    Mat img = imread("/Users/leo/Documents/학교 문서/영상처리/코드/code/ch04/Lenna.jpg",IMREAD_GRAYSCALE);
    imshow("Original Image",img);

    for(int r = 0; r<img.rows; r++)
    {
        for (int c = 0; c < img.cols; c++)
        {
            img.at<uchar>(r,c) = saturate_cast<uchar>(img.at<uchar>(r,c) + 30);
        }
    }

    imshow("New Image",img);
    waitKey(0);
    return 0;
}

int ex01()
{
    Mat img = imread("/Users/leo/Documents/학교 문서/영상처리/코드/code/ch04/Lenna.jpg",IMREAD_GRAYSCALE);
    imshow("Original Image",img);

    for(int r = 0; r<img.rows; r++)
    {
        for (int c = 0; c < img.cols; c++)
        {
            img.at<uchar>(r,c) = img.at<uchar>(r,c) + 30;
        }
    }

    imshow("New Image",img);
    waitKey(0);
    return 0;
}