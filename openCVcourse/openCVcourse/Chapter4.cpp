#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


void main() {

	////////// Blank Image //////////


	// Creates a blank image with 8 bit and 3 color channels. Scalar gives the image color in the order BGR.
	// 255 on all parameters = white. 0 on all parameters = black.
	Mat img(512, 512, CV_8UC3, Scalar(255,255,255));

	// Defines a circle. Point determines the center point coordinate. Next parameter the size (radius). Scalar = color.
	// Next parameter determines the thickness. Give it a value for thickness, and FILLED to fill it up
	circle(img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED);

	// If we use Point to define a rectangle, the first will define the top left cornor, and the second the top right cornor
	// Draws a rectangle in the circle. Thickness can be a number or FILLED.
	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);

	// Draws a line 10 pixels under the rectangle
	line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);

	// Writes text to the image. Point determins the starting point. After FONT, is scale. After Scalar is thickness.
	putText(img, "Simon's Workshop", Point(140, 262), FONT_ITALIC, 0.80, Scalar(0, 69, 255), 2);

	imshow("Image", img);
	waitKey(0);

}