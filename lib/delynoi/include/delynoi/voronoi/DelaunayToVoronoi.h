#ifndef DELYNOI_DELAUNAYTOVORONOI_H
#define DELYNOI_DELAUNAYTOVORONOI_H

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/polygon/Triangle.h>
#include <delynoi/voronoi/structures/DelaunayInfo.h>
#include <delynoi/models/Mesh.h>

/*
 * Class in charge of using the Delaunay triangulation to compute the Voronoi diagram
 */
class DelaunayToVoronoi {
private:
    /*
     * Voronoi diagram in Mesh form
     */
    Mesh<Polygon> mesh;

    /* Gets the circumcenter of a triangle or edge
     * @param del delaunay triangulation
     * @param triangle index of the triangle which circumcenter will be computed
     * @param edge index of the edge from which we entered triangle
     * @return circumcenter
     */
    Point getCircumcenter(DelaunayInfo del, int triangle, int edge);
public:
    /*
     * Constructor
     */
    explicit DelaunayToVoronoi(DelaunayInfo del);
    /*
     * @return voronoi diagram in Mesh form
     */
    Mesh<Polygon> getMesh();
};

#endif