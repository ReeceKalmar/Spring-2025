/*
Point class for CS 3505 assignment 2.
A Point holds x and y values.

By Eric Heisler and Reece Kalmar
01/19/2025
*/
#include "point.h"
#include <iostream>

Point::Point() : x(0.0), y(0.0) {}

Point::Point(double x, double y) : x(x), y(y) {}

Point::~Point() {}

double Point::getX() { return x; }

double Point::getY() { return y; }

Point Point::operator*(double scaleFactor) {
  return Point(x * scaleFactor, y * scaleFactor);
}

std::ostream &operator<<(std::ostream &output, Point pt) {
  output << pt.x << ", " << pt.y;
  return output;
}
