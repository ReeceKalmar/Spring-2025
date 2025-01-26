/*
 * Author: Reece Kalmar
 * Date: 01/24/2025
 * This program takes a integer input and draws a Barnsley Fern onto a png.
 */

#include "pngWriter.h"
#include "point.h"
#include "transform.h"
#include <cstdlib>

// Global constants
const double xMax = 2.75;
const double yMax = 10.1;
const Transform transformations[4] = {{0.0, 0.0, 0.0, 0.0, 0.16, 0.0},
                                      {0.2, -0.26, 0.0, 0.23, 0.22, 1.6},
                                      {-0.15, 0.28, 0.0, 0.26, 0.24, 0.44},
                                      {0.85, 0.04, 0.0, -0.04, 0.85, 1.6}};

// Global variables, these are here to simplify the methods, instead of passing
// them as inputs to parameters.
int height = 0;
int width = 0;

// Randomly selects an number from 0 - 3 representing which transformation
// to use from the array of transformations.
int selectTransformation() {
  int range = (std::rand() % 100) + 1; // 1-100
  if (range == 1)
    return 0; // 1%
  else if (range <= 8)
    return 1; // 7%
  else if (range <= 15)
    return 2; // 7%
  else {
    return 3; // 85%
  }
}

// Performs the iterations to generate the fern
void performIterations(int iterations, char *fileName) {
  Point pt{0, 0};
  PNGWriter img{static_cast<unsigned int>(height),
                static_cast<unsigned int>(width)};

  for (int i = 0; i < iterations; i++) {
    int transformIndex = selectTransformation();
    pt *= transformations[transformIndex];

    int x = pt.getX();
    int y = pt.getY();

    int pixelX = (int)((double)width / 2 * (1 + x / xMax));
    int pixelY = (int)((height - 1) * (1 - y / yMax));

    img.setPixel(pixelX, pixelY, 255, 0, 0, 255);
  }

  img.saveToFile(fileName);
}

int main(int argc, char *argv[]) {
  if (argc < 5) {
    std::cerr << "Usage: fernPNG <output_file> <width> <height> <iterations>\n";
    return -1;
  }

  width = strtol(argv[2], NULL, 10);
  height = strtol(argv[3], NULL, 10);
  int iterations = strtol(argv[4], NULL, 10);
  if (width <= 0 || height <= 0) {
    std::cout << "Invalid width and/or height";
    return 0;
  }

  performIterations(iterations, argv[1]);

  return 0;
}
