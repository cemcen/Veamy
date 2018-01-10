#include <veamy/models/constraints/Constraint.h>

Constraint::Constraint() {
    this->direction = {0};
}

Constraint::Constraint(ConstraintValue *value) {
    this->direction = {0};
    this->v = value;
}

double Constraint::getValue(Point p) {
    return v->getValue(p);
}

std::vector<int> Constraint::getDirection() {
    return direction;
}

int Constraint::isAffected(int axis) {
    return std::find(direction.begin(), direction.end(), axis) != direction.end();
}

void Constraint::setDirection(std::vector<int> d) {
    this->direction.assign(d.begin(), d.end());
}



