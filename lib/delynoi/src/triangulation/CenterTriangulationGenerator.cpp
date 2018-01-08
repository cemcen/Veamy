#include <delynoi/triangulation/CenterTriangulationGenerator.h>

std::vector<Triangle> CenterTriangulationGenerator::triangulate(Polygon p, std::vector<Point>& points) {
    if(!p.isConvex(points)){
        throw std::invalid_argument("Can not use a center triangulation scheme on a non convex polygon");
    }

    std::vector<int> polyPoints = p.getPoints();
    int n = polyPoints.size();

    std::vector<Triangle> triangles;
    Point center =  p.getAverage(points);
    points.push_back(center);
    int centerIndex = points.size()-1;

    for (int i = 0; i < n; ++i) {
        std::vector<int> trianglePoints = {polyPoints[i], polyPoints[(i+1)%n], centerIndex};

        Triangle t (trianglePoints, points);
        triangles.push_back(t);
    }

    return triangles;
}
