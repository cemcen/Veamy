#ifndef MESHER_TRIANGLEMESHGENERATOR_H
#define MESHER_TRIANGLEMESHGENERATOR_H

#include "MeshGenerator.h"
#include <vector>
#include <mesher/voronoi/lib/triangle.h>
#include <unordered_map>
#include <mesher/models/neighbourhood/EdgeData.h>
#include <mesher/voronoi/structures/PointData.h>
#include <utilities/UniqueList.h>
#include <mesher/models/Region.h>
#include <mesher/voronoi/structures/mapdata.h>
#include <mesher/models/Triangulation.h>
#include <mesher/models/neighbourhood/Neighbours.h>
#include <mesher/models/neighbourhood/SegmentMap.h>

class TriangleMeshGenerator : public MeshGenerator{
private:
    Region region;
    PolygonalMesh mesh;

    std::vector<Triangle> triangles;
    std::vector<Point> meshPoints;
    SegmentMap delaunayEdges;

    std::vector<PointData> points;
    UniqueList<int> realPoints;
    std::vector<EdgeData> edges;
    std::unordered_map<Key, int, KeyHasher> edgeMap;

    UniqueList<Point> voronoiPoints;
    SegmentMap voronoiEdges;
    UniqueList<Polygon> voronoiCells;

    Point getCircumcenter(int triangle, int edge, std::vector<Point>& points);
    void callTriangle(std::vector<Point> &point_list, std::vector<PointSegment> restrictedSegments,
                          char switches[]);
    PolygonalMesh delaunayToVoronoi();
    void writeInputInFile(UniqueList<Point> &point_list, Region region, std::vector<int> regionIndex);
public:
    TriangleMeshGenerator(std::vector<Point>& point_list, Region region);
    TriangleMeshGenerator(std::vector<Point>& point_list, Region region, std::vector<PointSegment> restrictedSegments);
    ~TriangleMeshGenerator();
    PolygonalMesh getMesh();
    Triangulation getDelaunayTriangulation();
};

#endif
