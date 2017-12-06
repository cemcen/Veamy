#ifndef DELYNOI_DELAUNAYINFO_H
#define DELYNOI_DELAUNAYINFO_H

#include <delynoi/models/polygon/Triangle.h>
#include "PointData.h"

struct DelaunayInfo{
    std::vector<Triangle> triangles;
    std::vector<Point> meshPoints;
    SegmentMap* delaunayEdges;

    std::vector<PointData> points;
    UniqueList<int> realPoints;
    std::vector<EdgeData> edges;
    std::unordered_map<Key, int, KeyHasher> edgeMap;

    DelaunayInfo( std::vector<Triangle> t, std::vector<Point> p, SegmentMap* e, std::vector<PointData> pD,
                  UniqueList<int> rP, std::vector<EdgeData> eD, std::unordered_map<Key, int, KeyHasher> eM){
        triangles = t;
        meshPoints = p;
        delaunayEdges = e;
        points = pD;
        realPoints = rP;
        edges = eD;
        edgeMap = eM;
    }
};

#endif