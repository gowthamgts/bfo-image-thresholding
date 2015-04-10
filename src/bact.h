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
//		cout << "JLASTB: " << jlast << endl;
//		cout << "JSWB: " << jsw << endl;
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
//		cout << "JLAST: " << jlast << endl;
//		cout << "JSW: " << jsw << endl;
	}

	float calc_jsw(bool current) {
		float t1 = 0, t2 = 0;
		float distance;
		for (int t = 0; t < BACT_NUM; t++) {
//			if (!current && counter == t) {
				// calc with current positions.
				distance = calc_distance(bs[t].cpos);
//			} else {
//				distance = calc_distance(current_pos[t][iteration]);
//			}
//			cout << "DIST: " << distance << endl;
//			distance = .1;
			//TODO check paper. output produces 0 for both t1 and t2
			t1 += (float)(-0.1 * exp(-0.2 * distance * distance));
			t2 += (float)(-0.1 * exp(-10 * distance * distance));
//			cout << "t1: " << t1 << " t2: " << t2 << endl<< endl;
		}
		jcc = t1 + t2;
//		cout << "JCC: " << jcc << endl;
		j = kapur::calc();
//		cout << "KAPUR: " << j << endl;
		return j + jcc;
	}

	/**
	 * This function calculates the distances between the global_max
	 * and the specified point
	 */
	int calc_distance(point cp) {
//		cout << "Global point: " << gp.x << " " << gp.y << endl;
//		cout << "Current point: " << cp.x << " " << cp.y << endl;
//		return ((gp.x-cp.x) * (gp.x-cp.x)) + ((gp.y-cp.y) * (gp.y-cp.y));
		return (((int) img.at<uchar>(gp.x, gp.y)) - ((int) img.at<uchar>(cp.x,
				cp.y)));
	}

	/**
	 * This function will find the next position for the bacteria and
	 * stores it in next_pos
	 */
	void find_next_pos() {
		random_num = find_random_range(-1, 1);
//		float move = STEP_SIZE * (random_num / sqrt(random_num*random_num));
		float move = STEP_SIZE * random_num;
//		next_pos[counter] = current_pos[counter];
//		cout << "CURR_POS: " << current_pos[counter].x << "\t"
//				<< current_pos[counter].y << " => "
//				<< get_intensity(current_pos[counter]) << endl;
//		next_pos[counter].x = round(next_pos[counter].x + move);
//		next_pos[counter].y = round(next_pos[counter].y + move);
//		int t = get_intensity(next_pos[counter]);
//		if (t < THRESHOLD_LIMIT) {
//			// not eligibile position falling back.
//			current_pos[counter+1] = current_pos[counter];
//		} else {
//			current_pos[counter+1] = next_pos[counter];
//		}
//		cout << "NEXT_POS: " << next_pos[counter].x << "\t"
//				<< next_pos[counter].y << " => " << t << endl;
		bs[counter].npos = bs[counter].cpos;
//		cout << "CPOS: [" << bs[counter].cpos.x << "][" << bs[counter].cpos.y << "] => "
//				<< get_intensity(bs[counter].cpos) << endl;
		bs[counter].npos.x = round(bs[counter].npos.x + move);
		bs[counter].npos.y = round(bs[counter].npos.y + move);
//		cout << "NPOS: [" << bs[counter].npos.x << "][" << bs[counter].npos.y << "] => "
//						<< get_intensity(bs[counter].npos) << endl;
		int t = get_intensity(bs[counter].npos);
		if (t > THRESHOLD_LIMIT) {
			// change the position
//			cout << "Counter: " << counter << endl;
			bs[counter].cpos = bs[counter].npos;
		}
	}

	void set_current_pos(point p) {
//		current_pos[counter] = p;
		bs[counter].cpos = p;
	}
};
