#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>
#include "Filter.h"
#include "NegativeFilter.h"
#include "CropFilter.h"
#include "GaussFilter.h"
#include "GrayScaleFilter.h"
#include "NegativeFilter.h"
#include "SharpeningFilter.h"
#include "EdgeDetectionFilter.h"

class Parser {
public:
    Image& GetImage();

    Parser(int argc, const char *argv[], const Image& image);

    void Parse();

private:
    void Consume();

    void ParseCropFilter();

    void ParseEdgeDetectionFilter();

    void ParseSharpeningFilter();

    void ParseNegativeFilter();
    void ParseFishEyeFilter();
    void ParseGrayScaleFilter();
    void ParseGaussFilter();
    void ApplyFilter();
private:
    Image image_;
    int pos_ = 3;
    const int argc_ = 0;
    const char **argv_;
    std::unique_ptr<Filter> filter_;
    using Command = std::function<void()>;
    std::unordered_map<std::string, Command> commands_;
};


