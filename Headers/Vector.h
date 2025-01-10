#ifndef VECTOR_H
#define VECTOR_H

#include "Point.h"
#include <string>
#include <iostream>
#include <cmath>

class Vector : public Point {
private:
    dividing _length;              // Comprimento do vetor, preciso mudar essa vari�vel para dividing
    dividing square_length;

    //dividing horizontal_angle;
    //boolean null_vector;
public:
    // Construtores
    Vector();                                            // Construtor padr�o
    Vector(const Point& point1, const Point& point2);    // Construtor com dois pontos
    Vector(const Point& point);                         // Construtor com um ponto

    // M�todos
    dividing horizontal_angle();
    bool is_Null();
    void calculate_Length();
    dividing getLength() const;
    dividing get_square_Length() const;
    dividing dotProduct(const Vector& other) const;         // Produto escalar
    Vector unitVector() const;                           // Retorna o vetor unit�rio
};

#endif
