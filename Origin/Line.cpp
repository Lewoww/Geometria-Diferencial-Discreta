#include "Line.h"

Line::Line(dividing a, dividing b, dividing c)
	: a(a), b(b), c(c), basePoint(Point()) {
	calculateNormalVector();
}

Line::Line(const Point& p1, const Point& p2)
{
}

Line::Line(const Point& p1, const Vector& v1)
{
}

dividing Line::getA() const{
	return a;
}

dividing Line::getB() const{
	return b;
}

dividing Line::getC() const{
	return c;
}

dividing Line::get_Equation()
{
	
	return dividing();
}

void Line::set_Equation(dividing a, dividing b, dividing c)
{
}

Point Line::get_Base_Point()
{
	return Point();
}

Vector Line::get_Direct_Vector()
{
	return Vector();
}

Vector Line::get_Normal_Vector()
{
	return Vector();
}

void Line::calculateDirectionVector(const Point& p1, const Point& p2) {
	direct_Vector = Vector(p1, p2);  // Vector from p1 to p2
}

// Calula o vetor normal com base em ax + by + c = 0
void Line::calculateNormalVector() {

	normal_Vector = Vector(Point(a, b));  // o vetor normal é (a, b)
}