#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Bestemmer kant thresholds. Low og high til Hysteresis edge tracking
int lowThreshold = 0;
int maxThreshold = 100;

// Kernel_size på Sobel operatoren. Den algoritme der finde gradienten for samtlige pixels.
int kernel_size = 3;

static void cannyThreshold(Mat &src, Mat &dst) {
	// Fjerner støj med GaussianBlur, da canny edge detection er overfølsom overfor støj. Der bruges en 5x5 kerne, og 
	// src overskrives, da vi ikke skal bruge det gamle billede. Kernel standard deviation i x-aksens retning på kernen
	// sættes til nul. På den måde udregner OpenCV selv standard deviation. GaussianBlur bruges, da det er standard for
	// preprocessering af canny edge detection.
	GaussianBlur(src, src, Size(5, 5), 0);

	// src overskrives igen, da det gamle billede ikke skal bruges. L2gradient er sat til "true", da funktionen i givet fald
	// bliver mere præcis med algoritment: L2 norm = sqr((dI/dx)^2+(dI/dy)^2)
	Canny(src, dst, lowThreshold, maxThreshold, kernel_size, true);
}


int main() {
	string path = "imgs/billede_noisefree.PNG";

	// Normalt ville man skulle konvertere billedet til grayscale, men vores billede er allerede i sort/hvid. dst er destinationsbilledet
	// til canny edge detect funktionen.
	Mat src = imread(path), dst;

	if (!src.data) {
		cerr << "No image data" << endl;
		}

	imshow("Original", src);
	cannyThreshold(src, dst);
	imshow("Canny Edge Detection", dst);
	waitKey(0);
	return 0;
}