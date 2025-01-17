#include <iostream>
#include "point.h"
#include "transform.h"

int main () {
	Point pt(1.0, 0.0);
	Transform tr(1.0225, -0.1929, 0.0032, 0.1929, 0.9982, 0.0032);

	for (int i = 0; i < 200; i++){
		pt *= tr;
		std::cout << pt << "\n";
	}

	return 0;
}
