/*
 * Author: Reece Kalmar
 * Date: 01/24/2025
 * This program takes a integer input and draws a Barnsley Fern onto a png.
 */

#include "pngWriter.h"
#include "point.h"
#include "transform.h"
#include <cstdlib>
#include <iostream>

// Global Constants
const int probabilities[4] = {1, 7, 7, 85};
const double transformations[4][6] = {{0.0, 0.0, 0.0, 0.0, 0.16, 0.0},
                                      {0.2, -0.26, 0.0, 0.23, 0.22, 1.6},
                                      {-0.15, 0.28, 0.0, 0.26, 0.24, 0.44},
                                      {0.85, 0.04, 0.0, -0.04, 0.85, 1.6}};

const Transform transforms[4]{
    Transform{transformations[0]},
    Transform{transformations[1]},
    Transform{transformations[2]},
    Transform{transformations[3]},
};

Point pt{};

int mapToImage(double value, double maxValue, int resolution) {
  return static_cast<int>((value / maxValue) * resolution);
}

// Function to select a transformation based on probabilities
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
void performIterations(int iterations, PNGWriter image) {

  for (int i = 0; i < iterations; i++) {
    int transformIndex = selectTransformation();
    pt *= transformations[transformIndex];
    // Map the point to image coordinates
    int x = mapToImage(pt.getX(), 2.75, image.getWidth());
    int y = mapToImage(pt.getY(), 10.1, image.getHeight());

    // Ensure the point is within bounds before setting the pixel
    if (x >= 0 && x < image.getWidth() && y >= 0 && y < image.getHeight()) {
      image.setPixel(x, y, 255, 0, 0, 255);
    }
  }
}

// Draws the Barnsley Fern from the image array.
void drawImage(char *fileName, PNGWriter image) { image.saveToFile(fileName); }

// Asks the user for the number of iterations, and calls helper methods
int main(int argc, char *argv[]) {
  if (argc <= 4) {
    std::cout << "incorrect amount of arguments";
    return 0;
  }

  char *fileName = argv[1];
  // Convert arguments to unsigned int safely
  unsigned int width = std::strtoul(argv[2], nullptr, 10);      // Base 10
  unsigned int height = std::strtoul(argv[3], nullptr, 10);     // Base 10
  unsigned int iterations = std::strtoul(argv[4], nullptr, 10); // Base 10

  // Check for conversion errors (e.g., invalid input)
  if (width == 0 || height == 0 || iterations == 0) {
    std::cout << "Invalid arguments: width, height, and iterations must be "
                 "positive integers.";
    return 0;
  }
  if (width > 1000000 || height > 1000000) {
    std::cout << "height x width " << height << " x " << width << " iterations "
              << iterations;
    std::cerr << "Error: Image dimensions exceed maximum supported size "
                 "(1,000,000x1,000,000)."
              << std::endl;
    return 1;
  }

  PNGWriter image{height, width};

  performIterations(iterations, image);
  drawImage(fileName, image);

  return 0;
}
