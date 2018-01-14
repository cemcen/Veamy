#include <veamy/postprocess/utilities/norm_utilities.h>
#include <veamy/models/Edge.h>

namespace norm_utilities{
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

    Eigen::VectorXd getAverage(Eigen::VectorXd u){
        Eigen::VectorXd uBar;
        uBar = Eigen::VectorXd::Zero(2);

        int n = u.rows()/2;
        double uX = 0, uY = 0;

        for (int i = 0; i < n; ++i) {
            uX += u(2*i);
            uY += u(2*i+1);
        }

        uBar(0) = uX/n;
        uBar(1) = uY/n;

        return uBar;
    }
}