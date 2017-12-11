#ifndef DELYNOI_TRIANGLEDELAUNAY_H
#define DELYNOI_TRIANGLEDELAUNAY_H

#include <delynoi/models/Region.h>
#include <delynoi/voronoi/structures/PointData.h>
#include <delynoi/voronoi/structures/DelaunayInfo.h>
#include <delynoi/models/Mesh.h>

extern "C"{
#include <delynoi/voronoi/lib/triangle.h>
};

/*
 * Class in charge of computing the Delaunay triangulation using the seed points and domain given, using Triangle
 */
class TriangleDelaunayGenerator {
private:
    /*
     * Input parameters, seed points for the diagram and domain
     */
    Region region;
    std::vector<Point> seedPoints;

    /*
     * Output for the representation of the Delaunay triangulation as a Delynoi mesh
     */
    std::vector<Triangle> triangles;
    std::vector<Point> meshPoints;
    SegmentMap* delaunayEdges;

    /*
     * Information for the computation of the Voronoi diagram
     */
    std::vector<PointData> points;
    UniqueList<int> realPoints;
    std::vector<EdgeData> edges;
    std::unordered_map<Key, int, KeyHasher> edgeMap;
    bool empty = false;

    /* Calls the Triangle library, filling the class members with the result
     * @param point_list points which Delaunay triangulation must be computed
     * @param switches list of switches for Triangle (define a number of options)
     */
    void callTriangle(std::vector<Point> &point_list, char switches[]);

    /* Calls the Triangle library, filling the class members with the result
     * @param point_list points which Delaunay triangulation must be computed
     * @param switches list of switches for Triangle (define a number of options)
     * @param restrictedSegment list of segments inside the domain which must be included in the triangulation
     */
    void callTriangle(std::vector<Point> &point_list, char switches[], std::vector<PointSegment> restrictedSegments);

    /* Creates a Mesh (in Delynoi format) from the information of the Delaunay triangulation
     * @return Delaunay triangulation in Mesh form
     */
    Mesh<Triangle> initializeMesh();
public:
    /*
     * Constructor
     */
    TriangleDelaunayGenerator(const std::vector<Point>& points, Region region);

    /* Returns the conforming Delaunay triangulation (all triangles, even those in the boundary or next to restricted
     * segments, are Delaunay through the inclusion of additional points)
     * @return the conforming Delaunay triangulation
     */
    Mesh<Triangle> getConformingDelaunayTriangulation();

    /* Returns the constrained Delaunay triangulation (triangles next to constrained segments are not necessarily
     * delaunay)
     * @return the constrained Delaunay triangulation
     */
    Mesh<Triangle> getConstrainedDelaunayTriangulation();

    /* Returns the constrained Delaunay triangulation (triangles next to constrained segments are not necessarily
     * delaunay)
     * @return the constrained Delaunay triangulation
     */
    Mesh<Triangle> getConstrainedDelaunayTriangulation(std::vector<PointSegment> restrictedSegments);

    /* Returns the conforming Delaunay triangulation in the format that can be used to compute the Voronoi diagram
     * @return Delaunay triangulation in DelaunayInfo format
     */
    DelaunayInfo getConformingDelaunay();

    /* Writes the input information in a text file (so that we can call Triangle externally)
     * @param point_list seed points
     * @param region domain in which the triangulation must be computed
     * @param regionIndex indexes of the points (in point_list) definining the region
     */
    void writeTriangleInputFile(UniqueList<Point> &point_list, Region region, std::vector<int> regionIndex);
};

#endif