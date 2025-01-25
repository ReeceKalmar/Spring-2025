#include "pngWriter.h"
#include <cstdio>
#include <cstdlib>
#include <png.h>
#include <stdexcept>

PNGWriter::PNGWriter(unsigned int height, unsigned int width)
    : height(height), width(width) {

  // Initializes the image data array.
  imageDatap = new png_bytep[height]{};
  rowDatap = new png_byte[height * width * 4]();

  // We initialize one contigous block of memory and use pointers
  // to the addresses for the 2d array.
  for (unsigned int y = 0; y < height; ++y) {
    imageDatap[y] = rowDatap + y * width * 4;
  }
}

PNGWriter::~PNGWriter() {
  if (imageDatap) {
    delete[] imageDatap;
  }
  delete[] rowDatap;
}

void PNGWriter::setPixel(int x, int y, unsigned char r, unsigned char g,
                         unsigned char b, unsigned char a) {
  int offset = x * 4;

  imageDatap[y][offset + 0] = r;
  imageDatap[y][offset + 1] = g;
  imageDatap[y][offset + 2] = b;
  imageDatap[y][offset + 3] = a;
}

void PNGWriter::saveToFile(char *fileName) {
  png_structp png =
      png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  png_infop info = png_create_info_struct(png);
  if (!info || !png) {
    png_destroy_write_struct(&png, &info);
    throw std::runtime_error("Failed to create PNG and info struct");
  }

  if (setjmp(png_jmpbuf(png))) {
    png_destroy_write_struct(&png, &info);
    throw std::runtime_error("Error during PNG initialization");
  }

  FILE *fp = fopen(fileName, "wb");

  if (!fp)
    std::runtime_error("Could not create save file stream");

  png_init_io(png, fp);

  // Output is 8bit depth, RGBA format.
  png_set_IHDR(png, info, width, height, 8, PNG_COLOR_TYPE_RGBA,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);

  // These three commands write the png file
  png_write_info(png, info);
  png_write_image(png, imageDatap);
  png_write_end(png, NULL);

  fclose(fp);
}

unsigned int PNGWriter::getHeight() { return height; }
unsigned int PNGWriter::getWidth() { return width; }
