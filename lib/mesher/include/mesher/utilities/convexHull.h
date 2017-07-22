#ifndef MESHER_CONVEXHULL_H
#define MESHER_CONVEXHULL_H

#include <mesher/models/basic/Point.h>

namespace convex {
    extern void convexHull(std::vector<Point> points, std::vector<Point>& u, std::vector<Point>& l);
    extern std::vector<std::pair<Point,Point> > rotatingCalipers(std::vector<Point> points);
}
#endif
