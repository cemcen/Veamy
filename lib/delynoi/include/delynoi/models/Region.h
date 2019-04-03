#ifndef DELYNOI_REGION_H
#define DELYNOI_REGION_H

#include <vector>
#include <delynoi/models/basic/Segment.h>
#include <delynoi/models/hole/Hole.h>
#include <delynoi/models/polygon/Polygon.h>
#include <algorithm>
#include <delynoi/utilities/delynoi_utilities.h>
#include <delynoi/models/generator/PointGenerator.h>
#include <climits>
#include <delynoi/models/hole/PolygonalHole.h>
#include <delynoi/models/hole/clipper/lib/clipper.hpp>
#include <delynoi/models/hole/clipper/ClipperWrapper.h>
#include <delynoi/config/DelynoiConfig.h>

/*
 * Models a region inside which a mesh can be generated. Region inherits from Polygon (as it is a polygon after all),
 * but keeps its points directly instead of their indexes, and can contain holes and seed points (used for mesh generation)
 */
class Region: public Polygon {
private:
    /*
     * List of holes contained in the region
     */
    std::vector<Hole> holes;

    /*
     * List of points defining the region
     */
    std::vector<Point> p;

    /*
     * List of seed points (for mesh generation) inside the region
     */
    std::vector<Point> seedPoints;

    /* Erase from the seed point list all seed points that are not inside the region (as they are generated in the
     * bounding box of the region)
     */
    void clean();
public:
    /*
     * Constructor.
     */
    Region(std::vector<Point>& points);

    /*
     * Default constructor
     */
    Region();

    /*
     * Constructor. Creates a region from a polygon instance and the list of mesh points
     */
    Region(const Polygon& other, std::vector<Point>& points);

    /*
     * Copy constructor.
     */
    Region(const Region& other);

    /* Changes the points of the region (defining a new one), without changing the instance itself
     * @param points new points of the region
     */
    void mutate(std::vector<Point>& points);

    /*
     * @return list of seed points of the region
     */
    std::vector<Point> getSeedPoints();

    /*
     * @return list of points defining the region
     */
    std::vector<Point> getRegionPoints();

    /*
     * @return list of holes inside the region
     */
    std::vector<Hole>& getHoles();

    /* Adds and processes a hole, including in the hole list if completely contained in the region, or mutating the region
     * if intersecting
     * @param h hole to add
     */
    void addHole(Hole h);

    /*
     * Empties the list of holes of the region
     */
    void cleanInternalHoles();

    /* Creates seed points inside the bounding box of the region using the given PointGenerator instance. The number
     * of points is determined by the two integers (nX in the horizontal axis, nY in he vertical axis)
     * @param p PointGenerator instance to use
     * @param nX number of points to create in the horizontal axis
     * @param nY number of points to create in the vertical axis
     */
    void generateSeedPoints(PointGenerator p, int nX, int nY);

    /* Adds already seed points to the list
     * @param seeds list of points to add
     */
    void addSeedPoints(std::vector<Point>& seeds);

    /* Adds seed points reading them from a file
     * @param fileName name of the file from which the seed points will be read
     */
    void addSeedsFromFile(std::string fileName);

    /*
     * @return the axis oriented bounding box of the region
     */
    BoundingBox getBox();

    /* Sets the region segments in a vector
     * @param s vector where the segments will be assigned
     */
    void getSegments(std::vector<IndexSegment>& s);

    /* Checks if a given point is inside the region
     * @param p point to check
     * @return whether the point is inside the region or not
     */
    bool containsPoint(Point p);

    /* Checks if a given point is in the border of the region
     * @param p point to check
     * @return whether the point is in the boundary or not
     */
    bool inEdges(Point p);

    /*
     * Empties the seed point list
     */
    void cleanSeedPoints();

    /*
     * Prints the region in a file
     * @param fileName name of the file to print the region to
     */
    void printInFile(std::string fileName);
};

#endif
