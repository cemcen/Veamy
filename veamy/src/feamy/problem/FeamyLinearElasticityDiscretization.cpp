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
    Mesh<Triangle> mesh;
    std::ifstream infile = utilities::openFile(fileName);

    mesh.createFromStream(infile, 1);

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

NormResult
FeamyLinearElasticityDiscretization::computeErrorNorm(NormCalculator<Triangle> *calculator, Mesh<Triangle> mesh, Feamer* f) {
    FeamyAdditionalInfo info(f->getElements(), mesh.getPoints().getList());

    calculator->setCalculator(new FeamyIntegrator<Triangle>, info);
    calculator->setExtraInformation(this->conditions);

    return calculator->getNorm(mesh);
}
