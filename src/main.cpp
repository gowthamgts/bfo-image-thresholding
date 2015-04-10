//contains all the predefined consts and opencv headers.
#include "predefines.h"
#include <string>
//preprocessing stuff contains remove_upper and a GLOBAL_MAX
#include "preprocessing.h"
#include "bact.h"
#include <ctime>
#include "colorconversion.h"
bool check_predicates(point temp) {
//	cout << "temp.x: " << temp.x << " temp.y: " << temp.y << endl;
	uint t = img.at<uchar>(temp.y, temp.x);
//	cout << t << endl;
	return (t < THRESHOLD_LIMIT) ? false : true;
}

/**
 * This function calculates the random 20 bacts from the swarm.
 */
point calc_random_bacts() {
	point temp = {0};
	while(!check_predicates(temp)) {
		temp.x = find_random_range(270,370);
		temp.y = find_random_range(240,360);
	}
	return temp;
}

int main()
{
	int i, j;
	Mat imgrgb = imread("/home/electron/Pictures/Images/1-11.jpg");
	namedWindow("Original Image", cv::WINDOW_AUTOSIZE);
	imshow("Original Image", imgrgb);
	Mat imgc, imgb;
	// Check that the image read is a 3 channels image and not empty
    CV_Assert(imgrgb.channels() == 3);
	if (imgrgb.empty()) {
		cout << "Image is empty. Specify correct path" << endl;
		return -1;
	}
	colorconversion::convert_rgb_to_ihls(imgrgb, imgc);
	namedWindow("IHLS Image", cv::WINDOW_AUTOSIZE);
	cv::cvtColor(imgc, imgb, CV_BGR2GRAY);
	imshow("IHLS Image", imgb);
	clean_image(imgb, img);
	namedWindow("Cropped Image", cv::WINDOW_AUTOSIZE);
	imshow("Cropped Image", img);
	std::srand(std::time(0));
	Bact b[BACT_NUM];
	for (i=0; i<20; i++) {
		b[i].counter = i;
		r[i] = calc_random_bacts();
		b[i].set_current_pos(r[i]);
//		cout << "Point selected at [" << r[i].x << "][" << r[i].y << "] => "
//				<< (int)img.at<uchar>(r[i].y, r[i].x) << endl;
	}
// Calculation for histograms start here.
	for(i=240; i< 360; i++) {
		for (j=270; j<370; j++) {
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
//	cout << "GLOBAL_MAX: " << GLOBAL_MAX << endl;
	find_global_point();

	for (int k=0; k<NRE; k++) {
		// Selection of 20 bacteria
		// Chemotactic Sequence
		for(i=0; i<BACT_NUM; i++) {
			b[i].counter = i;
			for(j = 0; j < NC; j++) {
//				cout << "\nBact " << (i+1) << "." << (j+1) << endl;
				b[i].iteration = j;
				b[i].start_process();
				// Reproduction phase
				if (b[i].jsw > b[i].jhealth) {
					b[i].jhealth = b[i].jsw;
				}
//				cout << "JHEALTH: " << b[i].jhealth << endl << endl;
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
//	float min = get_intensity(bs[0].cpos);
	float arr[10][2] = {0};

	int index = 0;
	while (index < 10) {
		arr[index][1] = 1;
		index++;
	}
	thresh = 0;
	for(i=0; i<BACT_NUM/2; i++) {
		bool cs = false;
		float inten = (float)get_intensity(bs[i].cpos);
//		cout << "inten: " << i << " => " << inten << endl;
		for (j=0; j<BACT_NUM/2; j++) {
			if (inten == arr[j][0]) {
//				cout << "Match at pos: " << j << ": " << ++arr[j][1] <<endl;
				cs = true;
				break;
			}
		}
		if(!cs) {
			arr[i][0] = inten;
		}
	}
	thresh = arr[0][0];
	float max = arr[0][1];
	for(i=0; i<BACT_NUM/2; i++) {
		if (max < arr[i][1]) {
			max = arr[i][1];
			thresh = arr[i][0];
		}
//		cout << arr[i][0] << ": " << arr[i][1] << endl;
//		cout << "Threshold: " << thresh << endl;
	}
	Mat dst;
	threshold(img, dst, thresh, 255, 0);
	namedWindow("Final Output", cv::WINDOW_AUTOSIZE);
	imshow("Final Output", dst);
	waitKey(0);
	cout << "PSNR: " << getPSNR(img, dst) << endl;
	return 0;
}
