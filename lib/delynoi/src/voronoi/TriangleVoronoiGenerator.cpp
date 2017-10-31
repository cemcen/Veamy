#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <delynoi/voronoi/DelaunayToVoronoi.h>


TriangleVoronoiGenerator::TriangleVoronoiGenerator(std::vector<Point> &point_list, Region region) {
    TriangleDelaunayGenerator delaunayGenerator(region, point_list);
    DelaunayInfo delaunay = delaunayGenerator.getConformingDelaunay();

    this->delaunay = delaunayGenerator.getConformingDelaunayTriangulation();
    this->voronoi = DelaunayToVoronoi(delaunay).getMesh();
}

Mesh<Polygon> TriangleVoronoiGenerator::getMesh() {
    return this->voronoi;
}

Mesh<Triangle> TriangleVoronoiGenerator::getConstrainedDelaunayTriangulation() {
    return this->delaunay;
}
