#pragma once
#include "predefines.h"
#include "opencv2\core\core.hpp"

#include <iostream>
#include <vector>
using namespace cv;
using namespace std;
namespace kapur {
	float calc(const Mat& original, int height, int width);
	struct_h calc_kapur_struct(const Mat& original);
}
