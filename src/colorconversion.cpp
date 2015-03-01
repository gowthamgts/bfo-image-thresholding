#include "colorconversion.h"

namespace colorconversion {
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

