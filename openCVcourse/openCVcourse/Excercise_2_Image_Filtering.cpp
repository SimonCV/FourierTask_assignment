#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

////////////////// Image Filtering //////////////////

void padImage(cv::Mat input, cv::Mat& output, int k) {
	// Laver en matrix fyldt med nuller
	output = cv::Mat::zeros(input.rows + 2 * k, input.cols + 2 * k, input.type());

	// Kopierer input billedet over i output billedet, der bliver et rektangel med k dimensioner større end 
	// input cols og rows.
	input.copyTo(output(cv::Rect(k, k, input.cols, input.rows)));
}

void main() {
	
	////////////////// Linear Filtering with padding //////////////////

	string path = "imgs/test_gaussian.png";

	// Defination af variabler
	Mat img = imread(path);		
	Mat padding, dest;
	Mat kernel;
	Point anchor;
	double delta{};
	int ddepth{}, kernel_size{};
	const char* window_name = "filter2D Demo";

	if (!img.data) {
		cerr << "No image data" << endl;
	}

	// Initialize arguments for the filter

	// The position of the anchor relative to its kernel. The location Point(-1, -1) indicates the center by default.
	anchor = Point(-1, -1);

	// A value to be added to each pixel during the correlation. By default it is 0
	delta = 0;

	// The depth of the destination image.  A negative value (such as −1) indicates that the depth is the same as the source.
	ddepth = -1;

	// Loop - Will filter the image with different kernel size each 0.5 seconds'
	int ind{};

	// Evig for loop
	for (;;) {
		// Update kernel size for a normalized box filter 
		kernel_size = 3 + 2 * (ind % 5);
		kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size * kernel_size);

		// Apply padding (blot en sort kant omkring billedet)
		padImage(img, padding, 10);

		// Apply filter
		filter2D(padding, dest, ddepth, kernel, anchor, delta, BORDER_DEFAULT);

		imshow("Filtered image", dest);

		char c = (char)waitKey(500);
		// Press 'ESC' to exit program. 27 = nummer for ESC - key. waitKey fungere som at den venter x antal sekunder
		// hvor man som user har mulighed for at komme med input før den fortsætter. Der er derved implementeret en 
		// form for cin.
		if (c == 27)
		{
			break;
		}

		ind++;
	}
	



	//////////////// Median Filtering //////////////////

	// Create 2 empty windows
	//namedWindow("Original image", WINDOW_AUTOSIZE);
	//namedWindow("Smoothed image", WINDOW_AUTOSIZE); 

	//string path = "imgs/test_saltpepper.png";

	//Mat img = imread(path);		
	//Mat dest;
	//int kernel_Size = 5;

	//// Smooth the image using Median kernel in "img" and save it to "dest"
	//medianBlur(img, dest, kernel_Size);

	//imshow("Original image", img);
	//imshow("Smoothed image", dest);

	//waitKey(0);
}