#include <veamy/problems/ScalarProblem.h>

void ScalarProblem::addConstraint(NaturalConstraints natural, PointConstraint constraint) {
    natural.addConstraint(constraint);
}

void ScalarProblem::addConstraint(NaturalConstraints natural, SegmentConstraint constraint, const std::vector<Point> &points) {
    natural.addConstraint(constraint);
}

void ScalarProblem::addConstraint(EssentialConstraints essential, PointConstraint constraint) {
    essential.addConstraint(constraint);
}

void ScalarProblem::addConstraint(EssentialConstraints essential, SegmentConstraint constraint) {

}
