#ifndef MESHER_REGION_H
#define MESHER_REGION_H

#include <vector>
#include <mesher/models/basic/Segment.h>
#include <mesher/models/hole/Hole.h>
#include <mesher/models/polygon/Polygon.h>
#include <algorithm>
#include <mesher/utilities/xpolyutilities.h>
#include <mesher/models/generator/PointGenerator.h>
#include <climits>
#include <mesher/models/hole/PolygonalHole.h>
#include <mesher/models/hole/clipper/lib/clipper.hpp>
#include <mesher/models/hole/clipper/ClipperWrapper.h>
#include <mesher/config/MesherConfig.h>

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
    BoundingBox getBox();
    void getSegments(std::vector<IndexSegment>& s);
    bool containsPoint(Point p);
    bool inEdges(Point p);
    void cleanSeedPoints();
    void printInFile(std::string fileName);
};

#endif
