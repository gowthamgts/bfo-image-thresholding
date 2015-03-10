#pragma once
#include <iostream>
#include "predefines.h"
#include "kapur.h"
#include <random>
using namespace std;
using namespace cv;

class Bact {
private:
	float j = 0, jcc = 0, random_num = 0;
	point current_pos;
public:
	int counter = 0;
	float jsw = 0, jlast = 0, jhealth = 0;
//	Bact(): jcc(0), jhealth(0), random_num(0), jsw(0), counter(0), jlast(0) {;}

	/**
	 * This function handles all the chemotactic steps needed for each bacterium.
	 */
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

	double find_random(int min, int max) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(-1, 1);
		float uniformOn01 = dis(gen);
		return uniformOn01;
	}

	float calc_jsw(bool current) {
		float t1 = 0, t2 = 0;
		for (int t = 0; t < BACT_NUM; t++) {
			point tp = {0};
			if (counter == t && !current) {
				bactpos[t] = next_pos[t].x;
			}
				// calculate for the new position
				tp.x = bactpos[t];
//			}
			tp.y = histvalue[tp.x];
//			cout << "tp.x: " << tp.x << "\ttp.y: " << tp.y << endl;
			float distance = calc_distance(gp.x, gp.y, tp.x, tp.y);
			t1 += (float)(-0.1 * exp(-0.2 * distance * distance));
			t2 += (float)(-0.1 * exp(-10 * distance * distance));
//			cout << "t1: " << (float)(-0.1 * exp(-0.2 * distance * distance)) << endl;
		}
		jcc = t1 + t2;
		j = kapur::calc();
//		cout << "JCC: " << jcc << endl;
//		cout << "J: " << j << endl;
//		cout << "JSW: " << jsw << endl;
		return j + jcc;
	}

	/**
	 * This function calculates the distances between the global_max and the specified point
	 */
	float calc_distance(int x1, int y1, int x2, int y2) {
		return sqrt(((x1-x2) * (x1-x2)) + ((y1-y2) * (y1-y2)));
	}

	/**
	 * This function will find the next position for the bacteria and stores it in next_pos
	 */
	void find_next_pos() {
		random_num = find_random(-1, 1);
		current_pos.x = bactpos[counter];
		current_pos.y = histvalue[bactpos[counter]];
//		float move = STEP_SIZE * (random_num / sqrt(random_num*random_num));
		float move = STEP_SIZE * random_num;
//		cout << "Movement: " << move << endl;
		next_pos[counter] = current_pos;
//		cout << "CURR_POS: " << next_pos[counter].x << "\t" << next_pos[counter].y << endl;
		next_pos[counter].x = round(next_pos[counter].x + move);
		next_pos[counter].y = histvalue[next_pos[counter].x];
//		cout << "NEXT_POS: " << next_pos[counter].x << "\t" << next_pos[counter].y << endl;
	}
};
