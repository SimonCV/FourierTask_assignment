#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

float width = 250, height = 350;
Mat matrix, imgWarp;

void main() {

	////////// Warp Images //////////

	
	string path = "Resources/cards.jpg";
	Mat img = imread(path);	

	// Coordinates of cards found through paint. Point2f is a floating Point. Called src, with 4 points in it
	// The points on the card are from left to right: topleft, topright, bottomleft, bottomright
	Point2f src[4] = { {737, 378}, {1029, 432}, {642, 713}, {975,785} };

	// Destination Point, that'll be a rectanglular image. Needs to be floating points. Therefore "f"
	Point2f dest[4] = { {0.0f, 0.0f}, {width, 0.0f}, {0.0f, height}, {width,height} };

	matrix = getPerspectiveTransform(src, dest);
	warpPerspective(img, imgWarp, matrix, Point(width, height));

	// Makes circles around the picture points. A nice way to see if we select the right points in the warp.
	// We do this after the warp, else the circles will appear in the warped image
	for (int i{ 0 }; i < 4; i++) {
		circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
	}

	imshow("Image", img);
	imshow("Image Warp", imgWarp);
	waitKey(0);					



}