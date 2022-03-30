#include <string>
#include "Image.h"
#include "ReadWrite.h"
#include "ExceptionInFilter.h"
#include "Parser.h"

int main(int argc, const char *argv[]) {
    if (argc == 1) {
        std::cout << "This is a console graphics editor, with the following filters available: "
                  << std::endl << "Crop (-crop width height),"
                                  " Grayscale (-gs), Negative (-neg), Sharpening (-sharp), " << std::endl <<
                  "Edge Detection (-edge threshold),"
                  " Gaussian Blur (-blur sigma), fish eye (-fish)";
    } else if (argc < 3) {
        throw NotEnoughArgumentsException(argc);
    } else {
        const Image image = image::ReadBMP(argv[1]);
        Parser parser(argc, argv, image);
        parser.Parse();
        Image new_image = parser.GetImage();
        image::WriteBMP(argv[2], new_image);
    }

    return 0;
}