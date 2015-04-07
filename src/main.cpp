//============================================================================
// Name        : main.cpp
// Author      : Gowtham Gopalakrishnan
// Copyright   : There is none. You're free to use.
// Description : Hello World in C++, Ansi-style
//============================================================================

//contains all the predefined consts and opencv headers.
#include "predefines.h"
#include <string>
//preprocessing stuff contains remove_upper and a GLOBAL_MAX
#include "preprocessing.h"
#include "bact.h"
#include <ctime>
#include <iomanip>
#include "colorconversion.h"
bool check_predicates(point temp) {
	uint t = img.at<uchar>(temp.y, temp.x);
//	cout << "Checking for temp.x: " << temp.x << " temp.y:" << temp.y << endl;
	return (t < THRESHOLD_LIMIT) ? false : true;
}

/**
 * This function calculates the random 20 bacts from the swarm.
 */
point calc_random_bacts() {
	point temp = {0};
	while(!check_predicates(temp)) {
		temp.x = find_random_range(0, 640);
		temp.y = find_random_range(0, 240);
	}
	return temp;
}

int main()
{
	int i, j;
	Mat imgrgb = imread("/home/electron/Pictures/Images/11-11.jpg");
	// Check that the image read is a 3 channels image and not empty
    CV_Assert(imgrgb.channels() == 3);
	if (imgrgb.empty()) {
		cout << "Image is empty. Specify correct path" << endl;
		return -1;
	}
	Mat cbr, ocbr, ihls, test;
//	cv::cvtColor(imgrgb, ihls, CV_RGB2HLS);
	colorconversion::convert_rgb_to_ihls(imgrgb, ihls);
	cv::cvtColor(imgrgb, cbr, CV_RGB2YCrCb);
	remove_upper(ocbr, cbr);
	float n, scrcb = 0, scr2 = 0;
	//some temp values
	for (i=0; i < cbr.rows; i++) {
			for (j=0; j < cbr.cols; j++) {
				cv::Vec3b t = cbr.at<cv::Vec3b>(j, i);
				float cr = (float) t.val[1];
				float cb = (float)t.val[2];
				scr2 += cr * cr;
				if(cr!=0 && cb!=0) {
					scrcb += check_nan(cr/cb);
				}
			}
	}
	cout << "scr2: " << scr2 << " scrcb: " << scrcb << endl;
	n = (0.95 * scr2) / scrcb;
	cout << "N: " << n << endl;
	// variable denoting the total iterations to be executed.
	int totalits = cbr.rows * cbr.cols;
	float lmap[totalits], ucr2;
	// variables for normalization
	float min, max;
	// init flag to find minimum and maximum
	bool iflag = false;
	// lamp index; serves as counter
	int index = 0;
	for (i=0; i < cbr.rows; i++) {
		for (j=0; j < cbr.cols; j++) {
			Vec3b t = cbr.at<Vec3b>(j, i);
			uint ucr = (uint) t.val[1];
			uint ucb = (uint)t.val[2];
			ucr2 = ucr * ucr;
			if(ucr!=0 && ucb!=0) {
				lmap[index] = ucr2 * (ucr2-n*(ucr/ucb)) * (ucr2-n*(ucr/ucb));
//				cout << "lmap: " << std::fixed << std::setprecision(2) << lmap
//									<< endl;
				if (!iflag) {
					// initial condition
					min = lmap[index];
					max = lmap[index];
					iflag = true;
				} else {
					min = (min > lmap[index])? lmap[index] : min;
					max = (max < lmap[index])? lmap[index] : max;
				}
			}
			index++;
		}
	}
	cout << "min: " << min << " max: " << max << endl;
	//normalization process
//	float a = 0, b = 1;
	index = 0;
	for (i=0; i < cbr.rows; i++) {
		for (j=0; j < cbr.cols; j++) {
//			lmap[i] = a + (((lmap[i] - min)*(b - a)) / max-min);
			lmap[index] = check_nan((lmap[index] - min) / (max - min));
			if (lmap[index] > 1.0) {
//				cout << std::fixed << std::setprecision(5)
//				<< "lmap[" << index << "]: " << lmap[index] << endl;
				imgrgb.at<Vec3b>(i,j) = Vec3b(0, 0, 255);
				cout << "i: " << i << " j: " << j << endl;
			}
			index++;
		}
	}
	namedWindow("Test", cv::WINDOW_AUTOSIZE);
	imshow("Test", imgrgb);
	waitKey(0);
	/*
	std::srand(std::time(0));
	Bact b[BACT_NUM];
	for (i=0; i<20; i++) {
		b[i].counter = i;
		r[i] = calc_random_bacts();
		b[i].set_current_pos(r[i]);
		cout << "Point selected at [" << r[i].x << "][" << r[i].y << "] => "
				<< (int)img.at<uchar>(r[i].y, r[i].x) << endl;
	}

// Calculation for histograms start here.
	for(i=0; i< 240; i++) {
		for (j=0; j<640; j++) {
			int temp = img.at<uchar>(i,j);
			histvalue[temp]++;
		}
	}

	// Calculating GLOBAL_MAX
	for (i=0; i<256; i++) {
		histkey[i] = i;
		if (GLOBAL_MAX < histvalue[i]) {
			GLOBAL_MAX = i;
		}
	}
	cout << "GLOBAL_MAX: " << GLOBAL_MAX << endl;
	find_global_point();
//	cout << "GP.x: " << gp.y << "\tGP.y: " << gp.x << " => "
//			<< (int) img.at<uchar>(gp.x, gp.y) << endl;

	for (int k=0; k<NRE; k++) {
		// Selection of 20 bacteria
		// Chemotactic Sequence
		for(i=0; i<BACT_NUM; i++) {
			b[i].counter = i;
			for(j = 0; j < NC; j++) {
				cout << "\nBact " << (i+1) << "." << (j+1) << endl;
				b[i].iteration = j;
				b[i].start_process();
				// Reproduction phase
				if (b[i].jsw > b[i].jhealth) {
					b[i].jhealth = b[i].jsw;
				}
				cout << "JHEALTH: " << b[i].jhealth << endl << endl;
			}
		}
		// sorting stage in reproduction 6.2
		for(i=0; i<BACT_NUM; i++) {
			for (j=i+1; j<BACT_NUM; j++) {
				if (b[i].jhealth > b[j].jhealth) {
					// swap
					Bact t = b[i];
					b[i] = b[j];
					b[j] = t;
				}
			}
		}
		// splitting stage in reproduction 6.3
		for(i=0; i<BACT_NUM/2; i++) {
			b[i] = b[(BACT_NUM/2) + i];
			bs[i] = bs[(BACT_NUM/2) + i];
		}
	}


	cout << endl;
	for(i=0; i<BACT_NUM; i++) {
		cout << "BACT " << (i+1) << ": [" << bs[i].cpos.x << "]["
				<< bs[i].cpos.y << "] "<< "=>" << get_intensity(bs[i].cpos)
				<< endl;
	}
//	cout << "HISTOGRAM: " << endl;
//	for(int i=0; i<20; i++) {
//		cout << bactpos[i] << "=> " << histvalue[bactpos[i]] << endl;
//	}
//	for (int i=0; i<256; i++) {
//		cout << i << ": " << histvalue[i] << endl;
//	}
	Mat dst;
	thresh = 64;
	threshold(img, dst, thresh, 255, 0);
	namedWindow("Test", cv::WINDOW_AUTOSIZE);
//	setMouseCallback("Test", call_back_func, NULL);
	imshow("Test", img);
	waitKey(0);
	*/
	return 0;
}
