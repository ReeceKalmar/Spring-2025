/*
Testing file for CS 3505 assignment 2.
creates a new Point and Transform object with set values and iterates 200 times, each iteration
using the overloaded *= operator on the newly created point object with the
created transform object.

By Reece Kalmar
01/19/2025
*/

#include "point.h"
#include "transform.h"
#include <iostream>

int main() {
  Point pt(1.0, 0);
  Transform tr(1.0113, -0.1788, 0.0, 0.1788, 1.0113, 0.0);

	for (int i = 0; i < 200; i++){
		pt *= tr;
		std::cout << pt << "\n";
	}

  return 0;
}
