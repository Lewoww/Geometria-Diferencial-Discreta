#ifndef POINT_H
#define POINT_H

#include <string>
#include <iostream>
#include "dividing.h"  // Inclua o cabe�alho da classe dividing

class Point {
private:
    std::string color;
    //vetor unit�rio t(tangente)
    //angulo com o x, horizontal
    //vetor de aresta
    //sen e cos do angulo em rela��o a aresta
    //cada ponto pr�ximo DEVE ser diferente do anterior
    //rotational angle
    //curvatura osculadora 2
    dividing x;
    dividing y;
public:
    // Construtores
    Point(dividing x = dividing(0.0f, 1), dividing y = dividing(0.0f, 1));
    Point(const std::string& color, dividing x, dividing y);

    // M�todos auxiliares
    std::string getColor() const;
    void setColor(const std::string& color);
    dividing getX() const;
    void setX(const dividing& x);   // Corrigido para aceitar o tipo dividing
    dividing getY() const;
    void setY(const dividing& y);   // Corrigido para aceitar o tipo dividing
    void printPoint() const;
    //m�todo distancia

    bool isEqual(const Point& a, const Point& b) const;  // Alterado para passar por refer�ncia
};

#endif
