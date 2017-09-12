#ifndef DELYNOI_TRIANGLEDELAUNAY_H
#define DELYNOI_TRIANGLEDELAUNAY_H

#include <delynoi/models/Region.h>
#include <delynoi/voronoi/structures/PointData.h>
#include <delynoi/voronoi/structures/DelaunayInfo.h>
#include <delynoi/models/Mesh.h>

extern "C"{
#include <delynoi/voronoi/lib/triangle.h>
};

class TriangleDelaunayGenerator {
private:
    Region region;
    std::vector<Triangle> triangles;
    std::vector<Point> meshPoints;
    SegmentMap delaunayEdges;

    std::vector<PointData> points;
    UniqueList<int> realPoints;
    std::vector<EdgeData> edges;
    std::unordered_map<Key, int, KeyHasher> edgeMap;

    void callTriangle(std::vector<Point> &point_list, char switches[]);
public:
    TriangleDelaunayGenerator(Region region, std::vector<Point> points);
    Mesh<Triangle> getDelaunayTriangulation();
    DelaunayInfo getDelaunay();

    void writeTriangleInputFile(UniqueList<Point> &point_list, Region region, std::vector<int> regionIndex);
};

#endif