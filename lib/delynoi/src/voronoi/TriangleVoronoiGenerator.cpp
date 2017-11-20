#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <delynoi/voronoi/DelaunayToVoronoi.h>


TriangleVoronoiGenerator::TriangleVoronoiGenerator(std::vector<Point> &point_list, Region region) {
    TriangleDelaunayGenerator delaunayGenerator(region, point_list);
    DelaunayInfo delaunay = delaunayGenerator.getConformingDelaunay();

    this->voronoi = DelaunayToVoronoi(delaunay).getMesh();
}

Mesh<Polygon> TriangleVoronoiGenerator::getMesh() {
    return this->voronoi;
}

