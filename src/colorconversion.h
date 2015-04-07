#pragma once
// stl library
#include <vector>
#define _USE_MATH_DEFINES // for C++
#include <cmath>
// OpenCV library
#include <opencv2/opencv.hpp>

namespace mathutils {

  // Maximum between three values
    inline unsigned int get_maximum(const unsigned int& r, const unsigned int& g, const unsigned int& b) {
        return (r >= g) ? ((r >= b) ? r : b) : ((g >= b) ? g : b);
    }
    // Minimum between three values
    inline unsigned int get_minimum(const unsigned int& r, const unsigned int& g, const unsigned int& b) {
        return (r <= g) ? ((r <= b) ? r : b) : ((g <= b) ? g : b);
    }

}

namespace colorconversion {
    // Saturation computation -- S = max(R, G, B) − min(R, G, B)
    inline float retrieve_saturation(const unsigned int& r, const unsigned int& g, const unsigned int& b) {
        return (mathutils::get_maximum(r, g, b) - mathutils::get_minimum(r, g, b));
    }

    // Conversion from RGB to IHLS
    void convert_rgb_to_ihls(const cv::Mat& rgb_image, cv::Mat& ihls_image) {
    	// Check the that the image has three channels
		CV_Assert(rgb_image.channels() == 3);

		// Create the output image if needed
		ihls_image.create(rgb_image.size(), CV_8UC3);

		// Make the conversion pixel by pixel
		for (int i = 0; i < rgb_image.rows; ++i) {
			const uchar* rgb_data = rgb_image.ptr<uchar> (i);
			uchar* ihls_data = ihls_image.ptr<uchar> (i);
			for (int j = 0; j < rgb_image.cols; ++j) {
				unsigned int b = *rgb_data++;
				unsigned int g = *rgb_data++;
				unsigned int r = *rgb_data++;
				*ihls_data++ = (uchar) retrieve_saturation(r, g, b);
				*ihls_data++ = (uchar) retrieve_saturation(r, g, b);
				*ihls_data++ = (uchar) retrieve_saturation(r, g, b);
			}
		}
    }
}
