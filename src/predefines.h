#pragma once
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;
typedef unsigned int uint;
typedef unsigned short int usint;
typedef short int sint;
typedef struct {
	float h0;
	float h1;
} struct_h;

typedef struct {
	int x;
	int y;
}point;

#define BACT_NUM 20
#define NS 10
#define NC 10
#define NRE 4
//TODO: Verify Step Size
#define STEP_SIZE 1
//TODO: Define the value for DELL_T
#define DELL_T 1
int GLOBAL_MAX = -1;
// A point of GLOBAL_MAX intensity
point gp = {0};
typedef struct{
	point cpos, npos;
}bacteria;

bacteria bs[20];

//Calculated points of the bacteria.
point r[20];
// This variable acts as a key
int histkey[256];
// This variable acts a value in a pair
int histvalue[256] = {0};
// Global img variable
cv::Mat img;
//Intensity limit for the images
#define THRESHOLD_LIMIT 35
// The final thresholding limit.
float thresh;

#include <random>
// This function will return a random number between 0 and 255.
int find_random() {
	return rand() % 255;
}

// This function gets the intensity value present at point p.
int get_intensity(point p) {
	return (int)img.at<uchar>(p.y, p.x);
}

// This function will return range number between the min and max.
double find_random_range(int min, int max) {
	int randNum = rand()%(max-min + 1) + min;
	return (double)randNum;
}


// This function finds the point that has a global_max
void find_global_point() {
	int i, j;
	// Fixing a point that has a same value as the global max.
	for(i=gp.x; i< img.rows; i++) {
		for (j=gp.y; j<img.cols; j++) {
			int temp = img.at<uchar>(i,j);
			if (temp == GLOBAL_MAX) {
				gp.x = i;
				gp.y = j;
				cout << "GP.x: " << gp.y << "\tGP.y: " << gp.x << " => "
							<< (int) img.at<uchar>(gp.x, gp.y) << endl;
				return;
			}
		}
	}
}

// Callback for mouse events
void call_back_func(int event, int x, int y, int flags, void* userdata) {
	if ( event == EVENT_MOUSEMOVE ) {
		cout << "Mouse move [" << x << "][" << y << "]: " <<
				(int)img.at<uchar>(Point(x,y)) << endl;
	}
}

// This function will check for nan and if present replaces with 0
float check_nan(float value) {
	return isnan(value) ? 0 : value;
}

// This function will return the PSNR measure
double getPSNR(const Mat& I1, const Mat& I2)
{
    Mat s1;
    absdiff(I1, I2, s1);       // |I1 - I2|
    s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
    s1 = s1.mul(s1);           // |I1 - I2|^2
    Scalar s = sum(s1);         // sum elements per channel
    double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels
    if( sse <= 1e-10) // for small values return zero
        return 0;
    else
    {
        double  mse =sse /(double)(I1.channels() * I1.total());
        double psnr = 10.0*log10((255*255)/mse);
        return psnr;
    }
}
