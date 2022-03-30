#include "EdgeDetectionFilter.h"
#include "GrayScaleFilter.h"

#pragma once
const Pixel WHITE_PIXEL = {255, 255, 255};
const Pixel BLACK_PIXEL = {0, 0, 0};

EdgeDetectionFilter::EdgeDetectionFilter(double threshold) : threshold_(threshold) {

}

Image EdgeDetectionFilter::Apply(const Image &image) {
    const int32_t width = image.GetWidth();
    const int32_t height = image.GetHeight();
    Image new_image(height, width);
    GrayScaleFilter gray_scale_filter;
    new_image = gray_scale_filter.Apply(image);
    uint8_t coefficient = static_cast<uint8_t>(threshold_);
    Image answer = DoMatrixFilter(new_image, matrix);
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            Pixel pixel = answer.GetPixel(x, y);
            if (pixel.blue > coefficient) {
                answer.SetPixel(x, y, WHITE_PIXEL);
            } else {
                answer.SetPixel(x, y, BLACK_PIXEL);
            }
        }
    }
    return answer;
}
