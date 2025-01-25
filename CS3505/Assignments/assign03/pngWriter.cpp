#include "pngWriter.h"
#include <cstdio>
#include <cstdlib>
#include <png.h>
#include <stdexcept>

void PNGWriter::initPNG() {
  pngStruct = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  pngInfo = png_create_info_struct(pngStruct);
  if (!pngInfo || !pngStruct) {
    png_destroy_write_struct(&pngStruct, &pngInfo);
    throw std::runtime_error("Failed to create PNG and info struct");
  }

  if (setjmp(png_jmpbuf(pngStruct))) {
    png_destroy_write_struct(&pngStruct, &pngInfo);
    throw std::runtime_error("Error during PNG initialization");
  }
  png_set_user_limits(pngStruct, 1000000, 1000000);
}

PNGWriter::PNGWriter(unsigned int height, unsigned int width)
    : height(height), width(width) {

  // Initializes png and info structs, used later for saving png
  PNGWriter::initPNG();

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
  png_destroy_write_struct(&pngStruct, &pngInfo);
  if (imageDatap) {
    delete[] imageDatap;
  }
  delete[] rowDatap;
}

void PNGWriter::setPixel(unsigned int x, unsigned int y, unsigned char r,
                         unsigned char g, unsigned char b, unsigned char a) {
  int offset = x * 4;

  imageDatap[y][offset + 0] = r;
  imageDatap[y][offset + 1] = g;
  imageDatap[y][offset + 2] = b;
  imageDatap[y][offset + 3] = a;
}

void PNGWriter::saveToFile(char *fileName) {
  FILE *fp = fopen(fileName, "wb");

  if (!fp)
    std::runtime_error("Could not create save file stream");

  png_init_io(pngStruct, fp);
  // Output is 8bit depth, RGBA format.
  png_set_IHDR(pngStruct, pngInfo, width, height, 8, PNG_COLOR_TYPE_RGBA,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);

  // These three commands write the png file
  png_write_info(pngStruct, pngInfo);
  png_write_image(pngStruct, imageDatap);
  png_write_end(pngStruct, NULL);

  fclose(fp);

  png_destroy_write_struct(&pngStruct, &pngInfo);
  initPNG();
}

unsigned int PNGWriter::getHeight() { return height; }
unsigned int PNGWriter::getWidth() { return width; }
