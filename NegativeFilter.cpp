#include "NegativeFilter.h"

Image NegativeFilter::Apply(const Image &image) {
    const int32_t width = image.GetWidth();
    const int32_t height = image.GetHeight();
    Image new_image(height, width);
    for (int64_t y = 0; y < height; ++y) {
        for (int64_t x = 0; x < width; ++x) {
            Pixel pixel(255 - image.GetPixel(x, y).red, 255 - image.GetPixel(x, y).green,
                        255 - image.GetPixel(x, y).blue);
            new_image.SetPixel(x, y, pixel);
        }
    }
    return new_image;
}
