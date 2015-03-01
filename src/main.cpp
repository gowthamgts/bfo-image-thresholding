//============================================================================
// Name        : main.cpp
// Author      : Gowtham Gopalakrishnan
// Version     :
// Copyright   : There is none. You're free to use.
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <string>

#include "opencv2/highgui/highgui.hpp"
#include "colorconversion.h"
#include "predefines.h"
#include "kapur.h"
#include "histogram.h"

using namespace std;
using namespace cv;
using namespace colorconversion;

// Some method declarations
void remove_upper( const Mat& original, Mat& result);
void calc_kapur( const Mat& original, Mat& result);
struct_h calc_kapur_struct(const Mat& original);

int main()
{
	Mat img, ihls_img, cropped, output;
	string ipath = "/home/electron/Pictures/ImageOutput";
	string suff = "-11.jpg";
	float result[50][2];
	int i;
	struct_h temp;
	for (i=0; i<50; i++) {
		img = imread(ipath + to_string(i+1) + suff);
		CV_Assert(img.channels() == 3);
		if (img.empty()) {
			cout << "Image is empty. Specify correct path" << endl;
			return -1;
		}
		temp = kapur::calc_kapur_struct(img);
		result[i][0] = temp.h0;
		result[i][1] = temp.h1;
		cout << "result[" << (i+1) << "]: " << result[i][0] << "\t" << result[i][1] << endl;	
	}
    /*img = imread("C:\\Users\\Len\\Downloads\\Image Database\\Images\\1-11.jpg");
    
	// Check that the image read is a 3 channels image and not empty
    CV_Assert(img.channels() == 3);
	if (img.empty()) {
		cout << "Image is empty. Specify correct path" << endl;
		return -1;
	}
	
	// Removing upper half
	convert_rgb_to_ihls(img, ihls_img);
	
	remove_upper(ihls_img, cropped);
	
	// Show preview
    namedWindow("Lip Segmentation", CV_WINDOW_AUTOSIZE);
	imshow("Lip Segmentation", cropped);

	//histogram::calc_hist(cropped);

	// Pass ihls image to kapur's method
	float kap_thresholding = kapur::calc(cropped, ihls_img.rows, ihls_img.cols);
	threshold(cropped, output, kap_thresholding, 255, 0);
	namedWindow("Thresholding [Type 0]", CV_WINDOW_AUTOSIZE);
	imshow("Thresholding [Type 0]", output);
	threshold(cropped, output, kap_thresholding, 255, 1);l
	namedWindow("Thresholding [Type 1]", CV_WINDOW_AUTOSIZE);
	imshow("Thresholding [Type 1]", output);
    waitKey(0); */
    return 0;
}

void remove_upper( const Mat& original, Mat& result) {
	uint i, j;
	uint width = original.cols;
	uint height = original.rows;
	original.copyTo(result);
	//std::cout << "Width: " << width << endl << "Height: " << height;
	for ( i=0; i<height/2; i++) {
		for (j=0; j<width; j++) {
			result.at<Vec3b> (i, j) = Vec3b(0,0,0);
		}
	}
}
