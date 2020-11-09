#include "main.h"
/*
���룺https://blog.csdn.net/keith_bb/article/details/53389819
*/
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int opencvdft()
{
    Mat I = imread("C:\\Users\\29263\\Downloads\\image.jpeg", IMREAD_GRAYSCALE);       //����ͼ��Ҷ�ͼ

    //�ж�ͼ���Ƿ���سɹ�
    if (I.empty())
    {
        cout << "ͼ�����ʧ��!" << endl;
        return -1;
    }
    else
        cout << "ͼ����سɹ�!" << endl << endl;

    Mat padded;                 //��0�������ͼ�����
    /*I.resize(Size(I.cols * 0.5, I.rows * 0.5));*/
    resize(I, I, Size((int)(I.cols*0.5),(int)(I.rows*0.5)));
    int m = getOptimalDFTSize(I.rows);
    int n = getOptimalDFTSize(I.cols);
    

    //�������ͼ��I���������Ϊpadded���Ϸ����󷽲�����䴦��
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(),CV_32F) };
    Mat complexI;
    merge(planes, 2, complexI);     //��planes�ںϺϲ���һ����ͨ������complexI

    dft(complexI, complexI);        //���и���Ҷ�任

    //�����ֵ��ת���������߶�(logarithmic scale)
    //=> log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI, planes);        //planes[0] = Re(DFT(I),planes[1] = Im(DFT(I))
                                    //��planes[0]Ϊʵ��,planes[1]Ϊ�鲿
    magnitude(planes[0], planes[1], planes[0]);     //planes[0] = magnitude
    Mat magI = planes[0];

    magI += Scalar::all(1);
    log(magI, magI);                //ת���������߶�(logarithmic scale)

    //����������л��У����Ƶ�׽��вü�
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    //�������и���Ҷͼ���е����ޣ�ʹ��ԭ��λ��ͼ������
    int cx = magI.cols / 2;
    int cy = magI.rows / 2;

    Mat q0(magI, Rect(0, 0, cx, cy));       //���Ͻ�ͼ�񻮶�ROI����
    Mat q1(magI, Rect(cx, 0, cx, cy));      //���Ͻ�ͼ��
    Mat q2(magI, Rect(0, cy, cx, cy));      //���½�ͼ��
    Mat q3(magI, Rect(cx, cy, cx, cy));     //���½�ͼ��

    //�任���ϽǺ����½�����
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    //�任���ϽǺ����½�����
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    //��һ��������0-1֮��ĸ�����������任Ϊ���ӵ�ͼ���ʽ
    normalize(magI, magI, 0, 1, NORM_MINMAX);

    imshow("����ͼ��", I);
    imshow("Ƶ��ͼ", magI);
    waitKey(0);


    return 0;
}

/////opencv�ٷ�Դ��

#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include <stdio.h>

using namespace cv;
using namespace std;

static void help(const char** argv)
{
    printf("\nThis program demonstrated the use of the discrete Fourier transform (dft)\n"
        "The dft of an image is taken and it's power spectrum is displayed.\n"
        "Usage:\n %s [image_name -- default lena.jpg]\n", argv[0]);
}

const char* keys =
{
    "{help h||}{@image|lena.jpg|input image file}"
};

int opencvSapmleOfdft(int argc, const char** argv)
{
    help(argv);
    CommandLineParser parser(argc, argv, keys);
    if (parser.has("help"))
    {
        help(argv);
        return 0;
    }
    string filename = parser.get<string>(0);
    //Mat img = imread(samples::findFile(filename), IMREAD_GRAYSCALE);
    Mat img = imread("C:\\Users\\29263\\Downloads\\image.jpeg", IMREAD_GRAYSCALE);
    resize(img, img, Size((int)(img.cols * 0.5), (int)(img.rows * 0.47)));
    if (img.empty())
    {
        help(argv);
        printf("Cannot read image file: %s\n", filename.c_str());
        return -1;
    }
    int M = getOptimalDFTSize(img.rows);
    int N = getOptimalDFTSize(img.cols);
    cout << "M = " << M << " N = " << N << endl;
    cout << "img.rows = " << img.rows << " img.cols = " << img.cols << endl;
    Mat padded;
    copyMakeBorder(img, padded, 0, M - img.rows, 0, N - img.cols, BORDER_CONSTANT, Scalar::all(0));
    imshow("img", img);
    namedWindow("padded", WINDOW_NORMAL);
    resizeWindow("padded", N, M);
    imshow("padded", padded);
    cout << "padded.rows = " << padded.rows << " padded.cols = " << padded.cols << endl;


    Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
    Mat complexImg;
    merge(planes, 2, complexImg);

    dft(complexImg, complexImg);

    // compute log(1 + sqrt(Re(DFT(img))**2 + Im(DFT(img))**2))
    split(complexImg, planes);
    magnitude(planes[0], planes[1], planes[0]);
    Mat mag = planes[0];
    mag += Scalar::all(1);
    log(mag, mag);

    // crop the spectrum, if it has an odd number of rows or columns
    mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));

    int cx = mag.cols / 2;
    int cy = mag.rows / 2;

    // rearrange the quadrants of Fourier image
    // so that the origin is at the image center
    Mat tmp;
    Mat q0(mag, Rect(0, 0, cx, cy));
    Mat q1(mag, Rect(cx, 0, cx, cy));
    Mat q2(mag, Rect(0, cy, cx, cy));
    Mat q3(mag, Rect(cx, cy, cx, cy));

    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(mag, mag, 0, 1, NORM_MINMAX);

    imshow("spectrum magnitude", mag);
    waitKey();
    return 0;
}

/////opencv�ٷ�Դ��
