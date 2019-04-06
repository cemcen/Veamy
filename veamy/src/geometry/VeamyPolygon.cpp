#include <veamy/geometry/VeamyPolygon.h>
#include <delynoi/triangulation/EarTriangulationGenerator.h>

VeamyPolygon::VeamyPolygon(Polygon p) : Polygon(p){}

std::vector<VeamyTriangle> VeamyPolygon::triangulate(std::vector<Point> &points) {
    std::vector<VeamyTriangle> veamyTriangles;
    std::vector<Triangle> triangles = EarTriangulationGenerator().triangulate(*this, points);

    for(Triangle t: triangles){
        veamyTriangles.push_back(VeamyTriangle(t));
    }

    return veamyTriangles;
}
