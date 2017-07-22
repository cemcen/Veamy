#ifndef THESIS_CLIPPERWRAPPER_H
#define THESIS_CLIPPERWRAPPER_H

#include <mesher/models/hole/clipper/lib/clipper.hpp>
#include <mesher/models/basic/Point.h>
#include <mesher/models/polygon/Polygon.h>

class ClipperWrapper {
private:
    static ClipperLib::IntPoint scalePoint(Point point, int maxScale);
public:
    static ClipperLib::Paths polyIntersection(std::vector<Point> parent, std::vector<Point> child, int maxScale);
};


#endif
