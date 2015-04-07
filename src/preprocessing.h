#pragma once
#include "opencv2/core/mat.hpp"
#include <cmath>
using namespace cv;
using namespace std;

void remove_upper( const Mat& original, Mat& result) {
	uint i, j;
	original.copyTo(result);
	for (i=0; i<original.rows/2; i++) {
		for (j=0; j<original.cols; j++) {
			result.at<Vec3b> (i, j) = Vec3b(0,0,0);
		}
	}
}
