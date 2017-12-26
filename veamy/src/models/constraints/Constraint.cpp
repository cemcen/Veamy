#include <veamy/models/constraints/Constraint.h>

Constraint::Constraint() {}

Constraint::Constraint(ConstraintValue *value) {
    this->v = value;
}

double Constraint::getValue(Point p) {
    return v->getValue(p);
}

std::vector<int> Constraint::getDirection() {
    return direction;
}

int Constraint::isAffected(int axis) {

}



