/*
Point class for CS 3505 assignment 2.
A Point holds x and y values.

By Eric Heisler and Reece Kalmar
01/17/2025
*/
#include "point.h"
#include "transform.h"
#include <iostream>

// Implement the methods prototyped in point.h
// You can include comments here if desired, 
// but they are already documented in point.h

Point::Point(): x(0.0), y(0.0) {}

Point::Point(double x, double y) : x(x), y(y) {}

Point::~Point() {}

double Point::getX() {
    return x;
}

double Point::getY() {
    return y;
}

// Operators
Point Point::operator*(double scaleFactor) {
	return Point(x*scaleFactor, y*scaleFactor);
}

Point& operator*=(Point& pt, Transform tr) {
    double newX = tr.a * pt.x + tr.b * pt.y + tr.c;
    double newY = tr.d * pt.x + tr.e * pt.y + tr.f;

    pt.x = newX;
    pt.y = newY;

    return pt;
}
// This doesn't start with Point:: so it is not in the scope of the class.
// However, it is a friend function, so it can access Point's variables.
std::ostream& operator<<(std::ostream& output, Point pt) {
    output << pt.x << ", " << pt.y;
    return output;
}
