#ifndef DELYNOI_REGION_H
#define DELYNOI_REGION_H

#include <vector>
#include <delynoi/models/basic/Segment.h>
#include <delynoi/models/hole/Hole.h>
#include <delynoi/models/polygon/Polygon.h>
#include <algorithm>
#include <delynoi/utilities/xpolyutilities.h>
#include <delynoi/models/generator/PointGenerator.h>
#include <climits>
#include <delynoi/models/hole/PolygonalHole.h>
#include <delynoi/models/hole/clipper/lib/clipper.hpp>
#include <delynoi/models/hole/clipper/ClipperWrapper.h>
#include <delynoi/config/DelynoiConfig.h>
#include <utilities/utilities.h>

class Region: public Polygon {
private:
    std::vector<Hole> holes;
    std::vector<Point> p;
    std::vector<Point> seedPoints;

    void clean();
public:
    Region(std::vector<Point>& points);
    Region();
    Region(const Polygon& other, std::vector<Point>& points);
    Region(const Region& other);
    ~Region();

    void mutate(std::vector<Point>& points);
    std::vector<Point> getSeedPoints();
    std::vector<Point> getRegionPoints();
    std::vector<Hole>& getHoles();
    void addHole(Hole h);
    void cleanInternalHoles();
    void generateSeedPoints(PointGenerator p, int nX, int nY);
    void addSeedPoints(std::vector<Point> seeds);
    void addSeedsFromFile(std::string fileName);
    BoundingBox getBox();
    void getSegments(std::vector<IndexSegment>& s);
    bool containsPoint(Point p);
    bool inEdges(Point p);
    void cleanSeedPoints();
    void printInFile(std::string fileName);
};

#endif
