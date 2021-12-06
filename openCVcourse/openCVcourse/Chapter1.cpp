#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


void main() {

	////////// Images //////////

	//
	//string path = "Resources/test.png";
	//Mat img = imread(path);		// Reads image from path. Mat is a matrix datatype
	//imshow("Image", img);			// Shows the image. First parameter gives the image a name, the second is the image itself
	//waitKey(0);					// The image will close again instantly, if it aren't given a time stretch to be open in. waitKey(0), keeps it open untill we manually close it
	//





	////////// Videos //////////

	//
	//string path = "Resources/test_video.mp4";
	//VideoCapture cap(path);
	//Mat img;

	//while (true) {
	//
	//	cap.read(img);

	//	imshow("Image", img);
	//	waitKey(20);				// Video is a series of images, therefore we don't want it to wait forever between images
	//}
	//





	////////// Webcam //////////

	
	VideoCapture cap(0);			// Instead of a string, we use a camera ID. If we only have one camera connected, the ID is 0
	Mat img;

	while (true) {

		cap.read(img);

		imshow("Image", img);
		waitKey(1);
	}

	
	}