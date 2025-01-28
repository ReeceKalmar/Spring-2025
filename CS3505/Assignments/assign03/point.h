#pragma once

/*
Point class for CS 3505 assignment 2.
A Point holds x and y values.

By Eric Heisler and Reece Kalmar
01/29/2025
*/
#include <iostream>

class Transform;

// Represents a simple 2d point (0, 0) in Euclidean Space.
class Point {
private:
  // The X,Y coordinates (X, Y).
  double x, y;

public:
  // This is the default constructor takes initial values for x and y
  // or defaults to x = 0, y = 0.
  Point(double initX = 0, double initY = 0);

  // The destructor does nothing because we didn't allocate any new memory
  ~Point();

  // Getter for the x value
  double getX();

  // Getter for the y value
  double getY();

  // * Operator overload that scales the 2d point vector by a scalar factor.
  Point operator*(double scaleFactor);

  // OSStream insertion operator (<<) overload the 2d point.
  friend std::ostream &operator<<(std::ostream &output, Point pt);

  // *= Overload that modifies the original 2d Point vector and transforms it
  // using the six transform coefficients.
  friend Point &operator*=(Point &pt, Transform tr);
};
