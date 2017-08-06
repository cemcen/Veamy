#include <veamy/models/constraints/Constraint.h>

Constraint::Constraint() {}

Constraint::Constraint(Constraint::Direction d, ConstraintValue *value) {
    this->v = value;
    this->direction = d;
}

double Constraint::getValue(Point p) {
    return v->getValue(p);
}

Constraint::Direction Constraint::getDirection() {
    return direction;
}

int Constraint::isAffected(DOF::Axis axis) {
    switch (direction){
        case Total:
            return 1;
        case Horizontal:
            return axis == DOF::Axis::x? 1 : 0;
        case Vertical:
            return axis == DOF::Axis::y? 1 : 0;
    }
}



