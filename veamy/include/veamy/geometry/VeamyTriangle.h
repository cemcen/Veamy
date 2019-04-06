#ifndef VEAMY_VEAMYTRIANGLE_H
#define VEAMY_VEAMYTRIANGLE_H

#include <delynoi/models/polygon/Triangle.h>
#include <veamy/lib/Eigen/Dense>

/*
 * Models a triangle, but with extra operations that only concern the Veamy library (mostly, triangulating and computing
 * the jacobian)
 */
class VeamyTriangle: public Triangle {
public:
    /*
     * Default constructor
     */
    VeamyTriangle();

    /*
     * Constructor. Constructs a VeamyTriangle from a Triangle
     */
    VeamyTriangle(Triangle t);

    /*
     * Constructor. Does nothing (a VeamyTriangle from a Polygon is included for completitude)
     */
    VeamyTriangle(Polygon p);

    /*
     * Constructor. Constructs a VeamyTriangle from three point indexes
     */
    VeamyTriangle(int p1, int p2, int p3);

    /* Triangulates the VeamyTriangle
     * @param points mesh points
     * @return list with the triangle triangle (it just contains this instance)
     */
    std::vector<VeamyTriangle> triangulate(std::vector<Point> &points);

    /* Computes the jacobian matrix of the triangle
     * @param points list of point the vertex make reference to
     * @return jacobian matrix
     */
    Eigen::MatrixXd getJacobian(std::vector<Point> &points);

    /*
     * @return if the instance is valid or not (has indexes set)
     */
    bool isNull();

    /* Finds the index in the vertex list of a given point
     * @param i point to find
     * @return index of i in the vertex list of this VeamyTriangle
     */
    int indexOf(int i);
};

#endif