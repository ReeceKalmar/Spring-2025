/*
 * Author: Reece Kalmar
 * Date: 01/16/2025
 * This program takes a integer input and draws a Barnsley Fern onto the
 * console.
 */

#include <cstdlib>
#include <iostream>

// Global Constants
const int width = 128;
const int height = 150;
const double xMax = 2.75;
const double yMax = 10.1;
const int probabilities[4] = {1, 7, 7, 85};
const double transformations[4][6] = {{0.0, 0.0, 0.0, 0.0, 0.16, 0.0},
                                      {0.2, -0.26, 0.0, 0.23, 0.22, 1.6},
                                      {-0.15, 0.28, 0.0, 0.26, 0.24, 0.44},
                                      {0.85, 0.04, 0.0, -0.04, 0.85, 1.6}};

// Function to select a transformation based on probabilities
int selectTransformation() {
  int range = std::rand() % 100; // 0-99
  if (range < probabilities[0])
    return 0; // 1%
  if (range < probabilities[0] + probabilities[1])
    return 1; // 7%
  if (range < probabilities[0] + probabilities[1] + probabilities[2])
    return 2; // 7%
  return 3;   // 85%
}

// Applies the transformation to x and y
void applyTransformation(double &x, double &y, const double *transformation) {
  double xNew =
      x * transformation[0] + y * transformation[1] + transformation[2];
  double yNew =
      x * transformation[3] + y * transformation[4] + transformation[5];
  x = xNew;
  y = yNew;
}

// Sets the pixel in the image array
void setPixel(double x, double y, unsigned char *image) {
  int pixelX = (int)(width / 2 * (1 + x / xMax));
  int pixelY = (int)((height - 1) * (1 - y / yMax));

  int byteIndex = (pixelY * width + pixelX) / 8;
  int bitOffset = (pixelY * width + pixelX) % 8;
  image[byteIndex] |= (1 << bitOffset);
}

// Performs the iterations to generate the fern
void performIterations(int iterations, unsigned char *image) {

  // Start out at (0,0)
  double x = 0.0, y = 0.0;

  for (int i = 0; i < iterations; i++) {
    int transformIndex = selectTransformation();
    applyTransformation(x, y, transformations[transformIndex]);
    setPixel(x, y, image);
  }
}

// Gets the value of a pixel in the image array
bool getPixel(int row, int col, unsigned char *image) {

  // Calculate the byte and bit offset for the pixel
  int byteIndex = (row * width + col) / 8;
  int bitOffset = (row * width + col) % 8;

  // Check if the corresponding bit is set
  return (image[byteIndex] & (1 << bitOffset)) != 0;
}

// Draws the Barnsley Fern from the image array.
void drawImage(unsigned char *image) {
  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      if (getPixel(row, col, image)) {
        std::cout << "#";
      } else {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }
}

// Asks the user for the number of iterations, and calls helper methods
int main() {
  std::cout << "Enter number of iterations to run the IFS\n";

  int iterations;
  std::cin >> iterations;

  if (iterations <= 0) {
    std::cout << "Program Exiting: You entered a negative number: "
              << iterations << "\n";
    return 0;
  }

  unsigned char image[height * width / 8] = {};

  performIterations(iterations, image);
  drawImage(image);

  return 0;
}
