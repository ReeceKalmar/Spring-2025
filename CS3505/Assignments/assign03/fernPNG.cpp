/*
Main program that creates a Barnsley Fern and saves it as a png file.

By Reece Kalmar
01/29/2025
*/

#include "pngWriter.h"
#include "point.h"
#include "transform.h"
#include <iostream>
#include <vector>

// Define Barnsley fern transformations
const std::vector<Transform> transforms = {
    Transform(0.0, 0.0, 0.0, 0.0, 0.16, 0.0),
    Transform(0.85, 0.04, 0.0, -0.04, 0.85, 1.6),
    Transform(0.2, -0.26, 0.0, 0.23, 0.22, 1.6),
    Transform(-0.15, 0.28, 0.0, 0.26, 0.24, 0.44)};

// Corresponding probabilities of (1%, 85%, 7%, 7%)
const std::vector<int> probabilities = {1, 86, 93, 100};

int main(int argc, char *argv[]) {
  if (argc != 5) {
    std::cerr
        << "Usage: ./fernPNG <output_file> <width> <height> <iterations>\n";
    return 1;
  }

  // Parse command-line arguments
  const char *outputFile = argv[1];
  unsigned int width = std::stoi(argv[2]);
  unsigned int height = std::stoi(argv[3]);

  if (width <= 0 || height <= 0) {
    std::cerr << "Invalide height x width: " << height << "x" << width << "\n";
    return 1;
  }

  unsigned int iterations = std::stoi(argv[4]);

  // Initialize PNGWriter and starting point
  PNGWriter png(height, width);
  Point pt;

  // Iteratively apply transformations and set pixels
  for (unsigned int i = 0; i < iterations; i++) {
    // Simpler RNG for selecting transformations
    int randomValue = rand() % 100 + 1;
    int choice = 0;
    for (size_t j = 0; j < probabilities.size(); j++) {
      if (randomValue <= probabilities[j]) {
        choice = j;
        break;
      }
    }

    pt *= transforms[choice];

    // Map point to image coordinates
    int x = static_cast<int>((pt.getX() + 2.5) / 5.0 * width);
    int y = static_cast<int>((10 - pt.getY()) / 10.0 * height);

    // Set pixel if within bounds
    if (x >= 0 && x < static_cast<int>(width) && y >= 0 &&
        y < static_cast<int>(height)) {
      png.setPixel(x, y, 0, 255, 0, 255);
    }
  }

  // Save the PNG image
  png.saveToFile(const_cast<char *>(outputFile));

  std::cout << "Barnsley fern image saved to " << outputFile << "\n";
  return 0;
}
