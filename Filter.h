#include "Image.h"
#pragma once
class Filter {
public:
    virtual Image Apply(const Image &image) = 0;
};

