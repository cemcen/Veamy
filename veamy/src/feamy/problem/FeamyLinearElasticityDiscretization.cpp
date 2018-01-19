#include <feamy/problem/FeamyLinearElasticityDiscretization.h>
#include <feamy/problem/linear_elasticity/LinearElasticityBoundaryVectorIntegrable.h>
#include <feamy/problem/linear_elasticity/LinearElasticityBodyForceIntegrable.h>
#include <feamy/problem/linear_elasticity/LinearElasticityStiffnessMatrixIntegrable.h>

FeamyLinearElasticityDiscretization::FeamyLinearElasticityDiscretization(LinearElasticityConditions *conditions) :
        ProblemDiscretization(conditions){
    this->conditions = conditions;
    this->numberDOF = 2;
    this->conditions->material->setMultiplicativeFactor(0.5);
}

Element<Triangle> *
FeamyLinearElasticityDiscretization::createElement(Feamer *f, Triangle &poly, UniqueList<Point> &points) {
    VeamyTriangle t (poly);
    FeamyElement* newElement = new FeamyElement(this->conditions, poly, points, f->DOFs, this->numberDOF);

    newElement->setIntegrables(new LinearElasticityBodyForceIntegrable(conditions->f),
                               new LinearElasticityBoundaryVectorIntegrable(),
                               new LinearElasticityStiffnessMatrixIntegrable(t, points.getList(),
                                                                             conditions->material->getMaterialMatrix()));

    return newElement;
}

Mesh<Triangle> FeamyLinearElasticityDiscretization::initProblemFromFile(std::string fileName) {
    //TODO: To be implemented
    return Mesh<Triangle>();
}

NormResult
FeamyLinearElasticityDiscretization::computeErrorNorm(NormCalculator<Triangle> *calculator, Mesh<Triangle> mesh, Feamer* f) {
    FeamyAdditionalInfo info(f->getElements(), mesh.getPoints().getList());

    calculator->setCalculator(new FeamyIntegrator<Triangle>, info);
    calculator->setExtraInformation(this->conditions);

    return calculator->getNorm(mesh);
}
