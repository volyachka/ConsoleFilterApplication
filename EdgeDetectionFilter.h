#include "Image.h"
#include "MatrixFilter.h"

#pragma once

class EdgeDetectionFilter : public MatrixFilter {
public:
    const Matrix matrix = {{0,  -1, 0},
                           {-1, 4,  -1},
                           {0,  -1, 0}};

    EdgeDetectionFilter(double threshold);

    Image Apply(const Image &image) override;

private:
    uint8_t threshold_;
};

