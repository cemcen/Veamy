#include <veamy/Veamer.h>
#include <iomanip>
#include <veamy/models/constraints/values/Constant.h>


Veamer::Veamer(ProblemDiscretization *problem) {
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

double Veamer::computeErrorNorm(NormCalculator<Polygon> *calculator, Mesh<Polygon> mesh) {
    calculator->setCalculator(new VeamyIntegrator<Polygon>);
    return calculator->getNorm(mesh);
}

