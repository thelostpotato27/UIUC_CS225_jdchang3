#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>



void rotate(std::string inputFile, std::string outputFile) {
  using cs225::HSLAPixel;
  using cs225::PNG;

  PNG* out1 = new PNG();
  out1 -> readFromFile(inputFile);
  unsigned width = out1 -> width();
  unsigned height = out1 -> height();
  PNG* out2 = new PNG(width, height);
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
      HSLAPixel & pixel = out1 -> getPixel(x, y);
      out2 -> getPixel(width-1-x, height-1-y) = pixel;
    }
  }
  out2 -> writeToFile(outputFile);
}



cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  using cs225::HSLAPixel;
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
      HSLAPixel & pixel = png.getPixel(x, y);
      pixel.s = 1;
      pixel.h = (x+y) % 360;
      pixel.l = .5;
    }
  }

  for (unsigned y = 0; y < height; y++) {
    for (unsigned x = 0; x < width - y; x++) {
      HSLAPixel & pixel = png.getPixel(x, y);
      pixel.h = 25;
    }
  }
  for (unsigned y = 0; y < height; y++) {
    for (unsigned x = 0; x < y; x++) {
      HSLAPixel & pixel = png.getPixel(x, y);
      pixel.h = 205;
    }
  }

  return png;
}
