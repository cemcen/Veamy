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
    extern Eigen::MatrixXd QMatrix(Eigen::MatrixXd &Wc);
    extern Eigen::VectorXd getElementNodalValues(Polygon &poly, Eigen::VectorXd &uNodal, DOFS &d);
    extern Eigen::VectorXd getAverage(Eigen::VectorXd u);
    extern Eigen::MatrixXd trianglePoints(Triangle& t, std::vector<Point>& points);
    extern void triangle_rules(Eigen::MatrixXd &points, Triangle &poly, std::vector<double> &weights, int order,
                                   std::vector<Point> &meshPoints);
}

#endif