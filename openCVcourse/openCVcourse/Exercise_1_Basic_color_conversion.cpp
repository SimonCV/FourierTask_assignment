#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void rotateMatrix(Mat image) {

};

void main() {
	////////////////// Transposing //////////////////

	//string path = "imgs/legoHouse.jpg";

	//Mat img = imread(path);		
	//if (!img.data) {
	//	cerr << "No image data" << endl;
	//}
	//
	//namedWindow("Display image", WINDOW_AUTOSIZE);	// Gør automatisk vinduet til billedestørrelse

	//Mat transpose(img.cols, img.rows, img.type());		// Laver en matrise ud af billedet i 8bit

	//for (int i{0}; i < img.rows; ++i) {
	//	for (int j{ 0 }; j < img.cols; ++j) {
	//		transpose.at<Vec3b>(j, img.rows-1-i) = img.at<Vec3b>(i, j);
	//	}
	//}

	//imshow("Original", img);
	//imshow("Transposed", transpose);

	//waitKey(0);


	////////////////// Isolating a color //////////////////

	string path = "imgs/BabyFood-Sample2.jpg";

	Mat img = imread(path);
	if (!img.data) {
		cerr << "No image data" << endl;
	}

	namedWindow("Display image", WINDOW_AUTOSIZE);	// Gør automatisk vinduet til billedestørrelse

	Mat imgHLS;

	// Ændre til HLS
	cvtColor(img, imgHLS, COLOR_BGR2HLS);			

	// Laver et sort billede af samme størrelse
	Mat spoonsHLS = Mat::zeros(imgHLS.rows, imgHLS.cols, imgHLS.type());	

	// Tjekker om hver pixel ligger over 150 i Hue, under 150 i luminance og over 150 i saturation
	for (int i{ 0 }; i < imgHLS.rows; ++i) {
		for (int j{ 0 }; j < imgHLS.cols; ++j) {
			if (imgHLS.at<Vec3b>(i, j)[0] > 150 && imgHLS.at<Vec3b>(i, j)[1] < 150 && imgHLS.at<Vec3b>(i, j)[2] > 150)
				spoonsHLS.at<Vec3b>(i, j) = imgHLS.at<Vec3b>(i, j);
		}
	}

	Mat spoonRGB;

	cvtColor(spoonsHLS, spoonRGB, COLOR_HLS2BGR);

	namedWindow("Display spoons");

	imshow("Spoons", spoonRGB);
	imshow("Original", img);
	imshow("HLS", imgHLS);

	waitKey(0);
}