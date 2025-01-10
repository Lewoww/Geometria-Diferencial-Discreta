#ifndef CURVE_H
#define CURVE_H

#include "Edge.h"
#include <vector>
#include <GLFW/glfw3.h>

class Curve {
private:
    std::vector<Edge> edges; // Corrigido nome para "edges" (mais intuitivo)
    float scale1; // Fator de escala no eixo X
    float scale2; // Fator de escala no eixo Y

public:
    // Construtor
    Curve();

    // Métodos auxiliares
    const std::vector<Edge>& getEdges() const;
    float calculateCurvature(int index);
    void addEdge(const Edge& edge);
    void removeEdge(int index);
    void setScale(float x, float y);
    void drawVertices(bool selected, int index) const; // Tornado método const
    void removeEdge(size_t index);
    void replaceEdge(size_t index, const Edge& newEdge);
    void drawCurve() const;
    size_t getNumEdges() const;
    bool isEmpty() const; // Nomenclatura mais convencional para is_empty
    //int findSelectedPoint(const std::vector<Vertex>& vertices, float x, float y, float tolerance);
};

#endif
