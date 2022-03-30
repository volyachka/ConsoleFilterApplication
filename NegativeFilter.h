#include "Image.h"
#include "Filter.h"
#pragma once

class NegativeFilter : public Filter {
public:
    Image Apply(const Image &image) override;
};
