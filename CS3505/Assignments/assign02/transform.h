#ifndef TRANSFORM_H
#define TRANSFORM_H

/*
Transform class for CS 3505 assignment 2.
A transform holds 6 values to transform a 2d Point Vector.

By Reece Kalmar
01/19/2025
*/

#include <ostream>

class Point;

// Represents 6 coefficients thats used to transform a 2d Vector Point.
class Transform {
private:
  // Represents the 6 coefficients that will be used as the transform.
  double a, b, c, d, e, f;

public:
  // Defailt Constructor that initializes the six coefficients to 0.
  Transform();

  // Constructor that takes and sets the 6 different coefficients.
  Transform(double a, double b, double c, double d, double e, double f);

  // Method that alters the parameter array (should have a size of 6), and sets
  // the values to that of the transform objects coefficients.
  void getParameters(double *array);

  // * Overload that creates a new 2d vector point with the transformation from
  // the transform coefficients.
  Point operator*(Point pt);

  // *= Overload that modifies the original 2d Point vector and transforms it
  // using the six transform coefficients.
  friend Point &operator*=(Point &pt, Transform tr);

  // OSStream insertion overload for a 6 coefficients of the transform object.
  friend std::ostream &operator<<(std::ostream &output, Transform tr);
};

#endif
