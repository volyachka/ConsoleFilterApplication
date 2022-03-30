#include "Image.h"
#include "Filter.h"

#pragma once

class CropFilter : public Filter {
public:

    CropFilter(int32_t height, int32_t width);

    Image Apply(const Image &image) override;

private:
    int32_t height_;
    int32_t width_;
};


