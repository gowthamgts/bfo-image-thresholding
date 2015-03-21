//============================================================================
// Name        : main.cpp
// Author      : Gowtham Gopalakrishnan
// Copyright   : There is none. You're free to use.
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <string>

//contains all the predefined consts and opencv headers.
#include "predefines.h"
//preprocessing stuff contains remove_upper and a GLOBAL_MAX
#include "preprocessing.h"
#include "bact.h"
using namespace std;

/**
 * This function will return true if the random key is already present
 * in the array.
 *
 * @return true if present else false.
 */
//bool check_presence(int index) {
//	int i = 0;
//	while(i < index) {
//		if (bactpos[index] == bactpos[i]) {
//			return true;
//		}
//		i++;
//	}
//	return false;
//}

bool check_predicates(point temp) {
	uint t = img.at<uchar>(temp.y, temp.x);
	return (t < 30) ? false : true;
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
	cv::Mat imgrgb = imread("/home/electron/Pictures/ImageOutput/crop-1.jpg");
	// Check that the image read is a 3 channels image and not empty
    CV_Assert(imgrgb.channels() == 3);
	if (imgrgb.empty()) {
		cout << "Image is empty. Specify correct path" << endl;
		return -1;
	}
	cv::cvtColor(imgrgb, img, CV_BGR2GRAY);

	Bact b[BACT_NUM];
	point r[20];
	for (i=0; i<20; i++) {
		b[i].set_current_pos(calc_random_bacts());
		cout << "Point selected at [" << r[i].x << "][" << r[i].y << "] => " << (int)img.at<uchar>(r[i].y, r[i].x) << endl;
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
	cout << "GP.x: " << gp.y << "\tGP.y: " << gp.x << " => " << (int) img.at<uchar>(gp.x, gp.y) << endl;


//	for(i=0; i< BACT_NUM; i++) {
//		b[i].set_current_pos(r[i]);
//	}

	for (int k=0; k<NRE; k++) {
		// Selection of 20 bacteria
		// Chemotactic Sequence
		for(i=0; i<BACT_NUM; i++) {
			for(j = 0; j < NC; j++) {
				cout << "\nBact " << (i+1) << "." << (j+1) << endl;
				b[i].counter = i;
				b[i].start_process();
				// Reproduction phase
				if (b[i].jsw > b[i].jhealth) {
					b[i].jhealth = b[i].jsw;
				}
//				cout << "JHEALTH: " << b[i].jhealth << endl << endl;
				break;
			}
			break;
		}
		break;
		/*
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
			bactpos[i] = bactpos[(BACT_NUM/2) + i];
		}
		*/
	}
//	cout << endl;
//	for(i=0; i<BACT_NUM; i++) {
//		cout << "BACT " << (i+1) << ": " << bactpos[i] << "=>" << histvalue[bactpos[i]] <<endl;
//	}
//	cout << "HISTOGRAM: " << endl;
//	for(int i=0; i<20; i++) {
//		cout << bactpos[i] << "=> " << histvalue[bactpos[i]] << endl;
//	}
//	for (int i=0; i<256; i++) {
//		cout << i << ": " << histvalue[i] << endl;
//	}
//	namedWindow("Test", WINDOW_NORMAL);
//	imshow("Test", img);
//	waitKey(0);
	return 0;
}
