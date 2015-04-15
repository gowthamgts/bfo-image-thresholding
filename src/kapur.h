#pragma once
#include "predefines.h"
#include "opencv2/core/core.hpp"
#include <vector>
using namespace cv;
using namespace std;
namespace kapur {
	float calc();
}
float kapur::calc() {
	int i;
	float pi[256] = {0};
	for (i=0; i < BACT_NUM; i++) {
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
	return j1;
}
