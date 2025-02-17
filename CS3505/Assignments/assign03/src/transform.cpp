/*
Transform class for CS 3505 assignment 2.
A transform holds 6 double values.

By Reece Kalmar
01/29/2025
*/

#include "transform.h"
#include "point.h"

Transform::Transform(double a, double b, double c, double d, double e, double f)
    : a(a), b(b), c(c), d(d), e(e), f(f) {}

Transform::Transform(const double coefficients[6])
    : a(coefficients[0]), b(coefficients[1]), c(coefficients[2]),
      d(coefficients[3]), e(coefficients[4]), f(coefficients[5]) {}

Transform::~Transform() {};

void Transform::getParameters(double array[6]) {
  array[0] = a;
  array[1] = b;
  array[2] = c;
  array[3] = d;
  array[4] = e;
  array[5] = f;
}

Point Transform::operator*(Point pt) {
  double oldX = pt.getX();
  double oldY = pt.getY();
  double newX = (a * oldX) + (b * oldY) + c;
  double newY = (d * oldX) + (e * oldY) + f;
  return Point(newX, newY);
}

Point &operator*=(Point &pt, Transform tr) {
  double x = pt.x;
  double y = pt.y;
  pt.x = (x * tr.a) + (y * tr.b) + tr.c;
  pt.y = (x * tr.d) + (y * tr.e) + tr.f;

  return pt;
}

std::ostream &operator<<(std::ostream &output, Transform tr) {
  output << "[" << tr.a << ", ";
  output << tr.b << ", ";
  output << tr.c << ", ";
  output << tr.d << ", ";
  output << tr.e << ", ";
  output << tr.f << "]";
  return output;
}
