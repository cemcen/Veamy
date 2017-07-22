#ifndef MESHER_POLYGONALHOLE_H
#define MESHER_POLYGONALHOLE_H

#include <vector>
#include <mesher/models/polygon/Polygon.h>
#include <mesher/models/hole/Hole.h>

class PolygonalHole: public Hole, public Polygon{
public:
    PolygonalHole(std::vector<Point>& p);
};

#endif
