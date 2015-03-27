#pragma once
#include "predefines.h"
#include "opencv2/core/core.hpp"
#include <vector>
using namespace cv;
using namespace std;
namespace kapur {
	float calc1();
	float calc();
}

float kapur::calc1() {
	int index = 0, i;
	int keys[256] = {0};
	int values[256] = {0};
	for (i=0; i<256; i++) {
		float t = histvalue[i];
		if(t!=0.0) {
			keys[index] = i;
			values[index] = t;
			//cout << "keys[" << index << "]: " << values[index] << endl;
			index++;
		}
	}

    float pi[256] = {0};
    for (i=0; i < index; i++) {
        pi[i] = (float)values[i]/index;
    }

    float w0 = 0, w1 = 0, h0 = 0, h1 = 0;
    for (i=0; i < index/2; i++) {
        w0 += pi[i];
    }

    for (i=index/2; i < index; i++) {
        w1 += pi[i];
    }

    for(i=0; i < index/2; i++) {
		float temp = (float)pi[i]/w0;
        h0 += (float)-(temp * log (temp));
    }

    for (i=index/2; i < index; i++) {
		float temp = (float)pi[i]/w1;
        h1 += (float) - (temp * log (temp));
    }

    float j1 = h0 + h1;
    //cout << "w0:" << w0 << endl << "w1:" << w1 << endl << "h0:" << h0 << endl << "h1:" << h1 << endl << "J:" << j1 << endl;
	return j1;
}
float check_nan(float value) {
	return isnan(value) ? 0 : value;
}
float kapur::calc() {
	int i;
	float pi[256] = {0};
	for (i=0; i < BACT_NUM; i++) {
//		cout << "intensity[" << i << "]: " << histvalue[get_intensity(bs[i].cpos)] << endl;
		pi[i] = (float) (histvalue[get_intensity(bs[i].cpos)]/BACT_NUM);
	}
	float w0 = 0, w1 = 0, h0 = 0, h1 = 0;
	for (i=0; i < BACT_NUM/2; i++) {
		w0 += pi[i];
	}

	for (i=BACT_NUM/2; i < BACT_NUM; i++) {
		w1 += pi[i];
	}

	for(i=0; i < BACT_NUM/2; i++) {
		float temp = (float)pi[i]/w0;
		h0 += (float)-(temp * log (temp));
		h0 = check_nan(h0);
	}

	for (i=BACT_NUM/2; i < BACT_NUM; i++) {
		float temp = (float)pi[i]/w1;
		h1 += (float) - (temp * log (temp));
		h1 = check_nan(h1);
	}

	float j1 = h0 + h1;
	//cout << "w0:" << w0 << endl << "w1:" << w1 << endl << "h0:" << h0 << endl << "h1:" << h1 << endl << "J:" << j1 << endl;
	return j1;
}
