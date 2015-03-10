//============================================================================
// Name        : main.cpp
// Author      : Gowtham Gopalakrishnan
// Version     :
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

int find_random() {
	return rand() % 255;
}

/**
 * This function will return true if the random key is already present
 * in the array.
 *
 * @return true if present else false.
 */
bool check_presence(int index) {
	int i = 0;
	while(i < index) {
		if (bactpos[index] == bactpos[i]) {
			return true;
		}
		i++;
	}
	return false;
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
	cv::Mat img;
	cv::cvtColor(imgrgb, img, CV_BGR2GRAY);
	for(i=0; i< 240; i++) {
		for (j=0; j<640; j++) {
			int temp = img.at<uchar>(j,i);
			histvalue[temp]++;
		}
	}
	for (i=0; i<256; i++) {
		histkey[i] = i;
		if (GLOBAL_MAX < histvalue[i]) {
			GLOBAL_MAX = i;
			gp.x = i;
			gp.y = histvalue[i];
		}
	}
	cout << "GLOBAL_MAX: " << GLOBAL_MAX << endl;
//	cout << "gp.x: " << gp.x << " gp.y: " << gp.y << endl;

	Bact b[BACT_NUM];
	for(i=0; i<BACT_NUM; i++) {
		again:
		bactpos[i] = find_random();
		int intvalue = histvalue[bactpos[i]];
		if (intvalue ==0 && check_presence(i)) {
			goto again;
		} else {
//				cout << "Calculating for the bacteria[" << bactpos[i] << "]: " << intvalue << endl;
		}
	}
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
//			cout << "JHEALTH: " << b[i].jhealth << endl << endl;
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
			bactpos[i] = bactpos[(BACT_NUM/2) + i];
		}
	}
	cout << endl;
	for(i=0; i<BACT_NUM; i++) {
		cout << "BACT " << (i+1) << ": " << bactpos[i] << "=>" << histvalue[bactpos[i]] <<endl;
	}
//	cout << "HISTOGRAM: " << endl;
//	for(int i=0; i<20; i++) {
//		cout << bactpos[i] << "=> " << histvalue[bactpos[i]] << endl;
//	}
//	for (int i=0; i<256; i++) {
//		cout << i << ": " << histvalue[i] << endl;
//	}
	return 0;
}
