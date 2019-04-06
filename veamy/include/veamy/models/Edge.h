#ifndef VEAMY_EDGE_H
#define VEAMY_EDGE_H

#include <delynoi/models/basic/Point.h>
#include <utilities/Pair.h>
#include <vector>
#include <veamy/models/dof/DOF.h>

/*
 * Class that models an edge (it is the same as a Segment, but with less operations)
 */
class Edge {
private:
    /*
     * Endpoints of the edge
     */
    int p1;
    int p2;
public:
    /*
     * Constructor
     */
    Edge(int p1, int p2);

    /* Computes the normal vector of the edge
     * @param points mesh points
     * @return the normal vector
     */
    Pair<double> getNormal(std::vector<Point> &points);

    /* Computes the length of the edge
     * @param points mesh points
     * @return length of the edge
     */
    double getLength(std::vector<Point> &points);

    /* Computes the middle point of the edge
     * @param points mesh points
     * @return middle point of the edge
     */
    Point middlePoint(std::vector<Point> &points);
};


#endif