#include "GrayScaleFilter.h"

Image GrayScaleFilter::Apply(const Image &image) {
    const int32_t width = image.GetWidth();
    const int32_t height = image.GetHeight();
    Image new_image(height, width);
    for (int64_t y = 0; y < height; ++y) {
        for (int64_t x = 0; x < width; ++x) {
            uint8_t color = static_cast<uint8_t>(0.299 * image.GetPixel(x, y).red + 0.587 * image.GetPixel(x, y).green +
                                                 0.114 * image.GetPixel(x, y).blue);
            Pixel pixel(color, color, color);
            new_image.SetPixel(x, y, pixel);
        }
    }
    return new_image;
}