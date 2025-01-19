#ifndef TRANSFORM_H
#define TRANSFORM_H
/*
Transform class for CS 3505 assignment 2.
An object that holds 6 double's to be used to transform a Point object.

By Reece Kalmar
01/17/2025
*/
#include <iostream> // for ostream

class Point;

class Transform {
private:
  double a, b, c, d, e, f;

public:
  // This constructor takes initial values for a, b, c, d, e and f.
  Transform(double a, double b, double c, double d, double e, double f);

  // The destructor does nothing because we didn't allocate any new memory
  ~Transform();

	// Sets the doubles of array using the Transform object's parameters
	void getParameters(double* parameters);

  // Operators
  Point operator*(Point pt);

	// Overload *=
	friend Point& operator*=(Point& pt, Transform tr);

  // Friend insertion operator to make printing easy
  friend std::ostream& operator<<(std::ostream& output, Transform tr);
};

#endif
