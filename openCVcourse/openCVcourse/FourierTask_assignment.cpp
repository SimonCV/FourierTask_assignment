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

void cannyThreshold(Mat &src, Mat &dst) {
    // Fjerner stoej med GaussianBlur, da canny edge detection er overfoelsom overfor stoej. Der bruges en 5x5 kerne, og
	// src overskrives, da vi ikke skal bruge det gamle billede. Kernel standard deviation i x-aksens retning p  kernen
    // saettes til nul. P  den m de udregner OpenCV selv standard deviation. GaussianBlur bruges, da det er standard for
	// preprocessering af canny edge detection.
    GaussianBlur(src, src, Size(5, 5), 0);

	// src overskrives igen, da det gamle billede ikke skal bruges. L2gradient er sat til "true", da funktionen i givet fald
    // bliver mere praecis med algoritment: L2 norm = sqr((dI/dx)^2+(dI/dy)^2)
    Canny(src, dst, lowThreshold, maxThreshold, kernel_size, true);
}

Mat houghCircleTransform(Mat &src) {
	// Initialize the accumulator to 0
    Mat accumulator = Mat::zeros(src.rows, src.cols, CV_8UC1);
    Mat acc(accumulator.rows, accumulator.cols, accumulator.type());

	double r = 32;
    double b = 0;
    double a = 0;

    cout << "Accumulator size = " << accumulator.rows << ", " << accumulator.cols << endl;
    cout << "Image size       = " << src.rows << ", " << src.cols << endl;

	// Best candidate. (x,y) in image space to (a,b) in Hough space
    for (int x = 0; x < src.rows; x++) {
        for (int y = 0; y < src.cols; y++) {
			//cout << "src.at(" << y << ", " << x << ") = " << (int)(src.at<uchar>(y, x)) << endl;
            if (src.at<uchar>(x, y) > 0) {
				for (double theta = 0; theta < 360; theta++) {
                    b = y - r * sin(theta * M_PI / 180);
                    a = x - r * cos(theta * M_PI / 180);
                    //cout << "Accum (a, b)(" << a << ", " << b << ") at (x, y, theta)(" << x << ", " << y << ", " << theta << ") = ";
                    accumulator.at<uchar>(a, b) += 1;
                    //cout << (int)accumulator.at<uchar>(a, b) << endl;
                }
			}
		}
    }
    return accumulator;
}

int main() {
    string path = "../openCVcourse/imgs/billede_noiseFree.png";

	// Normalt ville man skulle konvertere billedet til grayscale, men vores billede er allerede i sort/hvid. dst er destinationsbilledet
	// til canny edge detect funktionen.
    Mat src = imread(path), dst;
    Mat hough = Mat::zeros(src.rows, src.cols, CV_8UC1);

	if (!src.data) {
		cerr << "No image data" << endl;
    }

    imshow("Original", src);
    cannyThreshold(src, dst);
    imshow("Canny Edge Detection", dst);
    waitKey(0);
    destroyAllWindows();
    //cout << "src type = " << src.type() << endl;
    //cout << "dst type = " << dst.type() << endl;
    cout << "test1" << endl;
    houghCircleTransform(dst).copyTo(hough);
    cout << "test2"  << endl;
    //cout << "hough size out: " << hough.size << endl;
    //imshow("Hough Circle Transform", hough);
    //waitKey(0);
    //destroyAllWindows();
    return 0;
}
