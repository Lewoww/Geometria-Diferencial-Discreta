#include "Edge.h"
#include "dividing.h"
#include <math.h>


Edge::Edge(const std::string& color, const Point& p1, const Point& p2)
    : color(""), p1(p1), p2(p2) {
    length(p1, p2);
}

Edge::Edge(const Point p1, const Point p2) : color(""), p1(p1), p2(p2) {
    length(p1, p2);
}


Point Edge::getP1() const { 
    return p1; 
}

void Edge::setP1(const Point& p1) { this->p1 = p1; }

Point Edge::getP2() const { return p2; }

void Edge::setP2(const Point& p2) { this->p2 = p2; }


std::string Edge::getColor() const { return color; }

void Edge::setColor(const std::string& color) { this->color = color; }


void Edge::drawEdge(float s1, float s2) const {
    float x1 = (p1.getX() / s1).calculate();
    float y1 = (p1.getY() / s2).calculate();
    float x2 = (p2.getX() / s1).calculate();
    float y2 = (p2.getY() / s2).calculate();

    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);  // Cor verde
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}


void Edge::length(const Point& p1, const Point& p2)
{
    float x_diff = p1.getX().calculate() - p2.getX().calculate();
    float y_diff = p1.getY().calculate() - p2.getY().calculate();
    _length = sqrt((x_diff * x_diff) + (y_diff * y_diff));
}

float Edge::get_length() const
{
    return _length;
}
