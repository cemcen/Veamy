#include <veamy/postprocess/H1NormCalculator.h>

template <typename T>
H1NormCalculator<T>::H1NormCalculator(StrainValue *strain, StressValue *stress,
                                                          Eigen::VectorXd u, DOFS d) : NormCalculator<T>(u, d) {
    this->strainValue = strain;
    this->stressValue = stress;

    this->numComputable = new StrainStressDifferenceComputable<T>(this->strainValue, this->stressValue);
    this->denComputable = new StrainStressComputable<T>(this->strainValue, this->stressValue);
}

template <typename T>
H1NormCalculator<T>::H1NormCalculator(StrainValue *strain, Eigen::VectorXd u,
                                                       DOFS d) : NormCalculator<T>(u, d) {
    this->strainValue = strain;

    this->numComputable = new StrainDifferenceComputable<T>(this->strainValue);
    this->denComputable = new StrainComputable<T>(this->strainValue);
}

template <typename T>
void H1NormCalculator<T>::setCalculator(FeamyIntegrator<T>* integrator, FeamyAdditionalInfo info) {
    NormIntegrator<T>* den = integrator->clone();

    this->num = integrator;
    this->den = den;

    FeamyStrainCalculator<T>* calculator = new FeamyStrainCalculator<T>(info.points, info.elements,
                                                                  this->nodalDisplacements, this->dofs);
    this->numComputable->setCalculator(calculator);

    this->num->setComputable(this->numComputable);
    this->den->setComputable(this->denComputable);
}

template <typename T>
void H1NormCalculator<T>::setCalculator(VeamyIntegrator<T> *integrator, CalculatorConstructor<T> *calculator,
                                        std::vector<Point>& points) {
    NormIntegrator<T>* den = integrator->clone();

    this->num = integrator;
    this->den = den;

    this->numComputable->setCalculator(calculator->getStrainCalculator(points));

    this->num->setComputable(this->numComputable);
    this->den->setComputable(this->denComputable);
}

template <typename T>
void H1NormCalculator<T>::setExtraInformation(LinearElasticityConditions *conditions) {
    numComputable->setMaterialMatrix(conditions->material->getMaterialMatrix());
    denComputable->setMaterialMatrix(conditions->material->getMaterialMatrix());
}

template <typename T>
void H1NormCalculator<T>::setExtraInformation(PoissonConditions *conditions) {
    Eigen::MatrixXd I;
    I = Eigen::MatrixXd::Identity(2,2);

    numComputable->setMaterialMatrix(I);
    denComputable->setMaterialMatrix(I);
}

template class H1NormCalculator<Triangle>;
template class H1NormCalculator<Polygon>;