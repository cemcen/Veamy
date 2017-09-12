#ifndef VEAMY_NATURALCONSTRAINTS_H
#define VEAMY_NATURALCONSTRAINTS_H

#include <delynoi/models/polygon/Polygon.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/Constraints.h>

class NaturalConstraints : public Constraints{
public:
    NaturalConstraints();
    Eigen::VectorXd boundaryVector(std::vector<Point> points, Polygon p, IndexSegment segment);
};


#endif
