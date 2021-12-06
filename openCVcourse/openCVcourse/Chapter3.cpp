#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


void main() {

	////////// Resize and Crop //////////


	string path = "Resources/test.png";

	// Reads image from path. Mat is a matrix datatype
	Mat img = imread(path);
	Mat imgResize, imgCrop;

	// Viser hvor stort billedet er
	// cout << img.size() << endl;

	// Kopierer billedet over i et nyt billede med en ny størrelse. Kan skrive koordinater in i parameterlisten 
	// på Size() hvis man vil have billedet i et bestemt størrelse. Ellers kan man blot skrive procenter 
	// som billedet skal justeres i højden og bredden
	resize(img, imgResize, Size(), 0.5, 0.5);		

	// Creates a rectancle to crop from. Parameters are x koord, y koord, withe, height.
	Rect roi(200, 100, 300, 300);
	imgCrop = img(roi);

	// Shows the image. First parameter gives the image a name, the second is the image itself
	imshow("Image", img);
	imshow("Image Resized", imgResize);
	imshow("Image Cropped", imgCrop);

	// The image will close again instantly, if it aren't given a time stretch to be open in. waitKey(0), keeps it open untill we manually close it
	waitKey(0);

}