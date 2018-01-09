#include <veamy/postprocess/ElasticityH1NormCalculator.h>

template <typename T>
ElasticityH1NormCalculator<T>::ElasticityH1NormCalculator(StrainValue *strain, StressValue *stress, DisplacementValue* value,
                                                          Eigen::VectorXd u, DOFS d) : NormCalculator<T>(u, d) {
    this->strainValue = strain;
    this->stressValue = stress;
    this->value = value;

    this->numComputable = new StrainStressDifferenceComputable<T>(this->strainValue, this->stressValue);
    this->denComputable = new StrainStressComputable<T>(this->strainValue, this->stressValue);
}

template <typename T>
ElasticityH1NormCalculator<T>::ElasticityH1NormCalculator(StrainValue *strain, DisplacementValue *value, Eigen::VectorXd u,
                                                       DOFS d) : NormCalculator<T>(u, d) {
    this->strainValue = strain;
    this->value = value;

    this->numComputable = new StrainDifferenceComputable<T>(this->strainValue);
    this->denComputable = new StrainComputable<T>(this->strainValue);
}

template <typename T>
void ElasticityH1NormCalculator<T>::setCalculator(FeamyIntegrator<T>* integrator, FeamyAdditionalInfo info) {
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
void ElasticityH1NormCalculator<T>::setCalculator(VeamyIntegrator<T> *integrator, std::vector<Point> &point) {
    NormIntegrator<T>* den = integrator->clone();

    this->num = integrator;
    this->den = den;

    VeamyStrainCalculator<T>* calculator = new VeamyStrainCalculator<T>(this->dofs, this->nodalDisplacements, point);

    this->numComputable->setCalculator(calculator);

    this->num->setComputable(this->numComputable);
    this->den->setComputable(this->denComputable);
}

template <typename T>
void ElasticityH1NormCalculator<T>::setExtraInformation(Conditions *conditions) {
    LinearElasticityConditions* c = (LinearElasticityConditions*) conditions;

    numComputable->setMaterialMatrix(c->material->getMaterialMatrix());
    denComputable->setMaterialMatrix(c->material->getMaterialMatrix());
}

template class ElasticityH1NormCalculator<Triangle>;
template class ElasticityH1NormCalculator<Polygon>;