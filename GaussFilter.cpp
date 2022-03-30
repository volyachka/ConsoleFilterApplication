#include "GaussFilter.h"
#include "cmath"
#include "numbers"

struct DoublePixel {
    DoublePixel() = default;

    double red = 0;
    double green = 0;
    double blue = 0;

    DoublePixel &operator*=(double other) {
        red *= other;
        green *= other;
        blue *= other;
        return *this;
    }
};

Pixel FloatToInt(DoublePixel &pixel) {
    return {static_cast<uint8_t> (pixel.red), static_cast<uint8_t> (pixel.green), static_cast<uint8_t> (pixel.blue)};
}

GaussFilter::GaussFilter(double sigma) : sigma_(sigma) {
}

Image GaussFilter::Apply(const Image &image) {
    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();
    Image tmp_image(height, width);
    Image answer(height, width);
    std::vector<double> coefficient(static_cast<int32_t>(6 * sigma_ + 1));
    double summ = 0;
    int32_t border = static_cast<int32_t>(3 * sigma_);
    for (int32_t i = 0; i < 2 * border + 1; ++i) {
        coefficient[i] = exp(-pow(-border + i, 2) / (2 * pow(sigma_, 2))) / (pow(2 * std::numbers::pi, 0.5) * sigma_);
        summ += coefficient[i];
    }
    for (int32_t y = 0; y < height; ++y) {
        for (int32_t x = 0; x < width; ++x) {
            DoublePixel double_pixel;
            for (int32_t i = -border; i <= border; ++i) {
                if (x + i >= 0 && x + i < width) {
                    Pixel tmp_pixel = image.GetPixel(x + i, y);
                    double_pixel.red += tmp_pixel.red * coefficient[border + i];
                    double_pixel.green += tmp_pixel.green * coefficient[border + i];
                    double_pixel.blue += tmp_pixel.blue * coefficient[border + i];
                }
            }
            double_pixel *= 1 / summ;
            tmp_image.SetPixel(x, y, FloatToInt(double_pixel));
        }
    }
    for (int32_t x = 0; x < width; ++x) {
        for (int32_t y = 0; y < height; ++y) {
            DoublePixel double_pixel;
            for (int32_t i = -border; i <= border; ++i) {
                if (y + i >= 0 && y + i < height) {
                    Pixel tmp_pixel = tmp_image.GetPixel(x, y + i);
                    double_pixel.red += tmp_pixel.red * coefficient[border + i];
                    double_pixel.green += tmp_pixel.green * coefficient[border + i];
                    double_pixel.blue += tmp_pixel.blue * coefficient[border + i];
                }
            }
            double_pixel *= 1 / summ;
            answer.SetPixel(x, y, FloatToInt(double_pixel));
        }
    }
    return answer;
}
