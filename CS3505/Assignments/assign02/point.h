#ifndef POINT_H
#define POINT_H
/*
Point class for CS 3505 assignment 2.
A Point holds x and y values.

By Eric Heisler and Reece Kalmar
01/17/2025
*/
#include <iostream> // for ostream

class Transform;

class Point {
private:
  double x, y;

public:
  // default constructor initializes to (0, 0)
  Point();

  // This constructor takes initial values for x and y
  Point(double initX, double initY);

  // The destructor does nothing because we didn't allocate any new memory
  ~Point();

  // Getter for the x value
  double getX();

  // Getter for the y value
  double getY();

  // Operators
  Point operator*(double scaleFactor);

	// Overload *=
	friend Point& operator*=(Point& pt, Transform tr);

  // Friend insertion operator to make printing easy
  friend std::ostream &operator<<(std::ostream &output, Point pt);

  // TODO: You will add one more friend operator for *=
};

#endif // include guard for POINT_H
