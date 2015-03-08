#pragma once
#include "opencv2/core/mat.hpp"
#include <cmath>
using namespace cv;
using namespace std;

void remove_upper( const Mat& original, Mat& result) {
	uint i, j;
	uint width = original.cols;
	uint height = original.rows;
	original.copyTo(result);
	for ( i=0; i<height/2; i++) {
		for (j=0; j<width; j++) {
			result.at<Vec3b> (i, j) = Vec3b(0,0,0);
		}
	}
}
