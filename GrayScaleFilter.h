#include "Image.h"
#include "Filter.h"
#pragma once
class GrayScaleFilter : public Filter {
public :
    Image Apply(const Image &image) override;
};


