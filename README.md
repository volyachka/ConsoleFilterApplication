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
example.bmp
![example](https://user-images.githubusercontent.com/102247359/162234624-07f80e53-c97b-44e8-babe-3d91cdf633f1.jpg)

examples/example.bmp examples/output.bmp -crop 1600 1800 -blur 15

![output (3)](https://user-images.githubusercontent.com/102247359/162233791-455f4d60-475e-4f85-b871-6e61d7f0982e.jpg)


examples/example.bmp examples/output.bmp -edge 0.14

![output (2)](https://user-images.githubusercontent.com/102247359/162233129-22004b5e-618b-430a-b7a8-d9e4e2e93aa6.jpg)


examples/example.bmp examples/output.bmp -sharp -fish

![output (1)](https://user-images.githubusercontent.com/102247359/162231399-99a68c11-65db-49b5-a03c-1d3be5ceb9bf.jpg)


examples/example.bmp examples/output.bmp -neg

![output](https://user-images.githubusercontent.com/102247359/162229850-baab41f8-5870-41b6-b11c-6afa582ca250.jpg)

