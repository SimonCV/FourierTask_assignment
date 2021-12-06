#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


void main() {

	////////// Basic Functions //////////

	
	string path = "Resources/test.png";

	// Reads image from path. Mat is a matrix datatype
	Mat img = imread(path);		
	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

	// Converts to grayscale
	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	// Blurs the image. THe numbers controls the degree of blur. Higher value means more blur. Goes up to 9
	GaussianBlur(imgGray, imgBlur, Size(3,3), 3, 0);

	// Edge detection. lower value gives more edges.
	Canny(imgBlur, imgCanny, 25, 75);				

	// Creates a kernel for the dilation function. Bigger Size, means more dilation and vice versa. "You should only use odd numbers" - why?
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));	

	// Dilates the image. Makes the edges "fatter".
	dilate(imgCanny, imgDil, kernel);

	// Erode also uses an kernel to determine the degree of erossion. This case we use the same kernel as the dilate function
	erode(imgDil, imgErode, kernel);

	// Shows the image. First parameter gives the image a name, the second is the image itself
	imshow("Image", img);			
	imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dilation", imgDil);
	imshow("Image Erode", imgErode);

	// The image will close again instantly, if it aren't given a time stretch to be open in. waitKey(0), keeps it open untill we manually close it
	waitKey(0);					
	
}