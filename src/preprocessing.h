#pragma once
#include "opencv2/core/mat.hpp"
#include <cmath>
using namespace cv;
using namespace std;

void clean_image( const Mat& original, Mat& result) {
	uint i, j;
	original.copyTo(result);
	for (i=0; i<original.rows/2; i++) {
		for (j=0; j<original.cols; j++) {
			result.at<uchar>(i, j) = 0;
		}
	}
	for (i=(original.rows-original.rows/4); i<original.rows; i++) {
		for (j=0; j<original.cols; j++) {
			result.at<uchar> (i, j) = 0;
		}
	}
	for (i=original.rows/2; i<(original.rows-original.rows/4); i++) {
		for (j=0; j<(original.cols/2 - 50); j++) {
			result.at<uchar> (i, j) = 0;
		}
	}
	for (i=original.rows/2; i<(original.rows-original.rows/4); i++) {
		for (j=(original.cols/2 + 50); j<original.cols; j++) {
			result.at<uchar> (i, j) = 0;
		}
	}
}
