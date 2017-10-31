#include <feamy/Feamer.h>

void Feamer::initProblem(Mesh<Triangle> m, Conditions conditions, FemElementConstructor *constructor) {
    std::vector<Point> meshPoints = m.getPoints().getList();
    this->points.push_list(meshPoints);
    this->conditions = conditions;

    std::vector<Triangle> triangles = m.getPolygons();

    for(int i=0;i<triangles.size();i++){
        this->elements.push_back(constructor->createElement(this->conditions, triangles[i], this->points, DOFs));
    }
}

void Feamer::createAndAssemble(Eigen::MatrixXd &KGlobal, Eigen::VectorXd &fGlobal) {
    for(int i=0;i<elements.size();i++){
        elements[i]->computeK(DOFs, this->points, conditions);
        elements[i]->computeF(DOFs, this->points, conditions);
        elements[i]->assemble(DOFs, KGlobal, fGlobal);
    }
}

double Feamer::computeErrorNorm(NormCalculator *calculator, Mesh<Triangle> mesh) {
    return 0;
}
