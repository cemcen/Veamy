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
    std::vector<Point> seedPoints;

    std::vector<Triangle> triangles;
    std::vector<Point> meshPoints;
    SegmentMap* delaunayEdges;

    std::vector<PointData> points;
    UniqueList<int> realPoints;
    std::vector<EdgeData> edges;
    std::unordered_map<Key, int, KeyHasher> edgeMap;

    void callTriangle(std::vector<Point> &point_list, char switches[]);
    void callTriangle(std::vector<Point> &point_list, char switches[], std::vector<PointSegment> restrictedSegments);
    Mesh<Triangle> initializeMesh();
public:
    TriangleDelaunayGenerator(Region region, std::vector<Point> points);
    Mesh<Triangle> getConformingDelaunayTriangulation();
    Mesh<Triangle> getConstrainedDelaunayTriangulation();
    Mesh<Triangle> getConstrainedDelaunayTriangulation(std::vector<PointSegment> restrictedSegments);
    DelaunayInfo getConformingDelaunay();

    void writeTriangleInputFile(UniqueList<Point> &point_list, Region region, std::vector<int> regionIndex);
};

#endif