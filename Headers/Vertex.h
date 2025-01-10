#include "Point.h"
class Vertex : public Point
{
private:
    dividing tangentVectorX;
    dividing tangentVectorY;
    dividing angleWithX;  // Em radianos
    dividing edgeVectorX;
    dividing edgeVectorY;
    dividing sinAngleWithEdge;
    dividing cosAngleWithEdge;
    dividing rotationalAngle;  // Em radianos
    dividing osculatingCurvature;
    
    int position;
public:
    // Construtores
    Vertex(dividing x = dividing(0, 1), dividing y = dividing(0, 1));
    Vertex(const std::string& color, dividing x, dividing y);

    Vertex(const Point& point);

    // Métodos
    void setTangentVector(const dividing& tx, const dividing& ty);
    void setEdgeVector(const dividing& ex, const dividing& ey);
    void setRotationalAngle(dividing angle);
    void setOsculatingCurvature(dividing curvature);
    void setPreviousVertex(Vertex* prev);

    double getTangentVectorX()const;
    double getTangentVectorY()const;
    double getAngleWithX() const;
    double getSinAngleWithEdge() const;
    double getCosAngleWithEdge() const;
    double getRotationalAngle()const;
    double getOsculatingCurvature() const;

};

void updateVertexPosition(Vertex* vertex, dividing newX, dividing newY);