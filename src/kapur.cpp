#include "kapur.h"
using namespace std;

struct_h kapur::calc_kapur_struct(const Mat& original) {
	int i, j, t;
	static int mat[640][480];
	int intvalue[256];
	struct_h returner = {0, 0};
	fill_n(intvalue, 256, 0);
	for(i=320; i<640; i++) {
        for(j=0; j<480; j++) {
			t = (int)original.at<uchar>(j, i);
			mat[i][j] = t;
			intvalue[t]++;
        }
    }

    //cout << "The different intensity values were: " << endl;
	int index = 0;
	int rintvalue[256];
	fill_n(rintvalue, 256, 0);
	int rintkey[256];
    for(i=0; i<256; i++) {
		if(intvalue[i] != 0) {
			rintkey[index] = i;
			rintvalue[index] = intvalue[i];
			//cout<< rintkey[index] << " => " << rintvalue[index] << endl;
			index++;
		}
	}
    float pi[256] = {0};
    for (i=0; i < index; i++) {
        pi[i] = (float)rintvalue[i]/index;
    }

    float w0 = 0, w1 = 0;
    for (i=0; i < index/2; i++) {
        w0 += pi[i];
    }
	
    for (i=index/2; i < index; i++) {
        w1 += pi[i];
    }

    for(i=0; i < index/2; i++) {
		float temp = (float)pi[i]/w0;
		returner.h0 += (float)-(temp * log (temp));
    }

    for (i=index/2; i < index; i++) {
		float temp = (float)pi[i]/w1;
        returner.h1 += (float) - (temp * log (temp));
    }
	return returner;
}

float kapur::calc(const Mat& original, int height, int width) {
	int i, j, t;
	static int mat[640][480];
	int intvalue[256];
	fill_n(intvalue, 256, 0);
	for(i=320; i<640; i++) {
        for(j=0; j<480; j++) {
			t = (int)original.at<uchar>(j, i);
			mat[i][j] = t;
			intvalue[t]++;
        }
    }

    cout << "The different intensity values were: " << endl;
	int index = 0;
	int rintvalue[256];
	fill_n(rintvalue, 256, 0);
	int rintkey[256];
    for(i=0; i<256; i++) {
		if(intvalue[i] != 0) {
			rintkey[index] = i;
			rintvalue[index] = intvalue[i];
			cout<< rintkey[index] << " => " << rintvalue[index] << endl;
			index++;
		}
	}
    float pi[256] = {0};
    for (i=0; i < index; i++) {
        pi[i] = (float)rintvalue[i]/index;
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

    float j1;
    j1 = h0 + h1;

    cout << "w0:" << w0 << endl << "w1:" << w1 << endl << "h0:" << h0 << endl << "h1:" << h1 << endl << "J:" << j1;
	return j1;
}
