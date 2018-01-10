#include <feamy/Feamer.h>
#include <feamy/postprocess/integrator/FeamyIntegrator.h>

Feamer::Feamer(ProblemDiscretization<Triangle,Feamer> *problem) :
        Calculator2D(problem->getConditions(), problem->numberOfDOFs()){
    this->problem = problem;
}

void Feamer::initProblem(Mesh<Triangle> m, FeamyElementConstructor *constructor) {
    UniqueList<Point>& meshPoints = m.getPoints();
    this->points.push_list(meshPoints);

    std::vector<Triangle> triangles = m.getPolygons();

    for(int i=0;i<triangles.size();i++){
        FeamyElement* newElement = (FeamyElement*)this->problem->createElement(this, triangles[i], meshPoints);
        newElement->setShapeFunctions(constructor->getShapeFunctions(triangles[i], meshPoints));

        this->elements.push_back(newElement);
    }
}

NormResult Feamer::computeErrorNorm(NormCalculator<Triangle>* calculator, Mesh<Triangle> mesh) {
    return problem->computeErrorNorm(calculator, mesh);
}
