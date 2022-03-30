#include <cmath>
#include "MatrixFilter.h"


struct Int64TPixel {
    Int64TPixel() = default;

    int64_t red = 0;
    int64_t green = 0;
    int64_t blue = 0;

    Int64TPixel &operator*=(double other) {
        red *= other;
        green *= other;
        blue *= other;
        return *this;
    }

    Int64TPixel &operator+=(Pixel other) {
        red += other.red;
        green += other.green;
        blue += other.blue;
        return *this;
    }
};

Image MatrixFilter::DoMatrixFilter(const Image &image, const Matrix &matrix) {
    int64_t width = image.GetWidth();
    int64_t height = image.GetHeight();
    int border = static_cast<int>(matrix.size()) / 2;
    Image new_image(height, width);
    for (int64_t y = 0; y < height; ++y) {
        for (int64_t x = 0; x < width; ++x) {
            Int64TPixel new_pixel;
            for (int64_t t = -border; t <= border; ++t) {
                for (int64_t k = -border; k <= border; ++k) {
                    int64_t y_coord = std::min(std::max(int64_t(0), y + t), height - 1);
                    int64_t x_coord = std::min(std::max(int64_t(0), x + k), width - 1);
                    Pixel pixel = image.GetPixel(x_coord, y_coord);
                    new_pixel.red += pixel.red * matrix[t + border][k + border];
                    new_pixel.green += pixel.green * matrix[t + border][k + border];
                    new_pixel.blue += pixel.blue * matrix[t + border][k + border];
                }
            }
            Pixel pixel(std::min(static_cast<int64_t>(255), std::max(new_pixel.red, static_cast<int64_t>(0))),
                        std::min(static_cast<int64_t>(255), std::max(new_pixel.green, static_cast<int64_t>(0))),
                        std::min(static_cast<int64_t>(255), std::max(new_pixel.blue, static_cast<int64_t>(0))));
            new_image.SetPixel(x, y, pixel);
        }
    }
    return new_image;
}
