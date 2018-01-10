#include <veamy/problems/VeamyLinearElasticityDiscretization.h>
#include <veamy/models/elements/ElasticityVeamyElement.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/postprocess/utilities/NormResult.h>


VeamyLinearElasticityDiscretization::VeamyLinearElasticityDiscretization(LinearElasticityConditions *conditions)
        : ProblemDiscretization(conditions){
    this->conditions = conditions;
    this->numberDOF = 2;
    this->conditions->material->setMultiplicativeFactor(2);
}

Element<Polygon> *VeamyLinearElasticityDiscretization::createElement(Veamer *v, Polygon &poly, UniqueList<Point> &points) {
    return new ElasticityVeamyElement(conditions, poly, points, v->DOFs, this->numberDOF);
}

Mesh<Polygon> VeamyLinearElasticityDiscretization::initProblemFromFile(Veamer *v, std::string fileName) {
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

    PointConstraint xConstrained (constrainedPointsX, new Constant(0));
    PointConstraint yConstrained (constrainedPointsY, new Constant(0));
    PointConstraint xyConstrained (constrainedPointsXY, new Constant(0));
    conditions->addEssentialConstraint(xConstrained, elasticity_constraints::Direction::Horizontal);
    conditions->addEssentialConstraint(yConstrained, elasticity_constraints::Direction::Vertical);
    conditions->addEssentialConstraint(xyConstrained, elasticity_constraints::Direction::Total);

    NaturalConstraints natural;
    std::getline(infile, line);
    int numberNatural = std::atoi(line.c_str());
    for (int i = 0; i < numberNatural; ++i) {
        std::getline(infile, line);
        std::vector<std::string> splittedLine = utilities::splitBySpaces(line);

        Point p = mesh.getPoint(std::atoi(splittedLine[0].c_str()) - 1);
        PointConstraint xConstraint(p, new Constant(std::atof(splittedLine[1].c_str())));
        PointConstraint yConstraint(p, new Constant(std::atof(splittedLine[2].c_str())));

        conditions->addNaturalConstraint(xConstraint, elasticity_constraints::Direction::Horizontal);
        conditions->addNaturalConstraint(yConstraint, elasticity_constraints::Direction::Vertical);
    }

    infile.close();

    return mesh;
}

NormResult VeamyLinearElasticityDiscretization::computeErrorNorm(NormCalculator<Polygon> *calculator,
                                                                 Mesh<Polygon> mesh) {
    calculator->setCalculator(new VeamyIntegrator<Polygon>, mesh.getPoints().getList());
    calculator->setExtraInformation(this->conditions);

    return calculator->getNorm(mesh);
}
