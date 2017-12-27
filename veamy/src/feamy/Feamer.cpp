#include <feamy/Feamer.h>
#include <feamy/postprocess/integrator/FeamyIntegrator.h>

Feamer::Feamer(ProblemDiscretization *problem) {
    this->problem = problem;
}

void Feamer::initProblem(Mesh<Triangle> m, Conditions* conditions, FeamyElementConstructor *constructor) {
    std::vector<Point> meshPoints = m.getPoints().getList();
    this->points.push_list(meshPoints);

    std::vector<Triangle> triangles = m.getPolygons();

    for(int i=0;i<triangles.size();i++){
        this->elements.push_back(constructor->createElement(this->problem->getConditions(), triangles[i], this->points, DOFs));
    }
}

double Feamer::computeErrorNorm(NormCalculator<Triangle>* calculator, Mesh<Triangle> mesh) {
    FeamyAdditionalInfo info(this->elements, this->points.getList(),
                             this->conditions.material->getMaterialMatrix());

    calculator->setCalculator(new FeamyIntegrator<Triangle>, info);
    return calculator->getNorm(mesh);
}
