#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <delynoi/voronoi/DelaunayToVoronoi.h>


TriangleVoronoiGenerator::TriangleVoronoiGenerator(std::vector<Point> &point_list, Region region) {
    TriangleDelaunayGenerator delaunayGenerator(region, point_list);
    DelaunayInfo delaunay = delaunayGenerator.getDelaunay();

    this->delaunay = delaunayGenerator.getDelaunayTriangulation();
    this->voronoi = DelaunayToVoronoi(delaunay).getMesh();
}

Mesh<Polygon> TriangleVoronoiGenerator::getMesh() {
    return this->voronoi;
}

Mesh<Triangle> TriangleVoronoiGenerator::getDelaunayTriangulation() {
    return this->delaunay;
}
