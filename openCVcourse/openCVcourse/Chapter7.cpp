#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// imgDil is the image we want to find the contours on and img is the image we want to write on. Shapedetection.
void getContours(Mat imgDil, Mat img){

	vector<vector<Point>> contours;
	// Vector of 4 int variables
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// -1 for all contours, Scalar values are purple, 2 in thickness
	// drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		cout << "The area of contour " << i << " is: " << area << endl;

		vector<vector<Point>> conPoly(contours.size());
		vector<Rect> boundRect(contours.size());
		string objectType;

		// Checks every contour and only find the ones that is above area 1000. A way of filering noise
		if (area > 1000) {
			// Calculates a contour perimeter or curve length. Either computes a curve length or a closed contour perimeter. This is closed
			float peri = arcLength(contours[i], true);
			// Approximates the shape based of the number of corners. conPoly is the vector output. true = closed. Makes a number of
			// points in the shape. drawContours draws between those points. Circles will get kinda jagged
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			// Print out to see how many corners it found in each shape, to see what is equal to fx a circle or a square
			cout << "The number of corners for contour " << i << " is: " << conPoly[i].size() << endl;
			// Computes the maximum rectangle area of the shape
			boundRect[i] = boundingRect(conPoly[i]);


			int objCor = (int)conPoly[i].size();

			if (objCor == 3) {objectType = "Tri";}
			if (objCor == 4) { 
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				cout << "The aspect ratio for square/rectangle is: " << aspRatio << endl;
				if (aspRatio > 0.95 && aspRatio < 1.05) {
					objectType = "Square";
				}
				else { objectType = "Rect"; }
			}
			if (objCor > 4) { objectType = "Circle"; }

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);

			// boundRect[i].tl() calls the top left of the rectangle. boundRect[i].br() calls the bottom right.
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

			putText(img, objectType, { boundRect[i].x, boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);
		}
	}
}

void main() {

	////////// Images //////////
	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

	string path = "Resources/shapes.png";
	Mat img = imread(path);	

	// Prepocessing of image
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);

	getContours(imgDil, img);

	imshow("Image", img);		
	//imshow("Image Gray", imgGray);
	//imshow("Image Blur", imgBlur);
	//imshow("Image Canny", imgCanny);
	//imshow("Image Dil", imgDil);
	waitKey(0);					
}