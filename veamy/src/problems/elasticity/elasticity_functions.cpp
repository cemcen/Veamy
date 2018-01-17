#include <veamy/problems/elasticity/elasticity_functions.h>

namespace elasticity_functions{
    Eigen::MatrixXd QMatrix(Eigen::MatrixXd &Wc) {
        int n = Wc.rows()/2;

        Eigen::MatrixXd Q;
        Q = Eigen::MatrixXd::Zero(2*n, 2);

        for (int i = 0; i < n; ++i) {
            double Qi_x = Wc(2*i+1, 2);
            double Qi_y = Wc(2*i, 2);

            Q(2*i, 0) = Qi_y;
            Q(2*i, 1) = -Qi_y;
            Q(2*i+1, 0) = -Qi_x;
            Q(2*i+1, 1) = Qi_x;
        }

        return Q;
    }
}