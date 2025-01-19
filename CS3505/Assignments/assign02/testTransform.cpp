#include <iostream>
#include "point.h"
#include "transform.h"

int main () {
	Point pt(1.0, 0.0);
	Transform tr(1.0113, -0.1788, 0.0, 0.1788, 1.0113, 0.0);

	for (int i = 0; i < 200; i++){
		pt *= tr;
		std::cout << pt << "\n";
	}

	return 0;
}
