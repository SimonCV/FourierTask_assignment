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

static void cannyThreshold(Mat &src, Mat &dst) {
    // Fjerner stoej med GaussianBlur, da canny edge detection er overfoelsom overfor stoej. Der bruges en 5x5 kerne, og
	// src overskrives, da vi ikke skal bruge det gamle billede. Kernel standard deviation i x-aksens retning p  kernen
    // saettes til nul. P  den m de udregner OpenCV selv standard deviation. GaussianBlur bruges, da det er standard for
	// preprocessering af canny edge detection.
	GaussianBlur(src, src, Size(5, 5), 0);

	// src overskrives igen, da det gamle billede ikke skal bruges. L2gradient er sat til "true", da funktionen i givet fald
    // bliver mere praecis med algoritment: L2 norm = sqr((dI/dx)^2+(dI/dy)^2)
	Canny(src, dst, lowThreshold, maxThreshold, kernel_size, true);
}

static void houghCircleTransform(Mat& src, Mat& dst) {
	// Initialize the accumulator to 0
	Mat accumulator = Mat::zeros(src.cols*2, src.rows*2, src.type());



	double r = 32;
	int b = 0;
	int a = 0;
	double pi = 3.14159265359;

	cout << "Accumulator size = " << accumulator.cols << ", " << accumulator.rows << endl;
	cout << "Image size       = " << src.cols << ", " << src.rows << endl;

	// Best candidate. (x,y) in image space to (a,b) in Hough space
	for (int x = 0; x < src.cols; x++) {
		cout << "x = " << x << endl;
		for (int y = 0; y < src.rows; y++) {
			cout << "y = " << y << endl;
			//cout << "src.at(" << y << ", " << x << ") = " << (int)(src.at<uchar>(y, x)) << endl;
			if (src.at<cv::Vec3b>(y, x)[0] > 0) {
				for (double theta = 0; theta < 360; theta++) {
					//cout << "Theta = " << theta << endl;
					b = src.cols + (int)(y - (r * sin(theta * pi / 180)));
					a = src.rows + (int)(x - (r * cos(theta * pi / 180)));
					
					cout << "accum at " << a << ", " << b << " = " << endl;
					//cout << accumulator.at<uchar>(a, b) << endl;
					accumulator.at<Vec3b>(a, b)[0] += 1;
					imshow("Accumulator", accumulator);
					waitKey(1);
				}
				
			}
		}
	}
	
	imshow("Accumulator", accumulator);
	waitKey(0);
	//	For each cell(x, y)
	//	For each theta t = 0 to 360  // the possible  theta 0 to 360
	//	b = y – r * sin(t * PI / 180);  //polar coordinate for center (convert to radians)
	//a = x – r * cos(t * PI / 180); //polar coordinate for center (convert to radians)
	//A[a, b, r] += 1; //voting
	//end
}


void dumTest(Mat& src)
{
	Mat accumulator = Mat::zeros(src.cols * 2, src.rows * 2 , src.type());

	for (int x = 0; x < src.cols; x++) {
		//cout << "x = " << x << endl;
		for (int y = 0; y < src.rows; y++) {
			//cout << "y = " << y << endl;
			accumulator.at<Vec3b>(x, y)[0] = 255;
		}
	}
	imshow("navn", accumulator);
	waitKey(0);
}

int main() {
    string path = "../openCVcourse/imgs/billede_noiseFree.png";

	// Normalt ville man skulle konvertere billedet til grayscale, men vores billede er allerede i sort/hvid. dst er destinationsbilledet
	// til canny edge detect funktionen.
	Mat src = imread(path), dst;

	if (!src.data) {
		cerr << "No image data" << endl;
    }

	// houghCircleTransform(src, dst);'
    imshow("Original", src);
	waitKey(0);
	//dumTest(src);
	cannyThreshold(src, dst);
	imshow("Canny Edge Detection", dst);
    waitKey(0);
	cout << "type = " << src.type() << endl;
	cout << "type = " << dst.type() << endl;
	houghCircleTransform(dst, dst);
	destroyAllWindows;
	return 0;
}
