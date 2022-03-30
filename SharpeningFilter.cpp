#include "SharpeningFilter.h"
Image SharpeningFilter::Apply(const Image &image) {

    return DoMatrixFilter(image, matrix);
}
