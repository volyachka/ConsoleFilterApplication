#include "Parser.h"
#include "ExceptionInFilter.h"
#include "FishEyeFilter.h"

Parser::Parser(int argc, const char **argv, const Image& image) : argc_(argc), argv_(argv), image_(image) {
    commands_["-crop"] = [&]() {
        ParseCropFilter();
    };
    commands_["-gs"] = [&]() {
        ParseGrayScaleFilter();
    };
    commands_["-neg"] = [&]() {
        ParseNegativeFilter();
    };
    commands_["-edge"] = [&]() {
        ParseEdgeDetectionFilter();
    };
    commands_["-sharp"] = [&]() {
        ParseSharpeningFilter();
    };

    commands_["-blur"] = [&]() {
        ParseGaussFilter();
    };
    commands_["-fish"] = [&]() {
        ParseFishEyeFilter();
    };
}

void Parser::Parse() {
    while (pos_ < argc_) {
        Consume();
        ApplyFilter();
    }
}

void Parser::Consume() {
    std::string first_arg(argv_[pos_]);
    auto it = commands_.find(first_arg);

    if (it != commands_.end()) {
        it->second();
    } else {
        throw InvalidFilter(first_arg);
    }
}

void Parser::ParseCropFilter() {
    if (pos_ + 2 >= argc_) {
        throw std::range_error("Not enough arguments for CropFilter ");
    }
    try {
        int64_t width = static_cast<int64_t>(std::stoi(argv_[pos_ + 1]));
        int64_t height = static_cast<int64_t>(std::stoi(argv_[pos_ + 2]));
        filter_ = std::make_unique<CropFilter>(height, width);
    } catch (const std::invalid_argument &e) {
        throw std::invalid_argument(
                "crop parameter should be integer, got " + std::string(argv_[pos_ + 1]) + std::string(argv_[pos_ + 2]));
    }
    pos_ += 3;
}

void Parser::ParseEdgeDetectionFilter() {
    if (pos_ + 1 >= argc_) {
        throw std::out_of_range("Not enough arguments for NegativeFilter ");
    }
    try {
        double threshold = 255. * std::stod(argv_[pos_ + 1]);
        filter_ = std::make_unique<EdgeDetectionFilter>(threshold);
    } catch (const std::invalid_argument &e) {
        throw std::invalid_argument("threshold should be double, got " + std::string(argv_[pos_ + 1]));
    }
    pos_ += 2;
}

void Parser::ParseSharpeningFilter() {
    filter_ = std::make_unique<SharpeningFilter>();
    ++pos_;
}

void Parser::ParseNegativeFilter() {
    filter_ = std::make_unique<NegativeFilter>();
    ++pos_;
}

void Parser::ParseGrayScaleFilter() {
    filter_ = std::make_unique<GrayScaleFilter>();
    ++pos_;
}

void Parser::ApplyFilter() {
    image_ = filter_->Apply(image_);
}

Image& Parser::GetImage(){
    return image_;
}

void Parser::ParseGaussFilter() {
    if (pos_ + 1 >= argc_) {
        throw std::range_error("Not enough arguments for GaussFilter ");
    }
    try {
        double sigma = std::stod(argv_[pos_ + 1]);
        filter_ = std::make_unique<GaussFilter>(sigma);
    } catch (const std::invalid_argument &e) {
        throw std::invalid_argument("sigma should be double, got " + std::string(argv_[pos_ + 1]));
    }
    pos_ += 2;
}

void Parser::ParseFishEyeFilter() {
    filter_ = std::make_unique<FishEyeFilter>();
    ++pos_ ;
}
