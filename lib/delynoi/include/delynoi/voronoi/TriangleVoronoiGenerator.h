#ifndef DELYNOI_TRIANGLEMESHGENERATOR_H
#define DELYNOI_TRIANGLEMESHGENERATOR_H

#include <delynoi/voronoi/TriangleDelaunayGenerator.h>
#include <delynoi/voronoi/structures/DelaunayInfo.h>
#include <delynoi/models/Mesh.h>

/*
 * Class in charge of creating the Voronoi diagram from the Delaunay triangulation
 */
class TriangleVoronoiGenerator {
private:
    /*
     * Voronoi diagram in the format of a Delynoi mesh
     */
    Mesh<Polygon> voronoi;
    Mesh<Polygon> delaunay;
public:
    /*
     * Constructor. Using the point list (seed points) and a domain it computes the Voronoi diagram and sets it in the
     * class member
     */
    TriangleVoronoiGenerator(std::vector<Point>& point_list, Region region);

    /*
     * @return voronoi diagram
     */
    Mesh<Polygon> getMesh();

    /*
     * @return delaunay diagram
     */
    Mesh<Polygon> getTriangulation();
};

#endif
