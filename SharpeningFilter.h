#include "Image.h"
#include "MatrixFilter.h"

#pragma once

class SharpeningFilter : public MatrixFilter {
public:
    Matrix matrix = {{0,  -1, 0},
                     {-1, 5,  -1},
                     {0,  -1, 0}};

    Image Apply(const Image &image) override;
};

