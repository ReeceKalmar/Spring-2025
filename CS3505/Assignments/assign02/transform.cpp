#include "transform.h"
#include "point.h"

Transform::Transform(double a, double b, double c, double d, double e, double f)
    : a(a), b(b), c(c), d(d), e(e), f(f) {}

Transform::~Transform() {}

void Transform::getParameters(double* parameters){
	parameters[0] = a;
	parameters[1] = b;
	parameters[2] = c;
	parameters[3] = d;
	parameters[4] = e;
	parameters[5] = f;
}

Point Transform::operator*(Point pt){
	const double x = pt.getX();
	const double y = pt.getY();

	const double xNew = (a * x) + (b * y) + c;
	const double yNew = (d * x) + (e * y) + f;

	return Point(xNew, yNew);
}

Point& operator*=(Point& pt, Transform tr) {
    double newX = tr.a * pt.x + tr.b * pt.y + tr.c;
    double newY = tr.d * pt.x + tr.e * pt.y + tr.f;

    pt.x = newX;
    pt.y = newY;

    return pt;
}

std::ostream& operator<<(std::ostream& output, Transform tr) {
    output << "[" << tr.a << ", " << tr.b << ", " << tr.c << ", " << tr.d << ", " << tr.e << ", " << tr.f << "]";
    return output;
}
