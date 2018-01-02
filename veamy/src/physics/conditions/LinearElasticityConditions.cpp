#include <veamy/physics/conditions/LinearElasticityConditions.h>

LinearElasticityConditions::LinearElasticityConditions(ConstraintsContainer container, BodyForce *f, Material *mat) :
        Conditions(container, f){
    this->material = mat;
}

LinearElasticityConditions::LinearElasticityConditions(ConstraintsContainer container, Material *mat) :
        Conditions(container, new None(0,0)){
    this->material = mat;
}

LinearElasticityConditions::LinearElasticityConditions(Material *mat, BodyForce *force) : Conditions(force){
    this->material = mat;
}

LinearElasticityConditions::LinearElasticityConditions(Material *mat) : Conditions(new None(0,0)){
    this->material = mat;
}

void LinearElasticityConditions::addNaturalConstraint(PointConstraint &constraint,
                                                      elasticity_constraints::Direction direction) {
    constraint.setDirection(elasticity_constraints::constraints[direction]);
    Conditions::addNaturalConstraint(constraint);
}

void LinearElasticityConditions::addNaturalConstraint(SegmentConstraint &constraint, std::vector<Point> &points,
                                                      elasticity_constraints::Direction direction) {
    constraint.setDirection(elasticity_constraints::constraints[direction]);
    Conditions::addNaturalConstraint(constraint, points);
}

void LinearElasticityConditions::addNaturalConstraint(SegmentConstraint &constraint, UniqueList<Point> &points,
                                                      elasticity_constraints::Direction direction) {
    this->addNaturalConstraint(constraint, points.getList(), direction);
}

void LinearElasticityConditions::addEssentialConstraint(PointConstraint &constraint,
                                                        elasticity_constraints::Direction direction) {
    constraint.setDirection(elasticity_constraints::constraints[direction]);
    Conditions::addNaturalConstraint(constraint);
}

void LinearElasticityConditions::addEssentialConstraint(SegmentConstraint &constraint, std::vector<Point> &points,
                                                        elasticity_constraints::Direction direction) {
    constraint.setDirection(elasticity_constraints::constraints[direction]);
    Conditions::addNaturalConstraint(constraint, points);
}

void LinearElasticityConditions::addEssentialConstraint(SegmentConstraint &constraint, UniqueList<Point> &points,
                                                        elasticity_constraints::Direction direction) {
    this->addEssentialConstraint(constraint, points.getList(), direction);
}
