#ifndef VEAMY_NORM_UTILITIES_H
#define VEAMY_NORM_UTILITIES_H

#include <veamy/lib/Eigen/Dense>
#include <delynoi/models/polygon/Polygon.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/models/Edge.h>

namespace norm_utilities{
    /* Gets the nodal values associated to a given element
     * @param poly element
     * @param uNodal list of all nodal values
     * @param d degrees of freedom of the system (associates point to DOF)
     */
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

    /* Computes the average value of a vector of nodal values
     * @param u nodal values
     * @param n_dofs number of degrees of freedom of the system (determines the number of components of the result of
     * this function)
     * @return vector with the average of each component of the nodal values
     */
    extern Eigen::VectorXd getAverage(Eigen::VectorXd &u, int n_dofs);
}

#endif