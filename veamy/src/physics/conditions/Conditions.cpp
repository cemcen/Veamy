#include <veamy/physics/conditions/Conditions.h>

Conditions::Conditions(ConstraintsContainer container, BodyForce *bodyForce) {
    this->constraints = container;
    this->f = bodyForce;
}

Conditions::Conditions(BodyForce *bodyForce) {
    this->f = bodyForce;
}

Conditions::Conditions() {}

void Conditions::addNaturalConstraint(PointConstraint &constraint) {
    NaturalConstraints& natural = this->constraints.getNaturalConstraints();
    natural.addConstraint(constraint);
}

void Conditions::addNaturalConstraint(SegmentConstraint &constraint, std::vector<Point> &points) {
    NaturalConstraints& natural = this->constraints.getNaturalConstraints();
    natural.addConstraint(constraint, points);
}

void Conditions::addNaturalConstraint(SegmentConstraint &constraint, UniqueList<Point> &points) {
    this->addNaturalConstraint(constraint, points.getList());
}

void Conditions::addEssentialConstraint(PointConstraint &constraint) {
    EssentialConstraints& essential = this->constraints.getEssentialConstraints();
    essential.addConstraint(constraint);
}

void Conditions::addEssentialConstraint(SegmentConstraint &constraint, std::vector<Point> &points) {
    EssentialConstraints& essential = this->constraints.getEssentialConstraints();
    essential.addConstraint(constraint, points);
}

void Conditions::addEssentialConstraint(SegmentConstraint &constraint, UniqueList<Point> &points) {
    this->addEssentialConstraint(constraint, points.getList());
}
