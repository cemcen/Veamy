#ifndef VEAMY_NORM_UTILITIES_H
#define VEAMY_NORM_UTILITIES_H

#include <veamy/lib/Eigen/Dense>
#include <delynoi/models/polygon/Polygon.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/models/Edge.h>

namespace norm_utilities{
    template <typename T>
    Eigen::MatrixXd WcMatrix(T &p, std::vector<Point> &points) {
        std::vector<int> polygonPoints = p.getPoints();
        int n = (int) polygonPoints.size();
        Point average = p.getAverage(points);

        double area = p.getArea();

        Eigen::MatrixXd Wc;
        Wc = Eigen::MatrixXd::Zero(2*n, 3);

        for(int vertex_id=0; vertex_id<n; vertex_id++){
            Point vertex = points[polygonPoints[vertex_id]];

            Edge prev (polygonPoints[(n+vertex_id-1)%n], polygonPoints[vertex_id]);
            Edge next (polygonPoints[vertex_id], polygonPoints[(n+vertex_id+1)%n]);

            Pair<double> prevNormal = utilities::normalize(prev.getNormal(points));
            Pair<double> nextNormal = utilities::normalize(next.getNormal(points));

            double prevLength = prev.getLength(points);
            double nextLength = next.getLength(points);

            double Qi_x = (prevNormal.first*prevLength + nextNormal.first*nextLength)/(4*area);
            double Qi_y = (prevNormal.second*prevLength + nextNormal.second*nextLength)/(4*area);

            Wc(2*vertex_id, 0) = 2*Qi_x;
            Wc(2*vertex_id, 2) = Qi_y;
            Wc(2*vertex_id+1, 1) = 2*Qi_y;
            Wc(2*vertex_id+1, 2) = Qi_x;
        }

        return Wc;
    }

    template <typename T>
    Eigen::VectorXd getElementNodalValues(T &poly, Eigen::VectorXd &uNodal, DOFS &d) {
        int n_dofs = d.getNumberOfDOFS();
        std::vector<int> points = poly.getPoints();

        Eigen::VectorXd uPoly;
        uPoly = Eigen::VectorXd::Zero(points.size()*n_dofs);

        for (int i = 0; i < points.size(); ++i) {
            std::vector<int> dofs = d.pointToDOFS(points[i]);

            for (int j = 0; j < dofs.size(); ++j) {
                uPoly(n_dofs*i+j) = uNodal[dofs[j]];
            }
        }

        return uPoly;
    }

    extern Eigen::MatrixXd QMatrix(Eigen::MatrixXd &Wc);
    extern Eigen::VectorXd getAverage(Eigen::VectorXd u);

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

    template <typename T>
    extern void triangle_rules(Eigen::MatrixXd &points, T &poly, std::vector<double> &weights, int order,
                                   std::vector<Point> &meshPoints) {
        Eigen::MatrixXd triangle = norm_utilities::trianglePoints(poly, meshPoints);
        double area = poly.getArea();

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