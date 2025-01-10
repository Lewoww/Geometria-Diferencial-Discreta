#ifndef VECTOR_H
#define VECTOR_H

#include "Point.h"
#include <string>
#include <iostream>
#include <cmath>

class Vector : public Point {
private:
    dividing _length;              // Comprimento do vetor, preciso mudar essa variável para dividing
    dividing square_length;

    //dividing horizontal_angle;
    //boolean null_vector;
public:
    // Construtores
    Vector();                                            // Construtor padrão
    Vector(const Point& point1, const Point& point2);    // Construtor com dois pontos
    Vector(const Point& point);                         // Construtor com um ponto

    // Métodos
    dividing horizontal_angle();
    bool is_Null();
    void calculate_Length();
    dividing getLength() const;
    dividing get_square_Length() const;
    dividing dotProduct(const Vector& other) const;         // Produto escalar
    Vector unitVector() const;                           // Retorna o vetor unitário
};

#endif
