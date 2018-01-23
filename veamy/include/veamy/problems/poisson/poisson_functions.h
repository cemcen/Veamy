#ifndef VEAMY_POISSON_FUNCTIONS_H
#define VEAMY_POISSON_FUNCTIONS_H

#include <delynoi/models/basic/Point.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/Edge.h>

/*
 * Namespace containing functions used only for poisson problems solved using VEM
 */
namespace poisson_functions{
    /* Computes the W matrix used for VEM solving poisson
     * @param p geometry of the element
     * @param points mesh points
     * @return W matrix of p
     */
    template <typename T>
    Eigen::MatrixXd WMatrix(T &p, std::vector<Point> &points){
        std::vector<int> polygonPoints = p.getPoints();
        int n = (int) polygonPoints.size();
        double area = p.getArea();

        Eigen::MatrixXd W;
        W = Eigen::MatrixXd::Zero(n, 2);

        for(int vertex_id=0; vertex_id<n; vertex_id++){
            Edge prev (polygonPoints[(n+vertex_id-1)%n], polygonPoints[vertex_id]);
            Edge next (polygonPoints[vertex_id], polygonPoints[(n+vertex_id+1)%n]);

            Pair<double> prevNormal = utilities::normalize(prev.getNormal(points));
            Pair<double> nextNormal = utilities::normalize(next.getNormal(points));

            double prevLength = prev.getLength(points);
            double nextLength = next.getLength(points);

            double Qi_x = (prevNormal.first*prevLength + nextNormal.first*nextLength)/(4*area);
            double Qi_y = (prevNormal.second*prevLength + nextNormal.second*nextLength)/(4*area);

            W(vertex_id, 0) = 2*Qi_x;
            W(vertex_id, 1) = 2*Qi_y;
        }

        return W;
    }
}

#endif