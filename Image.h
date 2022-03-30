#include <fstream>
#include <vector>
#include <string>

#pragma once

struct Pixel {
    Pixel() = default;

    Pixel(const uint8_t &r, const uint8_t &g, const uint8_t &b);

    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;

    Pixel operator+(const Pixel &other) const;

    Pixel operator*(const int64_t &other) const;

    Pixel operator*=(const Pixel &other);

    Pixel operator*=(const int64_t &other);

    Pixel operator+=(const Pixel &other);
};


class Image {
public:
    Image(const int64_t &height, const int64_t &width);

    void SetPixel(const int64_t &x, const int64_t &y, const Pixel &pixel);

    Pixel GetPixel(const int64_t &x, const int64_t &y) const;

    int64_t GetWidth() const;

    int64_t GetHeight() const;

    Image &operator=(const Image &other);

    void ModifyNegativeHeight();
private:
    std::vector<std::vector<Pixel>> pixels_;
    int64_t width_;
    int64_t height_;
};

