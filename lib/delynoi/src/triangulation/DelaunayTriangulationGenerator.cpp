#include <delynoi/triangulation/DelaunayTriangulationGenerator.h>

std::vector<Triangle> DelaunayTriangulationGenerator::triangulate(Polygon p, std::vector<Point> points) {
    Region r (p, points);

    TriangleDelaunayGenerator generator(r, points);
    Mesh<Triangle> triangulation = generator.getConstrainedDelaunayTriangulation();

    return triangulation.getPolygons();
}
