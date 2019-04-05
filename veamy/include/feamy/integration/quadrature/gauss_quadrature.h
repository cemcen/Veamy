#ifndef VEAMY_GAUSSPOINTS_H
#define VEAMY_GAUSSPOINTS_H

#include <vector>
#include <delynoi/models/basic/Point.h>
#include <veamy/lib/Eigen/Dense>

/*
 * Namespace which contain functions related to the gaussian quadratures
 */
namespace gauss_quadrature{
    /*
     * Sets in two given vectors the quadrature points and weights of a line
     * @param order order of the quadrature
     * @param points,weights vectors where the points and weights will be set
     */
    extern void gauss_1d(int order, std::vector<double>& points, std::vector<double>& weights);

    /* Creates a matrix with the points of a polygon
     * @param t polygon
     * @param points mesh points
     * @return the points of the polygon in matrix form
     */
    template <typename T>
    Eigen::MatrixXd trianglePoints(T& t, std::vector<Point>& points){
        std::vector<Point> trianglePoints = t.getPoints(points);

        Eigen::MatrixXd triangle;
        triangle = Eigen::MatrixXd::Zero(t.numberOfSides(), 2);

        for (int i = 0; i < trianglePoints.size(); ++i) {
            Point p = trianglePoints[i];

            triangle(i, 0) = p.getX();
            triangle(i, 1) = p.getY();
        }

        return triangle;
    }

    /*
     * Sets the quadrature points and weights of a triangle
     * @param poly triangle
     * @param weights vector where the weights will be set
     * @param order order of the quadrature
     * @param meshPoints mesh points
     */
    template <typename T>
    void triangle_rules(Eigen::MatrixXd &points, T &poly, std::vector<double> &weights, int order,
                               std::vector<Point> &meshPoints) {
        Eigen::MatrixXd triangle = gauss_quadrature::trianglePoints(poly, meshPoints);
        double area = poly.getArea(meshPoints);

        if (order == 1) {
            Eigen::Matrix<double, 1, 3> t;
            t << 1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0;

            weights.push_back(1.0 * area);
            points = t * triangle;

            return;
        }

        if (order == 2) {
            Eigen::Matrix<double, 3, 3> t;
            t << 2.0 / 3.0, 1.0 / 6.0, 1.0 / 6.0,
                    1.0 / 6.0, 2.0 / 3.0, 1.0 / 6.0,
                    1.0 / 6.0, 1.0 / 6.0, 2.0 / 3.0;

            weights.push_back(1.0 / 3.0 * area);
            weights.push_back(1.0 / 3.0 * area);
            weights.push_back(1.0 / 3.0 * area);

            points = t * triangle;

            return;
        }

        if (order == 3) {
            Eigen::Matrix<double, 6, 3> t;
            t << 0.659027622374092, 0.231933368553031, 0.109039009072877,
                    0.109039009072877, 0.659027622374092, 0.231933368553031,
                    0.231933368553031, 0.109039009072877, 0.659027622374092,
                    0.109039009072877, 0.231933368553031, 0.659027622374092,
                    0.231933368553031, 0.659027622374092, 0.109039009072877,
                    0.659027622374092, 0.109039009072877, 0.231933368553031;

            weights.push_back(1.0 / 6.0 * area);
            weights.push_back(1.0 / 6.0 * area);
            weights.push_back(1.0 / 6.0 * area);
            weights.push_back(1.0 / 6.0 * area);
            weights.push_back(1.0 / 6.0 * area);
            weights.push_back(1.0 / 6.0 * area);

            points = t * triangle;

            return;
        }

        if (order == 4) {
            Eigen::Matrix<double, 6, 3> t;
            t << 0.816847572980459, 0.091576213509771, 0.091576213509771,
                    0.091576213509771, 0.816847572980459, 0.091576213509771,
                    0.091576213509771, 0.091576213509771, 0.816847572980459,
                    0.108103018168070, 0.445948490915965, 0.445948490915965,
                    0.445948490915965, 0.108103018168070, 0.445948490915965,
                    0.445948490915965, 0.445948490915965, 0.108103018168070;

            weights.push_back(0.109951743655322 * area);
            weights.push_back(0.109951743655322 * area);
            weights.push_back(0.109951743655322 * area);
            weights.push_back(0.223381589678011 * area);
            weights.push_back(0.223381589678011 * area);
            weights.push_back(0.223381589678011 * area);

            points = t * triangle;

            return;
        }

        if (order == 5) {
            Eigen::Matrix<double, 7, 3> t;
            t << 1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0,
                    0.059715871789770, 0.470142064105115, 0.470142064105115,
                    0.470142064105115, 0.059715871789770, 0.470142064105115,
                    0.470142064105115, 0.470142064105115, 0.059715871789770,
                    0.797426985353087, 0.101286507323456, 0.101286507323456,
                    0.101286507323456, 0.797426985353087, 0.101286507323456,
                    0.101286507323456, 0.101286507323456, 0.797426985353087;

            weights.push_back(0.225000000000000 * area);
            weights.push_back(0.132394152788506 * area);
            weights.push_back(0.132394152788506 * area);
            weights.push_back(0.132394152788506 * area);
            weights.push_back(0.125939180544827 * area);
            weights.push_back(0.125939180544827 * area);
            weights.push_back(0.125939180544827 * area);

            points = t * triangle;
        }
    }
}


#endif