#include "Image.h"

Image::Image(const int64_t& height, const int64_t& width) : width_(std::move(width)), height_(std::move(height)) {
    pixels_.resize(height_);
    for (size_t i = 0; i < height_; ++i) {
        pixels_[i].resize(width_);
    }
}

void Image::SetPixel(const int64_t& x, const int64_t& y, const Pixel &pixel) {
    pixels_[y][x].blue = pixel.blue;
    pixels_[y][x].green = pixel.green;
    pixels_[y][x].red = pixel.red;

}

struct Pixel Image::GetPixel(const int64_t& x, const int64_t& y) const {
    return pixels_[y][x];
}

int64_t Image::GetWidth() const {
    return width_;
}

int64_t Image::GetHeight() const {
    return height_;
}

Image &Image::operator=(const Image& other) {
    width_ = other.width_;
    height_ = other.height_;
    pixels_ = std::move(other.pixels_);
    return *this;
}

void Image::ModifyNegativeHeight() {
    height_ = -height_;
    std::reverse(pixels_.begin(), pixels_.end());

}

Pixel Pixel::operator+(const Pixel &other) const{
    Pixel new_pixel(red, green, blue);
    new_pixel += other;
    return new_pixel;
}

Pixel Pixel::operator*(const int64_t& other) const{
    Pixel new_pixel(red, green, blue);
    new_pixel *= other;
    return new_pixel;
}


Pixel Pixel::operator+=(const Pixel& other) {
    red += other.red;
    green += other.green;
    blue += other.blue;
    return *this;
}

Pixel Pixel::operator*=(const Pixel& other) {
    red *= other.red;
    green *= other.green;
    blue *= other.blue;
    return *this;
}

Pixel::Pixel(const uint8_t &r, const uint8_t &g, const uint8_t &b)  : red(r), green(g), blue(b) {}

Pixel Pixel::operator*=(const int64_t &other) {
    red *= other;
    green *= other;
    blue *= other;
    return *this;
}
