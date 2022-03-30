#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "Image.h"
#include "Filter.h"

#pragma once

class FishEyeFilter : public Filter {
public:
    Image Apply(const Image &image) override;

};