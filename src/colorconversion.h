#ifndef COLORCONVERSION_H_INCLUDED
#define COLORCONVERSION_H_INCLUDED

// stl library
#include <vector>
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#define M_PI 3.14159265358979323846
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
    // Conversion from RGB to IHLS
    void convert_rgb_to_ihls(const cv::Mat& rgb_image, cv::Mat& ihls_image);
    // Theta computation
    inline float retrieve_theta(const unsigned int& r, const unsigned int& g, const unsigned int& b) {
        return acos((r - (g * 0.5) - (b * 0.5)) / sqrtf((r * r) + (g * g) + (b * b) - (r * g) - (r * b) - (g * b)));
    }
    // Saturation computation -- S = max(R, G, B) − min(R, G, B)
    inline float retrieve_saturation(const unsigned int& r, const unsigned int& g, const unsigned int& b) {
        return (mathutils::get_maximum(r, g, b) - mathutils::get_minimum(r, g, b));
    }
}
#endif
