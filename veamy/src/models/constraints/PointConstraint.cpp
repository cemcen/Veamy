#include <veamy/models/constraints/PointConstraint.h>

PointConstraint::PointConstraint() : Constraint(){}

PointConstraint::PointConstraint(Point p, Constraint::Direction d, ConstraintValue *value) : Constraint(d, value) {
    this->constraints.push_back(p);
}

PointConstraint::PointConstraint(std::vector<Point> p, Constraint::Direction d, ConstraintValue *value) : Constraint(d, value){
    this->constraints.push_list(p);
}

UniqueList<Point> PointConstraint::getPoints() {
    return this->constraints;
}
