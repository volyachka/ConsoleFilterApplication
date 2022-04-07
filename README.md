Console graphic editor. To see the help, run the application without arguments
The application implements basic filters such as cropping, negative, edge detection, sharpening, fisheye, Gaussian blur. To run the application on the command line, you need to write `{program name} {path to the input file} {path to the output file}
[-{filter name 1} [filter parameter 1] [filter parameter 2] ...]
For example `./image_processor input.tmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5
In this example
1. The image is loaded from the file `input.bmp`
2. Cropped to the image with the beginning in the upper left corner and the size of 800x600 pixels
3. Translates to shades of gray
4. A blur with sigma 0.5 is applied
5. The resulting image is saved to the file `/tmp/output.bmp`
### List of basic filters

#### Crop (-crop width height)
Crops the image to the specified width and height. The upper left part of the image is used.

If the requested width or height exceeds the dimensions of the original image, the available part of the image is given.

#### Grayscale (-gs)
Converts the image to grayscale using the formula

#### Negative (-neg)
Converts an image to a negative using the formula

#### Sharpening (-sharp)
Sharpening. It is achieved by using a matrix

#### Edge Detection (-edge threshold)
Border selection.

#### Gaussian Blur (-blur sigma)

#### Fish eye (-fish)
