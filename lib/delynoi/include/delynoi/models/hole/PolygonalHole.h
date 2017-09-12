#ifndef DELYNOI_POLYGONALHOLE_H
#define DELYNOI_POLYGONALHOLE_H

#include <vector>
#include <delynoi/models/polygon/Polygon.h>
#include <delynoi/models/hole/Hole.h>

class PolygonalHole: public Hole, public Polygon{
public:
    PolygonalHole(std::vector<Point>& p);
};

#endif
