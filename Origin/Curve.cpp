#include "Curve.h"

// Construtor
Curve::Curve() : scale1(1.0f), scale2(1.0f) {}

// Retorna as arestas da curva
const std::vector<Edge>& Curve::getEdges() const {
    return edges;
}

// Calcula a curvatura (a lógica deve ser implementada futuramente)
float Curve::calculateCurvature(int index) {
    if (index < 0 || index >= edges.size()) {
        return 0.0f; // Retorna 0 se o índice for inválido
    }
    // Exemplo: a lógica pode ser baseada na diferença de inclinações entre arestas adjacentes
    return 0.0f;
}

// Adiciona uma aresta à curva
void Curve::addEdge(const Edge& edge) {
    edges.push_back(edge);
}

//remove a aresta no índice desejado
void Curve::removeEdge(int index) {
    if (index >= 0 && index < edges.size()) {
        edges.erase(edges.begin() + index);
    }
    else {
        std::cout << "Índice inválido!" << std::endl;
    }
}


// Define a escala da curva
void Curve::setScale(float x, float y) {
    scale1 = x;
    scale2 = y;
}

// Desenha os vértices da curva como bolinhas
void Curve::drawVertices(bool isDragging, int index) const {
    glPointSize(7.0f); // Define o tamanho dos pontos
    glColor3f(1.0f, 0.0f, 0.0f); // Vermelho para os vértice
    
    glBegin(GL_POINTS);
        for (const Edge& edge : edges) {
        if (isDragging) {
            glColor3f(0.0f, 0.0f, 1.0f);
        }
        glVertex2f(edge.getP1().getX().calculate(), edge.getP1().getY().calculate());
        glVertex2f(edge.getP2().getX().calculate(), edge.getP2().getY().calculate());
    }
    glEnd();
}

void Curve::removeEdge(size_t index) {
    if (index < edges.size()) {
        edges.erase(edges.begin() + index);
    }
}

void Curve::replaceEdge(size_t index, const Edge& newEdge) {
    if (index < edges.size()) {
        edges[index] = newEdge;
    }
}

// Desenha a curva (como linhas conectando os vértices)
void Curve::drawCurve() const {
    for (const auto& edge : edges) {
        edge.drawEdge(scale1, scale2);
    }

}

// Retorna o número de arestas na curva
size_t Curve::getNumEdges() const {
    return edges.size();
}

// Verifica se a curva está vazia
bool Curve::isEmpty() const {
    return edges.empty();
}

/*
int Curve::findSelectedPoint(const std::vector<Vertex>& vertices, float x, float y, float tolerance) {
    for (size_t i = 0; i < vertices.size(); ++i) {
        float dx = vertices[i].getX().toFloat() - x;
        float dy = vertices[i].getY().toFloat() - y;
        if (std::sqrt(dx * dx + dy * dy) <= tolerance) {
            return static_cast<int>(i);
        }
    }
    return -1;
}*/
