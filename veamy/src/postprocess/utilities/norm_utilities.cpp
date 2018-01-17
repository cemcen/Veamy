#include <veamy/postprocess/utilities/norm_utilities.h>
#include <veamy/models/Edge.h>

namespace norm_utilities{
    Eigen::VectorXd getAverage(Eigen::VectorXd u, int n_dofs){
        Eigen::VectorXd uBar;
        uBar = Eigen::VectorXd::Zero(n_dofs);

        int n = u.rows()/n_dofs;
        std::vector<double> uH (n_dofs,0);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n_dofs; ++j) {
                 uH[j] += u(n_dofs*i + j);
            }
        }

        for (int k = 0; k < n_dofs; ++k) {
            uBar(k) = uH[k]/n;
        }

        return uBar;
    }
}