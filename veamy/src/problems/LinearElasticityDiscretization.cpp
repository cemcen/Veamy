#include <veamy/problems/LinearElasticityDiscretization.h>
#include <veamy/models/elements/ElasticityVeamyElement.h>
#include <veamy/models/constraints/values/Constant.h>

LinearElasticityDiscretization::LinearElasticityDiscretization(LinearElasticityConditions *conditions)
        : ProblemDiscretization(conditions){
    this->conditions = conditions;
    this->numberDOF = 2;
}

Element *LinearElasticityDiscretization::createElement(Veamer *v, Polygon &poly, UniqueList<Point> &points) {
    return new ElasticityVeamyElement(conditions, poly, points, v->DOFs, this->numberDOF);
}

Element *LinearElasticityDiscretization::createElement(Feamer *f, Triangle &poly, UniqueList<Point> &points) {
    return nullptr;
}

Mesh<Polygon> LinearElasticityDiscretization::initProblemFromFile(Veamer *v, std::string fileName) {
    Mesh<Polygon> mesh;
    std::ifstream infile = utilities::openFile(fileName);

    mesh.createFromStream(infile, 0);

    EssentialConstraints essential;
    std::vector<Point> constrainedPointsX;
    std::vector<Point> constrainedPointsY;
    std::vector<Point> constrainedPointsXY;

    std::string line;
    std::getline(infile, line);
    int numberEssential = std::atoi(line.c_str());
    for (int i = 0; i < numberEssential; ++i) {
        std::getline(infile, line);
        std::vector<std::string> splittedLine = utilities::splitBySpaces(line);

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
        std::vector<std::string> splittedLine = utilities::splitBySpaces(line);

        Point p = mesh.getPoint(std::atoi(splittedLine[0].c_str()) - 1);
        PointConstraint xConstraint(p, Constraint::Direction::Horizontal, new Constant(std::atof(splittedLine[1].c_str())));
        PointConstraint yConstraint(p, Constraint::Direction::Vertical, new Constant(std::atof(splittedLine[2].c_str())));

        natural.addConstraint(xConstraint);
        natural.addConstraint(yConstraint);
    }

    infile.close();
    ConstraintsContainer container;
    container.addConstraints(natural, mesh.getPoints());
    container.addConstraints(essential, mesh.getPoints());

    this->conditions->constraints = container;
    return mesh;
}
