#include <veamy/postprocess/H1NormCalculator.h>

H1NormCalculator::H1NormCalculator(StrainValue *strain, StressValue *stress, Eigen::VectorXd u, DOFS d,
                                   std::vector<Point> points) : NormCalculator(u, d){
    this->strainValue = strain;
    this->stressValue = stress;
}

void H1NormCalculator::setCalculator(NormIntegrator *integrator) {
    VeamyIntegrator* obj = dynamic_cast<VeamyIntegrator*>(integrator);

    if(obj!= nullptr){
        this->setCalculator(obj);
        return;
    }

    FeamyIntegrator* obj2 = dynamic_cast<FeamyIntegrator*>(integrator);

    if(obj2!= nullptr){
        this->setCalculator(obj2);
        return;
    }
}

void H1NormCalculator::setCalculator(FeamyIntegrator *integrator, ) {
    NormIntegrator* den = integrator->clone();




    num->setComputable(new StrainStressDifferenceComputable(this->strainValue, this->stressValue, this->nodalDisplacements,
                                                            this->dofs, ));
    den->setComputable(new StrainStressComputable(this->strainValue, this->stressValue));

    NormCalculator::setCalculators(num, den);
}

void H1NormCalculator::setCalculator(VeamyIntegrator *integrator) {

}
