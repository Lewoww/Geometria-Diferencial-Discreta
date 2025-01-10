#include "Curve.h"
#include <cmath>
#include <GLFW/glfw3.h>
#include <iostream>
#include "dividing.h"
#include "Vertex.h"

using namespace std;

// Variáveis globais
float cameraX = 0.0f;
float cameraY = 0.0f;
std::vector<Vertex> vertices;
Curve currentCurve;
float zoomFactor = 1.0f;
bool isCurveClosed = false;
bool isFPressed = false;
bool isDragging = false;
Vertex* draggedVertex = nullptr;

void processInput(GLFWwindow* window) {
    const float moveSpeed = 0.01f;
    const float zoomSpeed = 0.005f;

    // Movimentação da câmera
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        cameraY += moveSpeed * zoomFactor;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        cameraY -= moveSpeed * zoomFactor;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        cameraX -= moveSpeed * zoomFactor;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        cameraX += moveSpeed * zoomFactor;
    }

    // Zoom in
    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
        zoomFactor *= (1.0f - zoomSpeed);
        if (zoomFactor < 0.1f) {
            zoomFactor = 0.1f;
        }
    }

    // Zoom out
    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
        zoomFactor *= (1.0f + zoomSpeed);
        if (zoomFactor > 10.0f) {
            zoomFactor = 10.0f;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !isFPressed) {
        if (isCurveClosed) {
            // Abrir a curva
            if (!currentCurve.getEdges().empty()) {
                currentCurve.removeEdge(currentCurve.getNumEdges() - 1);
            }
            isCurveClosed = false;
        }
        else {
            // Fechar a curva
            if (!vertices.empty() && currentCurve.getEdges().size() > 1) {
                Vertex& firstVertex = vertices.front();
                Vertex& lastVertex = vertices.back();

                Edge closingEdge("", lastVertex, firstVertex);
                currentCurve.addEdge(closingEdge);

                isCurveClosed = true;
            }
        }
        isFPressed = true;
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE) {
        isFPressed = false;
    }
}

int findSelectedPoint(const std::vector<Vertex>& curve, float mouseX, float mouseY, float tolerance) {
    for (size_t i = 0; i < curve.size(); ++i) {
        float pointX = curve[i].getX().calculate();
        float pointY = curve[i].getY().calculate();

        // Calcula a distância entre o ponto e o clique do mouse
        float distance = std::sqrt(std::pow(mouseX - pointX, 2) + std::pow(mouseY - pointY, 2));

        if (distance <= tolerance) {
            return i; // Retorna o índice do ponto selecionado
        }
    }
    return -1; // Nenhum ponto foi selecionado
}

static void displayVertexDetails(Vertex* vertex) {
    if (vertex) {
        std::cout << "Vertex Details:" << std::endl;
        std::cout << "Position: (" << vertex->getX().calculate() << ", " << vertex->getY().calculate() << ")" << std::endl;
        std::cout << "Angle with X-axis: " << vertex->getAngleWithX() << " radians" << std::endl;
        std::cout << "Osculating Curvature: " << vertex->getOsculatingCurvature() << std::endl;
        std::cout << "---------------------------------" << std::endl;
    }
}
void drawAxes(GLFWwindow* window) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    float xLimit = 16.0f * zoomFactor;
    float yLimit = xLimit / aspectRatio;

    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINES);
    glVertex2f(-xLimit, 0.0f);
    glVertex2f(xLimit, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0f, -yLimit);
    glVertex2f(0.0f, yLimit);
    glEnd();
}
// Função para redesenhar a curva e os vértices
void updateDrawing(GLFWwindow* window, int index) {
    glClear(GL_COLOR_BUFFER_BIT);  // Limpa a tela

    drawAxes(window);  // Desenha os eixos de coordenadas

    // Desenha a curva
    currentCurve.drawCurve();

    // Desenha os vértices
    currentCurve.drawVertices(isDragging, index);

    // Troca os buffers para que a cena atualizada seja visível
    glfwSwapBuffers(window);
}

static void mouseButtonClick(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        float x = ((xpos / width) * 2.0f - 1.0f) * zoomFactor + cameraX;
        float y = -((ypos / height) * 2.0f - 1.0f) * zoomFactor + cameraY;

        float selectionTolerance = 0.05f;

        // Encontrar o ponto selecionado (se existir)
        int selectedIndex = findSelectedPoint(vertices, x, y, selectionTolerance);

        if (selectedIndex != -1) {
            if (isDragging && draggedVertex == &vertices[selectedIndex]) {
                // Atualiza a posição do vértice arrastado
                updateVertexPosition(draggedVertex, x / 1, y / 1);

                // Atualiza a aresta anterior (se existir)
                if (selectedIndex > 0) { // Verifica se há uma aresta anterior
                    Edge newPrevEdge(vertices[selectedIndex - 1], vertices[selectedIndex]);
                    currentCurve.replaceEdge(selectedIndex - 1, newPrevEdge);
                }

                // Atualiza a aresta seguinte (se existir)
                if (selectedIndex < vertices.size() - 1) { // Verifica se há uma aresta seguinte
                    Edge newNextEdge(vertices[selectedIndex], vertices[selectedIndex + 1]);
                    currentCurve.replaceEdge(selectedIndex, newNextEdge);
                }

                // Redesenha a curva com as arestas atualizadas
                updateDrawing(window, selectedIndex);

                // Finaliza o arraste
                isDragging = false;
                draggedVertex = nullptr;
                std::cout << "Point updated and edges replaced\n\n";
            }

            else {
                // Selecionar novo ponto
                std::cout << "Selected point index: " << selectedIndex << "\n";
                displayVertexDetails(&vertices[selectedIndex]);
                isDragging = true;
                draggedVertex = &vertices[selectedIndex];
            }
        }
        else if (!isCurveClosed && !isDragging) {
            // Nenhum ponto selecionado e não está no modo de arrastar: cria um novo vértice
            Vertex newVertex(dividing(x, 1), dividing(y, 1));
            vertices.push_back(newVertex);

            if (!currentCurve.getEdges().empty()) {
                // Adiciona uma nova aresta conectando ao último vértice da curva
                Edge lastEdge = currentCurve.getEdges().back();
                Vertex lastVertex = lastEdge.getP2();

                Edge newEdge("green", lastVertex, newVertex);
                currentCurve.addEdge(newEdge);
            }
            else if (vertices.size() > 1) {
                // Caso especial para a primeira aresta
                Edge firstEdge("green", vertices[0], newVertex);
                currentCurve.addEdge(firstEdge);
            }
        }
    }
}

static void mouseMove(GLFWwindow* window, double xpos, double ypos) {
    if (isDragging && draggedVertex) {
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        // Convertendo as coordenadas do cursor para o sistema de coordenadas da tela
        float x = ((xpos / width) * 2.0f - 1.0f) * zoomFactor + cameraX;
        float y = -((ypos / height) * 2.0f - 1.0f) * zoomFactor + cameraY;

        // Atualiza a posição do vértice
        updateVertexPosition(draggedVertex, dividing(x, 1), dividing(y, 1));
    }
}

void initOpenGL() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "window", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouseButtonClick);
    glfwSetCursorPosCallback(window, mouseMove);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(
            (-1.0f * zoomFactor) + cameraX,
            (1.0f * zoomFactor) + cameraX,
            (-1.0f * zoomFactor) + cameraY,
            (1.0f * zoomFactor) + cameraY,
            -1.0f,
            1.0f
        );
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


        updateDrawing(window, NULL);  // Atualiza e redesenha a cena

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

int main() {
    initOpenGL();
    return 0;
}