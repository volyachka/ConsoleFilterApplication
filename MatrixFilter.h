#include "Image.h"
#include "Filter.h"
#pragma once
class MatrixFilter : public Filter {
protected:
    using Matrix = std::vector<std::vector<int>>;

    Image DoMatrixFilter(const Image &image, const Matrix& matrix);
};
