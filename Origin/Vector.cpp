#include "Vector.h"
#include "Point.h"

// Construtores
Vector::Vector() : Point(), _length() {}

Vector::Vector(const Point& point1, const Point& point2)
    :Point(point2.getX() - point1.getX(), point2.getY() - point1.getY()), _length() {
    calculate_Length();  // Calcula o comprimento do vetor resultante
}

Vector::Vector(const Point& point) : Point(point), _length() {
    calculate_Length();  // Calcula o comprimento
}



dividing Vector::horizontal_angle()
{
    return dividing();
}

bool Vector::is_Null()
{
    if(_length.get_numerator() == 0) {
        return true;
    }
    return false;
}

void Vector::calculate_Length()
{
    float a, b, p, q;
    a = (this->getX()).get_numerator();
    b = (this->getX()).get_denominator();
    p = (this->getY()).get_numerator();
    q = (this->getY()).get_denominator();
    square_length.set_numerator(a * a * q * q + p * p * b * b);
    square_length.set_denominator(b * b * q * q);

    _length = sqrt(square_length.calculate());
}

dividing Vector::getLength() const {
    return _length;
}

dividing Vector::get_square_Length() const {
    return square_length;
}

// Calcula o produto escalar com outro vetor
dividing Vector::dotProduct(const Vector& other) const {
    dividing a = (getX().get_numerator() * other.getX().get_numerator(), getX().get_denominator() * other.getX().get_denominator());
    dividing b = (getY().get_numerator() * other.getY().get_numerator(), getY().get_denominator() * other.getY().get_denominator());
    return (a + b);
}

// Retorna o vetor unitário (vetor normalizado)
Vector Vector::unitVector() const {
    if (_length.get_numerator() == 0) {
        std::cerr << "Vetor não pode ser normalizado." << std::endl;
        return Vector();  // Retorna um vetor padrão se o comprimento for 0
    }
    Point unitPoint(getX() / _length, getY() / _length); // Divide cada componente pelo comprimento do vetor
    return Vector(unitPoint);  // Retorna o vetor unitário
}
