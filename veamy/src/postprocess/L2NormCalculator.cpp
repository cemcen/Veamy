#include <veamy/postprocess/L2NormCalculator.h>
#include <veamy/postprocess/computables/DisplacementDifferenceComputable.h>
#include <veamy/postprocess/computables/DisplacementComputable.h>

L2NormCalculator::L2NormCalculator(DisplacementValue *value, Eigen::VectorXd u, DOFS d) : NormCalculator(u, d) {
    this->value = value;
}

void L2NormCalculator::setCalculators(NormIntegrator* num) {
    NormIntegrator* den = num->clone();

    num->setComputable(new DisplacementDifferenceComputable(this->value, this->nodalDisplacements, this->dofs));
    den->setComputable(new DisplacementComputable(this->value));

    NormCalculator::setCalculators(num, den);
}


