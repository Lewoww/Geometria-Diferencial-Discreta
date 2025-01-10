#ifndef EDGE_H
#define EDGE_H

#include "Point.h"
#include <GLFW/glfw3.h>
#include <string>

class Edge {
private:
    Point p1;
    Point p2;
    float _length;
    std::string color;
    //curvatura 3 ponto médio da aresta


public:
    Edge(const std::string& color = "", const Point& p1 = Point(), const Point& p2 = Point()); //lenght precisa ser calculado, não passado
    Edge(Point p1, Point p2);


    // Métodos auxiliares

    Point getP1() const;
    void setP1(const Point& p1);

    Point getP2() const;
    void setP2(const Point& p2);

    std::string getColor() const;
    void setColor(const std::string& color);

    void drawEdge(float s1, float s2) const;

    void length(const Point& p1, const Point& p2);
    float get_length() const;
};

#endif
