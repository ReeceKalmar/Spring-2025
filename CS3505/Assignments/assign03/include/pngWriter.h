#pragma once

/*
This is a wrapper class that uses libpng
to create a new png image and write it.

By Reece Kalmar
01/24/2025
*/

#include <png.h>

// This object represents a png, and has
// instance methods to change and write said PNG.
class PNGWriter {
private:
  // This is a 2d byte array which stores the PNG's row data.
  // Uses smart pointer for better memory management on cases where an exception
  // is thrown.
  png_bytep *imageDatap;

  // This is a byte array used to initialize imageDatap.
  // Uses smart pointer for better memory management on cases where an exception
  // is thrown.
  png_byte *rowDatap;

  // The height of the PNG, as a unsigned int.
  unsigned int height;

  // The width of the PNG, as a unsigned int.
  unsigned int width;

public:
  // This constructor takes an unsigned height and width integer, or defaults to
  // 1000x1000. Produces a PNG with (0, 0, 0, 0) for each RGBA pixel.
  PNGWriter(unsigned int height = 1000, unsigned int width = 1000);

  // Destructor that deletes the dynamically allocated
  // imageDatap and rowDatap variables.
  ~PNGWriter();

  // Setter method that allows you to set a RGBA value of a (height x width)
  // png. Note: the x and y of a PNG is zero based.
  void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b,
                unsigned char a);

  // Takes a character array  fileName as a parameter, saves the current PNG to
  // a newly created file named fileName. Note: after using this you should
  // Destruct/Reinitialize the PNGWriter variable.
  void saveToFile(char *fileName);

  // Getter method that returns an unsigned int for the height of the current
  // PNG.
  unsigned int getHeight();

  // Getter method that returns an unsigned int for the width of the current
  // PNG.
  unsigned int getWidth();
};
