#pragma once
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

typedef unsigned int uint;
typedef unsigned short int usint;
typedef short int sint;
typedef struct {
	float h0;
	float h1;
} struct_h;

typedef struct {
	int x;
	int y;
}point;

#define BACT_NUM 20
#define NS 10
#define NC 10
#define NRE 4
//TODO: Verify Step Size
#define STEP_SIZE 1
//TODO: Define the value for DELL_T
#define DELL_T 1
float GLOBAL_MAX = -1;
point gp = {0};
point next_pos[BACT_NUM] = {0};
int bactpos[BACT_NUM] = {0};
int histkey[256];
int histvalue[256] = {0};
