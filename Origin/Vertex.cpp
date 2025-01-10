#include "Vertex.h"

// Construtores
Vertex::Vertex(dividing x, dividing y) : Point(x, y),
tangentVectorX(0, 1), tangentVectorY(0, 1), angleWithX(0, 1),
edgeVectorX(0, 1), edgeVectorY(0, 1),
sinAngleWithEdge(0, 1), cosAngleWithEdge(1, 1),
rotationalAngle(0, 1), osculatingCurvature(0, 1),
position(0) {}

Vertex::Vertex(const std::string& color, dividing x, dividing y)
    : Point(color, x, y),
    tangentVectorX(0, 1), tangentVectorY(0, 1), angleWithX(0, 1),
    edgeVectorX(0, 1), edgeVectorY(0, 1),
    sinAngleWithEdge(0, 1), cosAngleWithEdge(1, 1),
    rotationalAngle(0, 1), osculatingCurvature(0, 1),
    position(0) {}

Vertex::Vertex(const Point& point)
    : Point(point.getColor(), point.getX(), point.getY()), // Inicializa a classe base com os valores do Point
    tangentVectorX(0, 1), tangentVectorY(0, 1), angleWithX(0, 1),
    edgeVectorX(0, 1), edgeVectorY(0, 1),
    sinAngleWithEdge(0, 1), cosAngleWithEdge(1, 1),
    rotationalAngle(0, 1), osculatingCurvature(0, 1),
    position(0) {}

// Métodos
void Vertex::setTangentVector(const dividing& tx, const dividing& ty) {
    tangentVectorX = tx;
    tangentVectorY = ty;
}

void Vertex::setEdgeVector(const dividing& ex, const dividing& ey) {
    edgeVectorX = ex;
    edgeVectorY = ey;
}

void Vertex::setRotationalAngle(dividing angle) {
    rotationalAngle = angle;
}

void Vertex::setOsculatingCurvature(dividing curvature) {
    osculatingCurvature = curvature;
}

void Vertex::setPreviousVertex(Vertex* prev) {
    if (prev) {
        dividing dx = getX() - prev->getX();
        dividing dy = getY() - prev->getY();

        setEdgeVector(dx, dy);
        dividing magnitude = dx * dx + dy * dy; // Evita conversão para double

        // Define o seno e o cosseno do ângulo com a aresta
        if (magnitude != dividing(0, 1)) {
            sinAngleWithEdge = dy / magnitude;
            cosAngleWithEdge = dx / magnitude;
        }
        else {
            sinAngleWithEdge = dividing(0, 1);
            cosAngleWithEdge = dividing(1, 1);
        }
    }
}

double Vertex::getAngleWithX() const {
    // Calcula o ângulo com o eixo X diretamente em radianos
    return atan2(tangentVectorY.calculate(), tangentVectorX.calculate());
}

double Vertex::getSinAngleWithEdge() const {
    return sinAngleWithEdge.calculate();
}

double Vertex::getCosAngleWithEdge() const {
    return cosAngleWithEdge.calculate();
}

double Vertex::getOsculatingCurvature() const {
    return osculatingCurvature.calculate();
}

void updateVertexPosition(Vertex* vertex, dividing newX, dividing newY) {
    if (vertex) {
        vertex->setX(newX);
        vertex->setY(newY);

        //std::cout << "Vertex updated to new position: ("
        //    << newX.calculate() << ", " << newY.calculate() << ")\n";
    }
    else {
        std::cout << "No vertex selected.\n";
    }
}

