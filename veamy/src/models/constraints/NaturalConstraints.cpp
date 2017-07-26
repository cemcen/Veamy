#include <veamy/models/constraints/NaturalConstraints.h>

NaturalConstraints::NaturalConstraints() {}

Eigen::VectorXd NaturalConstraints::boundaryVector(std::vector<Point> points, Polygon p, IndexSegment segment) {
    isConstrainedInfo constrainedInfo = isConstrained(points, segment);

    if(constrainedInfo.isConstrained){
        std::vector<int> polygonPoints = p.getPoints();
        int n = (int) polygonPoints.size();

        std::vector<Constraint> constraints = segment_map[constrainedInfo.container];

        Eigen::MatrixXd Nbar;
        Nbar = Eigen::MatrixXd::Zero(2,4);
        Nbar(0,0) = 1.0/2;
        Nbar(1,1) = 1.0/2;
        Nbar(0,2) = 1.0/2;
        Nbar(1,3) = 1.0/2;

        std::cout<< Nbar << std::endl << std::endl;
        Eigen::VectorXd h;

        h = Eigen::VectorXd::Zero(2);

        for(Constraint c: constraints){
            h(0) += c.getValue(points[segment.getFirst()])*c.isAffected(DOF::Axis::x);
            h(1) += c.getValue(points[segment.getSecond()])*c.isAffected(DOF::Axis::y);
        }

        std::cout<< h << std::endl << std::endl;
        std::cout<< Nbar.transpose()*h << std::endl << std::endl;

        double length = segment.length(points);
        Eigen::VectorXd result = length*(Nbar.transpose()*h);
        std::cout << result << std::endl << std::endl;

        return result;
    }

    Eigen::VectorXd zeros;
    zeros = Eigen::VectorXd::Zero(4);

    return zeros;
}

