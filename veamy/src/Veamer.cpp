#include <veamy/Veamer.h>

Veamer::Veamer(ProblemDiscretization<Polygon,Veamer>* problem) :
        Calculator2D(problem->getConditions(), problem->numberOfDOFs()) {
    this->problem = problem;
}

Mesh<Polygon> Veamer::initProblemFromFile(std::string fileName) {
    Mesh<Polygon> mesh = this->problem->initProblemFromFile(this, fileName);
    initProblem(mesh);

    return mesh;
}

void Veamer::initProblem(const Mesh<Polygon> &m) {
    std::vector<Point> meshPoints = m.getPoints().getList();
    this->points.push_list(meshPoints);

    std::vector<Polygon> polygons = m.getPolygons();

    for(int i=0;i<polygons.size();i++){
        this->elements.push_back(this->problem->createElement(this, polygons[i], this->points));
    }
}

NormResult Veamer::computeErrorNorm(NormCalculator<Polygon> *calculator, Mesh<Polygon> mesh) {
    return problem->computeErrorNorm(calculator, mesh);
}

