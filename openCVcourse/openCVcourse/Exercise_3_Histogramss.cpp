#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class Histogram {
public:
	Mat calc_histogram(Mat src) {
		Mat hist;
		hist = Mat::zeros(256, 1, CV_32F);
		src.convertTo(src, CV_32F);
		double value = 0;
		for (int i = 0; i < src.rows; i++) {
			for (int j = 0; j < src.cols; j++) {
				value = src.at<float>(i, j);
				hist.at<float>(value) = hist.at<float>(value) + 1;
			}
		}
		return hist;
	}

	void plot_histogram(Mat histogram) {
		Mat histogram_image(400, 512, CV_8UC3, Scalar(0, 0, 0));
		Mat normalized_histogram;

		normalize(histogram, normalized_histogram, 0, 400, NORM_MINMAX, -1, Mat());

		// Multiplies by two to extend the range to 512
		for (int i = 0; i < 256; i++) {
			rectangle(histogram_image, Point(2 * i, histogram_image.rows - normalized_histogram.at<float>(i)),
				Point(2 * (i + 1), histogram_image.rows), Scalar(255, 0, 0));
		}

		namedWindow("Histogram", WINDOW_NORMAL);
		imshow("Histogram", histogram_image);
	}
};

int main() {
	string path = "imgs/legoHouse.jpg";

	Mat img = imread(path);
	if (!img.data) {
		cerr << "No image data" << endl;
	}

	imshow("Original", img);

	waitKey(0);

	return 0;
}