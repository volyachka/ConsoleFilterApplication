#include "CropFilter.h"

CropFilter::CropFilter(int32_t height, int32_t width) : height_(height), width_(width) {}

Image CropFilter::Apply(const Image &image) {
    const int32_t initial_height = image.GetHeight();
    const int32_t initial_width = image.GetWidth();
    Image new_image(std::min(height_, initial_height), std::min(width_, initial_width));
    for (int32_t y = 0; y < std::min(height_, initial_height); ++y) {
        for (int32_t x = 0; x < std::min(width_, initial_width); ++x) {
            new_image.SetPixel(x, y, (image.GetPixel(x, image.GetHeight() - height_ + y)));
        }
    }
    return new_image;
}
