/*
PNGWriter class for CS 3505 assignment 3.
PNGWriter holds a png and methods to manipulate and save
the png to a specified file.

By Reece Kalmar
01/29/2025
*/

#include "pngWriter.h"
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <png.h>
#include <stdexcept>

PNGWriter::PNGWriter(unsigned int height, unsigned int width)
    : imageDatap(std::make_unique<png_bytep[]>(height)),
      rowDatap(std::make_unique<png_byte[]>(height * width * 4)),
      height(height), width(width) {

  // We initialize one contigous block of memory and use pointers
  // to the addresses for the 2d array.
  // This is more efficient than allocating memory for each column.
  for (unsigned int y = 0; y < height; y++) {
    imageDatap[y] = rowDatap.get() + (y * width * 4);
  }
}

PNGWriter::~PNGWriter() {}

void PNGWriter::setPixel(int x, int y, unsigned char r, unsigned char g,
                         unsigned char b, unsigned char a) {
  // Each row stores (width * (bitdepth / 8) * bytesPerPixel).
  // Since currently the bitdepth is 8, meaning one byte per color value (R, G,
  // B, A), and since we use 4 bytes per pixel, one for RGB and another for the
  // alpha value. Theres a total of (width * (8/8) * 4) indices per row.
  int offset = x * 4;

  imageDatap[y][offset + 0] = r;
  imageDatap[y][offset + 1] = g;
  imageDatap[y][offset + 2] = b;
  imageDatap[y][offset + 3] = a;
}

void PNGWriter::saveToFile(char *fileName) {

  // We need to initialize the write struct for the PNG.
  png_structp png =
      png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
    throw std::runtime_error("Failed to create PNG write struct");
  }

  // Aswell, to initialize the header info struct for the PNG.
  png_infop info = png_create_info_struct(png);
  if (!info) {
    png_destroy_write_struct(&png, NULL);
    throw std::runtime_error("Failed to create PNG header info struct");
  }

  // This sets a long jump back to here in case libpng fails, in which case we
  // deallocate the png and info struct.
  if (setjmp(png_jmpbuf(png))) {
    png_destroy_write_struct(&png, &info);
    throw std::runtime_error("Error during PNG initialization");
  }

  // Better memory management for FILE* in case program crashes.
  std::unique_ptr<FILE, int (*)(FILE *)> fp(fopen(fileName, "wb"), fclose);

  if (!fp)
    throw std::runtime_error("Could not create save file stream");

  png_init_io(png, fp.get());

  png_set_IHDR(png, info, width, height, 8, PNG_COLOR_TYPE_RGBA,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);

  // These three commands write the png file
  png_write_info(png, info);
  png_write_image(png, imageDatap.get());
  png_write_end(png, NULL);

  // Clean up any memory
  png_destroy_write_struct(&png, &info);
}

// Simple getter methods for the height and width
unsigned int PNGWriter::getHeight() { return height; }
unsigned int PNGWriter::getWidth() { return width; }
