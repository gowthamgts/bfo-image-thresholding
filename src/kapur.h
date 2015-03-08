#pragma once
#include "predefines.h"
#include "opencv2/core/core.hpp"
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;
namespace kapur {
//	float calc(const Mat original);
//	struct_h calc_kapur_struct(const Mat& original);
	float calc1();
	float calc();
}


//struct_h kapur::calc_kapur_struct(const Mat& original) {
//	int i, j, t;
//	static int mat[640][480];
//	int intvalue[256];
//	struct_h returner = {0, 0};
//	fill_n(intvalue, 256, 0);
//	for(i=320; i<640; i++) {
//        for(j=0; j<480; j++) {
//			t = (int)original.at<uchar>(j, i);
//			mat[i][j] = t;
//			intvalue[t]++;
//        }
//    }
//
//    //cout << "The different intensity values were: " << endl;
//	int index = 0;
//	int rintvalue[256];
//	fill_n(rintvalue, 256, 0);
//	int rintkey[256];
//    for(i=0; i<256; i++) {
//		if(intvalue[i] != 0) {
//			rintkey[index] = i;
//			rintvalue[index] = intvalue[i];
//			//cout<< rintkey[index] << " => " << rintvalue[index] << endl;
//			index++;
//		}
//	}
//    float pi[256] = {0};
//    for (i=0; i < index; i++) {
//        pi[i] = (float)rintvalue[i]/index;
//    }
//
//    float w0 = 0, w1 = 0;
//    for (i=0; i < index/2; i++) {
//        w0 += pi[i];
//    }
//
//    for (i=index/2; i < index; i++) {
//        w1 += pi[i];
//    }
//
//    for(i=0; i < index/2; i++) {
//		float temp = (float)pi[i]/w0;
//		returner.h0 += (float)-(temp * log (temp));
//    }
//
//    for (i=index/2; i < index; i++) {
//		float temp = (float)pi[i]/w1;
//        returner.h1 += (float) - (temp * log (temp));
//    }
//	return returner;
//}
//
//float kapur::calc(const Mat hist) {
//	int index = 0, i, j;
//	int keys[256] = {0};
//	int values[256] = {0};
//	for (i=0; i<256; i++) {
//		float t = hist.at<float>(i);
//		if(t!=0.0) {
//			keys[index] = i;
//			values[index] = t;
//			//cout << "keys[" << index << "]: " << values[index] << endl;
//			index++;
//		}
//	}
//
//    float pi[256] = {0};
//    for (i=0; i < index; i++) {
//        pi[i] = (float)values[i]/index;
//    }
//
//    float w0 = 0, w1 = 0, h0 = 0, h1 = 0;
//    for (i=0; i < index/2; i++) {
//        w0 += pi[i];
//    }
//
//    for (i=index/2; i < index; i++) {
//        w1 += pi[i];
//    }
//
//    for(i=0; i < index/2; i++) {
//		float temp = (float)pi[i]/w0;
//        h0 += (float)-(temp * log (temp));
//    }
//
//    for (i=index/2; i < index; i++) {
//		float temp = (float)pi[i]/w1;
//        h1 += (float) - (temp * log (temp));
//    }
//
//    float j1;
//    j1 = h0 + h1;
//
//    //cout << "w0:" << w0 << endl << "w1:" << w1 << endl << "h0:" << h0 << endl << "h1:" << h1 << endl << "J:" << j1 << endl;
//	return j1;
//}

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
		pi[i] = (float)histvalue[bactpos[i]]/BACT_NUM;
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
