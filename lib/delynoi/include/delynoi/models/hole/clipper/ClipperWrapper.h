#ifndef DELYNOI_CLIPPERWRAPPER_H
#define DELYNOI_CLIPPERWRAPPER_H

#include <delynoi/models/hole/clipper/lib/clipper.hpp>
#include <delynoi/models/basic/Point.h>
#include <delynoi/models/polygon/Polygon.h>

class ClipperWrapper {
private:
    static ClipperLib::IntPoint scalePoint(Point point, int maxScale);
public:
    static ClipperLib::Paths polyIntersection(std::vector<Point> parent, std::vector<Point> child, int maxScale);
};


#endif
