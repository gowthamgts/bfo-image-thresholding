#pragma once
#include <iostream>
#include "predefines.h"
#include "kapur.h"
using namespace std;
using namespace cv;



class Bact {
private:
	float j = 0, jcc = 0, random_num = 0;
public:
	int counter = 0, iteration = 0;
	float jsw = 0, jlast = 0, jhealth = 0;
	// This function handles all the chemotactic steps
	// needed for each bacterium.
	void start_process() {
		jsw = calc_jsw(true);
		jlast = jsw;
		find_next_pos();
		jsw = calc_jsw(false);
		// Swimming process
		int m = 0;
		while(m<NS) {
			if(jsw < jlast) {
				jlast = jsw;
				find_next_pos();
				jsw = calc_jsw(false);
			} else {
				m = NS;
			}
			m++;
		}
	}

	float calc_jsw(bool current) {
		float t1 = 0, t2 = 0;
		float distance;
		for (int t = 0; t < BACT_NUM; t++) {
			distance = calc_distance(bs[t].cpos);
			t1 += (float)(-0.1 * exp(-0.2 * distance * distance));
			t2 += (float)(-0.1 * exp(-10 * distance * distance));
		}
		jcc = t1 + t2;
		j = kapur::calc();
		return j + jcc;
	}

	/**
	 * This function calculates the distances between the global_max
	 * and the specified point
	 */
	int calc_distance(point cp) {
		return (((int) img.at<uchar>(gp.x, gp.y)) - ((int) img.at<uchar>(cp.x,
				cp.y)));
	}

	/**
	 * This function will find the next position for the bacteria and
	 * stores it in next_pos
	 */
	void find_next_pos() {
		random_num = find_random_range(-1, 1);
		float move = STEP_SIZE * random_num;
		bs[counter].npos = bs[counter].cpos;
		bs[counter].npos.x = round(bs[counter].npos.x + move);
		bs[counter].npos.y = round(bs[counter].npos.y + move);
		int t = get_intensity(bs[counter].npos);
		if (t > THRESHOLD_LIMIT) {
			bs[counter].cpos = bs[counter].npos;
		}
	}

	void set_current_pos(point p) {
		bs[counter].cpos = p;
	}
};
