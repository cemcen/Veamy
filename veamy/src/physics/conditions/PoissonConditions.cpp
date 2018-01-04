#include <veamy/physics/conditions/PoissonConditions.h>

PoissonConditions::PoissonConditions(ConstraintsContainer container, BodyForce *f) : Conditions(container, f) {}

PoissonConditions::PoissonConditions(ConstraintsContainer container) : Conditions(container, new None(0)){}

PoissonConditions::PoissonConditions(BodyForce *f) : Conditions(f) {}

PoissonConditions::PoissonConditions() : Conditions(new None(0)){}
