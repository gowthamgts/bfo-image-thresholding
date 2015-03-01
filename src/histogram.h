#pragma once
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;

namespace histogram {
	void calc_hist(const Mat& src) {
		Mat dst;
		if( !src.data ) {
			return;
		}
		vector<Mat> bgr_planes;
		split( src, bgr_planes );

		// Establish the number of bins
		int histSize = 256;

		// Set the ranges ( for B,G,R) )
		float range[] = { 0, 256 } ;
		const float* histRange = { range };
		bool uniform = true; bool accumulate = false;

		Mat b_hist, g_hist, r_hist;
		/// Compute the histograms:
		calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
		calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
		calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

		/// Display
		namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
//		imshow("calcHist Demo", histImage );
		waitKey(0);
	}
}