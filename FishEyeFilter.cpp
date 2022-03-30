#include "FishEyeFilter.h"


Image FishEyeFilter::Apply(const Image &img) {
    const int32_t width = img.GetWidth();
    const int32_t height = img.GetHeight();
    Image new_image(height, width);
    double w = static_cast<double>(width);
    double h = static_cast<double>(height);
    for (int64_t y = 0; y < height; ++y) {
        for (int64_t x = 0; x < width; ++x) {
            double xnd = static_cast<double>((2 * x - w) / w);
            double ynd = static_cast<double>((2 * y - h) / h);
            double radius = std::hypot(xnd, ynd);
            if (0 <= radius && radius <= 1) {
                double new_radius = (radius + (1 - sqrt(1 - radius * radius))) / 2;
                if (new_radius <= 1) {
                    double theta = atan2(ynd, xnd);
                    double nx = new_radius * cos(theta);
                    double ny = new_radius * sin(theta);
                    double x2 = (((nx + 1) * width) / 2);
                    double y2 = (((ny + 1) * height) / 2);
                    if (0 <= y2 && y2 < height && 0 <= x2 && x2 < width) {
                        Pixel pixel = img.GetPixel(x2, y2);
                        new_image.SetPixel(x, y, pixel);
                    }
                }
            }
        }
    }
    return new_image;
}