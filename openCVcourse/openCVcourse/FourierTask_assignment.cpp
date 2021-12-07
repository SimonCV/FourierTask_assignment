#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
// #include <math.h>

using namespace cv;
using namespace std;

// Bestemmer kant thresholds. Low og high til Hysteresis edge tracking
int lowThreshold = 0;
int maxThreshold = 100;

// Kernel_size p  Sobel operatoren. Den algoritme der finde gradienten for samtlige pixels.
int kernel_size = 3;

string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

void cannyThreshold(Mat &src, Mat &dst) {
    // Fjerner stoej med GaussianBlur, da canny edge detection er overfoelsom overfor stoej. Der bruges en 5x5 kerne, og
    // src overskrives, da vi ikke skal bruge det gamle billede. Kernel standard deviation i x-aksens retning paa kernen
    // saettes til nul. Paa den maade udregner OpenCV selv standard deviation. GaussianBlur bruges, da det er standard for
	// preprocessering af canny edge detection.
    GaussianBlur(src, src, Size(5, 5), 0);

	// src overskrives igen, da det gamle billede ikke skal bruges. L2gradient er sat til "true", da funktionen i givet fald
    // bliver mere praecis med algoritment: L2 norm = sqr((dI/dx)^2+(dI/dy)^2)
    Canny(src, dst, lowThreshold, maxThreshold, kernel_size, true);
}

void houghCircleTransform(Mat &canny) {
    // Initialize the accumulator to 0
    Mat temp(480, 640, CV_8UC1);
    Mat acc = Mat::zeros(Size(canny.cols, canny.rows), CV_8UC1);

    double r = 32;
    int b = 0;
    int a = 0;

    cout << "Acc type    : " << type2str(acc.type()) << endl;

    cout << "Image size = " << canny.rows << ", " << canny.cols << endl;
    cout << "Acc   size = " << acc.rows << ", " << acc.cols << endl;

    // Best candidate. (x,y) in image space to (a,b) in Hough space
    for (int x = 0; x < canny.rows; x++) {
        for (int y = 0; y < canny.cols; y++) {
            //cout << "canny.at(" << y << ", " << x << ") = " << (int)(canny.at<uchar>(y, x)) << endl;
            if (canny.at<uchar>(x, y) > 0) {
                for (double theta = 0; theta < 360; theta++) {
                    b = y - r * sin(theta * M_PI / 180);
                    a = x - r * cos(theta * M_PI / 180);
                    //cout << "Accum (a, b)(" << a << ", " << b << ") at (x, y, theta)(" << x << ", " << y << ", " << theta << ") = ";
                    //if (a < x && b < y) {
                        acc.at<uchar>(a, b) += 1;
                    //}
                    //cout << acc.at<uchar>(a, b) << endl;
                }
            }
        }
    }
    imshow("Acc", acc);
    waitKey(0);
}

int main() {
    string path = "../openCVcourse/imgs/billede_noiseFree.png";

    // Normalt ville man skulle konvertere billedet til grayscale, men vores billede er allerede i sort/hvid. dst er destinationsbilledet
    // til canny edge detect funktionen.
    Mat src = imread(path), dst;
    Mat hough = Mat::zeros(src.cols, src.rows, CV_8UC1);

    cout << "Source type : " << type2str(src.type()) << endl;
    cout << "Canny type  : " << type2str(dst.type()) << endl;
    cout << "Hough type  : " << type2str(hough.type()) << endl;

    if (!src.data) {
        cerr << "No image data" << endl;
    }

    imshow("Original", src);
    cannyThreshold(src, dst);
    src.release();
    imshow("Canny Edge Detection", dst);
    waitKey(0);
    destroyAllWindows();
    cout << "test1" << endl;
    houghCircleTransform(dst);
    cout << "test2"  << endl;
    return 0;
}
