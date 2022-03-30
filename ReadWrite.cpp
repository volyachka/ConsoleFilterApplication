#include "ReadWrite.h"
#include "Image.h"
#include "ExceptionInFilter.h"

namespace {
    template<typename T>
    void Read(std::ifstream &input, T &value) {
        input.read(reinterpret_cast<char *>(&value), sizeof(value));
    }

    template<typename T>
    void Write(std::ofstream &output, T &value) {
        output.write(reinterpret_cast<const char *>(&value), sizeof(value));
    }

    void Skip(std::ifstream &input, const int count) {
        input.seekg(count, std::ios::cur);
    }

    void WriteZeros(std::ofstream &output, const int count) {
        for (size_t i = 0; i < count; ++i) {
            output.write("\0", 1);
        }
    }

    int GetPadding(const int pixel_width) {
        return (4 - (pixel_width * 3) % 4) % 4;
    }

    void WriteInformation(unsigned char *information_header, const int32_t &information, int i) {
        information_header[i] = information;
        information_header[i + 1] = information >> 8;
        information_header[i + 2] = information >> 16;
        information_header[i + 3] = information >> 24;
    }

    void WritePadding(std::ofstream &output, const int padding) {
        unsigned char color_padding[3] = {0, 0, 0};
//        if (padding > 3) {
//            throw std::invalid_argument("Padding should be < 3, but got " + std::to_string(padding));
//        }
        output.write(reinterpret_cast<char *> (&color_padding), padding);
    }

    void FillZeroes(unsigned char *information_header, int information_header_size) {
        for (int i = 0; i < information_header_size; ++i) {
            information_header[i] = 0;
        }
    }
}

Image image::ReadBMP(const char *path) {
    int32_t size = 0;
    int32_t offset = 0;
    int32_t pixel_width = 0;
    int32_t pixel_height = 0;
    int padding = 0;
    char header[2];
    std::ifstream input(path, std::ios::in | std::ios::binary);
    if (input.is_open()) {
        try {
            Read(input, header);
            if (header[0] != 'B' || header[1] != 'M') {
                throw InvalidFormat(header);
            }
            Read(input, size);
            Skip(input, 4);
            Read(input, offset);
            Skip(input, 4);
            Read(input, pixel_width);
            Read(input, pixel_height);
        }
        catch (const std::invalid_argument &e) {
            throw InvalidParameterInHeader(e.what());
        }
        padding = GetPadding(pixel_width);
    } else {
        throw FileOpenFailedException(path);
    }
    Image image(pixel_width, pixel_height);
    if (input.is_open()) {
        input.seekg(offset, std::ios::beg);
        for (int64_t y = 0; y < pixel_height; ++y) {
            for (int64_t x = 0; x < pixel_width; ++x) {
                uint8_t color[3];
                try {
                    Read(input, color);
                } catch (std::invalid_argument &e) {
                    throw InvalidByte();
                }
                Pixel pixel(static_cast<uint8_t>(color[2]), static_cast<uint8_t>(color[1]),
                            static_cast<uint8_t>(color[0]));
                image.SetPixel(x, y, pixel);
            }
            input.ignore(padding);
        }
        input.close();
    } else {
        throw FileOpenFailedException(path);
    }
    if ((pixel_height < 0)) {
        image.ModifyNegativeHeight();
    }
    return image;
}

const int32_t OFFSET = 54;
const unsigned char HEADER[] = {'B', 'M'};
const int INFORMATION_HEADER_SIZE = 40;
unsigned char information_header[INFORMATION_HEADER_SIZE];
const int NUMBER_OF_BITS_PER_PIXEL = 24;
const int NUMBER_OF_COLOR_PLANES = 1;

void image::WriteBMP(const char *path, const Image &image) {
    const int32_t width = image.GetWidth();
    const int32_t height = image.GetHeight();
    int padding = GetPadding(width);
    int32_t size = OFFSET + image.GetWidth() * image.GetHeight() * 3 + padding * image.GetHeight();
    std::ofstream output(path, std::ios::out | std::ios::binary);
    if (output.is_open()) {
        Write(output, HEADER);
        Write(output, size);
        WriteZeros(output, 4);
        Write(output, OFFSET);
        FillZeroes(information_header, INFORMATION_HEADER_SIZE);
        information_header[0] = INFORMATION_HEADER_SIZE;
        WriteInformation(information_header, width, 4);
        WriteInformation(information_header, height, 8);
        information_header[12] = NUMBER_OF_COLOR_PLANES;
        information_header[14] = NUMBER_OF_BITS_PER_PIXEL;
        Write(output, information_header);
        for (int64_t y = 0; y < height; ++y) {
            for (int64_t x = 0; x < width; ++x) {
                uint8_t color[3];
                Pixel pixel = image.GetPixel(x, y);
                color[0] = pixel.blue;
                color[1] = pixel.green;
                color[2] = pixel.red;
                Write(output, color);
            }
            WritePadding(output, padding);
        }
    }
    output.close();
}