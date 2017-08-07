#include <veamy/Veamer.h>
#include <iomanip>
#include <veamy/models/constraints/values/Constant.h>

Veamer::Veamer() {}

PolygonalMesh Veamer::initProblemFromFile(std::string fileName, Material material) {
    return initProblemFromFile(fileName, material, new None());
}

PolygonalMesh Veamer::initProblemFromFile(std::string fileName, Material material, BodyForce *force) {
    PolygonalMesh mesh;
    std::string completeName = utilities::getPath() + fileName;
    std::ifstream infile(completeName);

    mesh.createFromStream(infile);

    EssentialConstraints essential;
    std::vector<Point> constrainedPointsX;
    std::vector<Point> constrainedPointsY;
    std::vector<Point> constrainedPointsXY;

    std::string line;
    std::getline(infile, line);
    int numberEssential = std::atoi(line.c_str());
    for (int i = 0; i < numberEssential; ++i) {
        std::getline(infile, line);
        std::vector<std::string> splittedLine = utilities::split(line, ' ');

        if(splittedLine[1] == "1" && splittedLine[2] == "1"){
            Point p = mesh.getPoint(std::atoi(splittedLine[0].c_str()) - 1);
            constrainedPointsXY.push_back(p);
        }

        if(splittedLine[1] == "1" && splittedLine[2] == "0"){
            Point p = mesh.getPoint(std::atoi(splittedLine[0].c_str()) - 1);
            constrainedPointsX.push_back(p);
        }

        if(splittedLine[1] == "0" && splittedLine[2] == "1"){
            Point p = mesh.getPoint(std::atoi(splittedLine[0].c_str()) - 1);
            constrainedPointsY.push_back(p);
        }
    }

    PointConstraint xConstrained (constrainedPointsX, Constraint::Direction::Horizontal, new Constant(0));
    PointConstraint yConstrained (constrainedPointsY, Constraint::Direction::Vertical, new Constant(0));
    PointConstraint xyConstrained (constrainedPointsXY, Constraint::Direction::Total, new Constant(0));
    essential.addConstraint(xConstrained);
    essential.addConstraint(yConstrained);
    essential.addConstraint(xyConstrained);

    NaturalConstraints natural;
    std::getline(infile, line);
    int numberNatural = std::atoi(line.c_str());
    for (int i = 0; i < numberNatural; ++i) {
        std::getline(infile, line);
        std::vector<std::string> splittedLine = utilities::split(line, ' ');

        Point p = mesh.getPoint(std::atoi(splittedLine[0].c_str()) - 1);
        PointConstraint xConstraint(p, Constraint::Direction::Horizontal, new Constant(std::atof(splittedLine[1].c_str())));
        PointConstraint yConstraint(p, Constraint::Direction::Vertical, new Constant(std::atof(splittedLine[2].c_str())));

        natural.addConstraint(xConstraint);
        natural.addConstraint(yConstraint);
    }

    infile.close();
    ConstraintsContainer container;
    container.addConstraints(natural, mesh);
    container.addConstraints(essential, mesh);

    ProblemConditions conditions(container, force, material);
    initProblem(mesh, conditions);

    return mesh;
}


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
    Eigen::MatrixXd K, Ks;
    Eigen::VectorXd f;
    int n = this->DOFs.size();

    K = Eigen::MatrixXd::Zero(n,n);
    Ks = Eigen::MatrixXd::Zero(n,n);
    f = Eigen::VectorXd::Zero(n);

    for(int i=0;i<elements.size();i++){
        elements[i].computeK(DOFs, this->points, conditions);
        elements[i].computeF(DOFs, this->points, conditions);
        elements[i].assemble(DOFs, K, f);
    }

    //std::cout << K << std::endl;

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
    path = path  + "\\" + fileName;

    std::ofstream file;
    file.open(path, std::ios::out);
    file << std::fixed;
    file << std::setprecision(20);

    std::vector<std::string> results(this->points.size());

    for (int k = 0; k < u.rows(); k = k + 2) {
        int point_index = DOFs.get(k).pointIndex();
        double def_x = u[k];
        double def_y = u[k+1];

        results[point_index] = utilities::toString(point_index) + " " + utilities::toString(def_x) + " "
                               + utilities::toString(def_y);
    }

    for (std::string s: results){
        file << s << std::endl;
    }

    file.close();
}
