#include "Filter.h"
#include "Image.h"
#pragma once
class GaussFilter: public Filter {
private:
    double sigma_;
public:
    GaussFilter(double sigma);
    Image Apply(const Image &image) override;
};

