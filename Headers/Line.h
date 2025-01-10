#include "Vector.h"

class Line
{
private: 
	dividing a, b, c;
	Point basePoint;
	Vector direct_Vector;
	Vector normal_Vector;

public:
	//Construtores:
	Line(dividing a, dividing b, dividing c);
	Line(const Point& p1, const Point& p2);
	Line(const Point& p1, const Vector& v1);

	dividing getA() const;
	dividing getB() const;
	dividing getC() const;

	dividing get_Equation();
	void set_Equation(dividing a, dividing b, dividing c);
	Point get_Base_Point();
	Vector get_Direct_Vector();
	Vector get_Normal_Vector();
	
	void calculateDirectionVector(const Point& p1, const Point& p2);
	void calculateNormalVector();

};


