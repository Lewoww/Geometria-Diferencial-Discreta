#include "Point.h"
#include "dividing.h"

// Construtores
Point::Point(dividing x, dividing y) : color(""), x(x), y(y) {
    // Inicializa com valores padrão, se necessário
}

Point::Point(const std::string& color, dividing x, dividing y) : color(color), x(x), y(y) {
    // Inicializa com cor e valores de x e y
}

// Métodos auxiliares
std::string Point::getColor() const {
    return color;
}

void Point::setColor(const std::string& color) {
    this->color = color;
}

dividing Point::getX() const {
    return x;
}

void Point::setX(const dividing& x) {
    this->x = x;
}

dividing Point::getY() const {
    return y;
}

void Point::setY(const dividing& y) {
    this->y = y;
}

// Imprime os valores calculados de X e Y
void Point::printPoint() const {
    std::cout << "Color: " << color << "\n"
        << "X: " << x.calculate() << "\n"  // Calcula o valor de X
        << "Y: " << y.calculate() << std::endl;  // Calcula o valor de Y
}

// Verifica se dois pontos são iguais
bool Point::isEqual(const Point& a, const Point& b) const {
    return (a.getX().calculate() == b.getX().calculate()) &&
        (a.getY().calculate() == b.getY().calculate());
}
