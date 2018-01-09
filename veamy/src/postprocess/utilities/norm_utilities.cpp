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

    Eigen::MatrixXd trianglePoints(Triangle& t, std::vector<Point>& points){
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

    void triangle_rules(Eigen::MatrixXd &points, Triangle &poly, std::vector<double> &weights, int order,
                            std::vector<Point> &meshPoints) {
        Eigen::MatrixXd triangle = norm_utilities::trianglePoints(poly, meshPoints);
        double area = poly.getArea();

        if (order==1) {
            Eigen::Matrix<double,1,3> t;
            t << 1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0;

            weights.push_back(1.0*area);
            points = t * triangle;

            return;
        }

        if(order == 2){
            Eigen::Matrix<double,3,3> t;
            t <<    2.0 / 3.0, 1.0 / 6.0, 1.0 / 6.0,
                    1.0 / 6.0, 2.0 / 3.0, 1.0 / 6.0,
                    1.0 / 6.0, 1.0 / 6.0, 2.0 / 3.0;

            weights.push_back(1.0 / 3.0 * area);
            weights.push_back(1.0 / 3.0 * area);
            weights.push_back(1.0 / 3.0 * area);

            points = t * triangle;

            return;
        }

        if (order==3){
            Eigen::Matrix<double,6,3> t;
            t <<    0.659027622374092, 0.231933368553031, 0.109039009072877,
                    0.109039009072877, 0.659027622374092, 0.231933368553031,
                    0.231933368553031, 0.109039009072877, 0.659027622374092,
                    0.109039009072877, 0.231933368553031, 0.659027622374092,
                    0.231933368553031, 0.659027622374092, 0.109039009072877,
                    0.659027622374092, 0.109039009072877, 0.231933368553031;

            weights.push_back(1.0/6.0 * area);
            weights.push_back(1.0/6.0 * area);
            weights.push_back(1.0/6.0 * area);
            weights.push_back(1.0/6.0 * area);
            weights.push_back(1.0/6.0 * area);
            weights.push_back(1.0/6.0 * area);

            points = t * triangle;

            return;
        }

        if (order==4) {
            Eigen::Matrix<double,6,3> t;
            t <<    0.816847572980459, 0.091576213509771, 0.091576213509771,
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

        if (order==5) {
            Eigen::Matrix<double,7,3> t;
            t <<    1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0,
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