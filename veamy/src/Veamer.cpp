#include <veamy/Veamer.h>

Veamer::Veamer() {}

void Veamer::initProblem(PolygonalMesh m, ProblemConditions conditions) {
    std::vector<Point> meshPoints = m.getPoints().getList();
    this->points.push_list(meshPoints);
    this->conditions = conditions;

    std::vector<Polygon> polygons = m.getPolygons();

    for(int i=0;i<polygons.size();i++){
        createElement(polygons[i]);
    }
}

void Veamer::createElement(Polygon p) {
    elements.push_back(Element(this->conditions, p, this->points, DOFs));
}

void Veamer::insertElement(Polygon p, int index) {
    elements.insert(elements.begin() + index, Element(this->conditions, p, this->points, DOFs));
}

Eigen::VectorXd Veamer::simulate(PolygonalMesh &mesh) {
    Eigen::MatrixXd K;
    Eigen::VectorXd f;
    int n = this->DOFs.size();

    K = Eigen::MatrixXd::Zero(n,n);
    f = Eigen::VectorXd::Zero(n);

    for(int i=0;i<elements.size();i++){
        elements[i].computeK(DOFs, this->points, conditions);
        elements[i].computeF(DOFs, this->points, conditions);
        elements[i].assemble(DOFs, K, f);
    }

    //Apply constrained_points
    EssentialConstraints essential = this->conditions.constraints.getEssentialConstraints();
    std::vector<int> c = essential.getConstrainedDOF();

    Eigen::VectorXd boundary_values = essential.getBoundaryValues(this->points.getList(), this->DOFs.getDOFS());

    for (int j = 0; j < c.size(); ++j) {
        for (int i = 0; i < K.rows(); ++i) {
            f(i) = f(i) - (K(i,c[j])*boundary_values(j));

            K(c[j],i) = 0;
            K(i,c[j]) = 0;
        }

        K(c[j], c[j]) = 1;
        f(c[j]) = boundary_values(j);
    }

     //Solve the system
    Eigen::VectorXd x = K.fullPivHouseholderQr().solve(f);

    // Deform mesh
    for (int k = 0; k < x.rows(); k = k + 2) {
        int point_index = DOFs.get(k).pointIndex();
        double def_x = x[k];
        double def_y = x[k+1];

        mesh.deformPoint(point_index, def_x, def_y);
    }

    mesh.update();

    return x;
}


Pair<int> Veamer::pointToDOFS(int point_index) {
    return this->DOFs.pointToDOFS(point_index);
}

Material Veamer::getMaterial() {
    return conditions.material;
}

UniqueList<Point> Veamer::getPoints() const {
    return this->points;
}

UniqueList<Point> Veamer::getPoints() {
    return this->points;
}

ProblemConditions Veamer::getConditions() const {
    return this->conditions;
}

void Veamer::writeDisplacements(std::string fileName, Eigen::VectorXd u) {
    std::string path = utilities::getPath();
    path = path  + "ResultadosNumericos" + "\\" + fileName;

    std::ofstream file;
    file.open(path, std::ios::out);

    for (int k = 0; k < u.rows(); k = k + 2) {
        int point_index = DOFs.get(k).pointIndex();
        double def_x = u[k];
        double def_y = u[k+1];

        file << utilities::toString(point_index) << " " << utilities::toString(def_x) << " " << utilities::toString(def_y) << std::endl;
    }

    file.close();
}
