#include "Image.h"
#include "ExceptionInFilter.h"

#pragma once

namespace image {
    Image ReadBMP(const char *path);
    void WriteBMP(const char *path, const Image &image);
}