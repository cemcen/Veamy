#ifndef VEAMY_NATURALCONSTRAINTS_H
#define VEAMY_NATURALCONSTRAINTS_H

#include <mesher/models/polygon/Polygon.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/Constraints.h>

class NaturalConstraints : public Constraints{
public:
    NaturalConstraints();
    double boundaryVector(std::vector<Point> points, Polygon p, int point, int DOF_index);
};


#endif
