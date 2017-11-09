#include <veamy/postprocess/calculators/DisplacementCalculator.h>
#include <veamy/models/dof/DOFS.h>

template <typename T>
DisplacementCalculator<T>::DisplacementCalculator(DOFS d, Eigen::VectorXd u) {
    this->dofs = d;
    this->nodalValues = u;
}

template class DisplacementCalculator<Triangle>;
template class DisplacementCalculator<Polygon>;