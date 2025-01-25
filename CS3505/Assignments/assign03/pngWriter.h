#pragma once

/*
This is a wrapper class that uses libpng
to open/create a new png image and write to it

By Reece Kalmar
01/24/2025
*/

#include <png.h>

class PNGWriter {
private:
  png_structp pngStruct;
  png_infop pngInfo;
  png_bytep *imageDatap;
  png_byte *rowDatap;

  unsigned int height;
  unsigned int width;

  void initPNG();

public:
  // PNGWriter();
  // PNGWriter(char *fileName);
  PNGWriter(unsigned int height, unsigned int width);
  ~PNGWriter();
  // bool isPng(char *fileName);
  void setPixel(unsigned int x, unsigned int y, unsigned char r,
                unsigned char g, unsigned char b, unsigned char a);
  void saveToFile(char *fileName);
};
