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
	int counter = 0;
	float jsw = 0, jlast = 0, jhealth = 0;

	// This function handles all the chemotactic steps needed for each bacterium.
	void start_process() {
		jsw = calc_jsw(true);
		jlast = jsw;
		find_next_pos();
		jsw = calc_jsw(false);
//		cout << "JLASTB: " << jlast << endl;
//		cout << "JSWB: " << jsw << endl;
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
		cout << "JLAST: " << jlast << endl;
		cout << "JSW: " << jsw << endl;
	}

	float calc_jsw(bool current) {
		float t1 = 0, t2 = 0;
		for (int t = 0; t < BACT_NUM; t++) {
			float distance = calc_distance(gp, current_pos[t]);
			cout << "DIST: " << distance << endl;
			t1 += (float)(-0.1 * exp(-0.2 * distance * distance));
			t2 += (float)(-0.1 * exp(-10 * distance * distance));
			cout << "t1: " << t1 << " t2: " << t2 << endl;
		}
		jcc = t1 + t2;
		j = kapur::calc();
		cout << "JCC: " << jcc << endl;
		cout << "J: " << j << endl;
		cout << "JSW: " << jsw << endl;
		return j + jcc;
	}

	/**
	 * This function calculates the distances between the global_max and the specified point
	 */
	float calc_distance(point gp, point cp) {
		return sqrt(((gp.x-cp.x) * (gp.x-cp.x)) + ((gp.y-cp.y) * (gp.y-cp.y)));
	}

	/**
	 * This function will find the next position for the bacteria and stores it in next_pos
	 */
	void find_next_pos() {
		random_num = find_random_range(-1, 1);
//		float move = STEP_SIZE * (random_num / sqrt(random_num*random_num));
		float move = STEP_SIZE * random_num;
		next_pos[counter] = current_pos[counter];
		cout << "CURR_POS: " << next_pos[counter].x << "\t" << next_pos[counter].y << " => " << get_intensity(next_pos[counter]) << endl;
		next_pos[counter].x = round(next_pos[counter].x + move);
		next_pos[counter].y = round(next_pos[counter].y + move);
		int t = get_intensity(next_pos[counter]);
		if (t < 30) {
			// not eligibile position falling back.
			next_pos[counter] = current_pos[counter];
		}
		cout << "NEXT_POS: " << next_pos[counter].x << "\t" << next_pos[counter].y << " => " << t << endl;
	}

	void set_current_pos(point p) {
		current_pos[counter] = p;
	}
};
