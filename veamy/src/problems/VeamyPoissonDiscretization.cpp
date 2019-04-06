#include <veamy/problems/VeamyPoissonDiscretization.h>
#include <veamy/models/elements/PoissonVeamyElement.h>
#include <veamy/postprocess/calculators/VeamyPoissonDisplacementCalculator.h>
#include <veamy/postprocess/constructors/PoissonConstructor.h>
#include <veamy/models/constraints/values/Constant.h>

VeamyPoissonDiscretization::VeamyPoissonDiscretization(PoissonConditions *conditions) : ProblemDiscretization(conditions){
    this->conditions = conditions;
    this->numberDOF = 1;
}

Element<Polygon> *VeamyPoissonDiscretization::createElement(Veamer *v, Polygon &poly, UniqueList<Point> &points) {
    return new PoissonVeamyElement(this->conditions, poly, points, v->DOFs, this->numberDOF);
}

Mesh<Polygon> VeamyPoissonDiscretization::initProblemFromFile(std::string fileName) {
    Mesh<Polygon> mesh;
    std::ifstream infile = utilities::openFile(fileName);

    mesh.createFromStream(infile, 1);

    std::string line;
    std::getline(infile, line);
    int numberEssential = std::atoi(line.c_str());
    for (int i = 0; i < numberEssential; ++i) {
        std::getline(infile, line);
        std::vector<std::string> splittedLine = utilities::splitBySpaces(line);

        Point p = mesh.getPoint(std::atoi(splittedLine[0].c_str()) - 1);
        PointConstraint constrainedPoint(p, new Constant(std::atof(splittedLine[1].c_str())));
        this->conditions->addEssentialConstraint(constrainedPoint);
    }

    std::getline(infile, line);
    int numberNatural = std::atoi(line.c_str());
    for (int i = 0; i < numberNatural; ++i) {
        std::getline(infile, line);
        std::vector<std::string> splittedLine = utilities::splitBySpaces(line);

        int p1 = std::atoi(splittedLine[0].c_str()) - 1;
        int p2 = std::atoi(splittedLine[1].c_str()) - 1;

        IndexSegment segment(p1, p2);

        SegmentConstraint constrainedSegment(segment, new Constant(std::atof(splittedLine[2].c_str())));

        this->conditions->addNaturalConstraint(constrainedSegment, mesh.getPoints());
    }

    infile.close();
    return mesh;
}

NormResult
VeamyPoissonDiscretization::computeErrorNorm(NormCalculator<Polygon> *calculator, Mesh<Polygon>& mesh, Veamer *solver) {
    CalculatorConstructor<Polygon>* constructor = new PoissonConstructor<Polygon>(solver->DOFs, calculator->getNodalDisplacements());
    calculator->setCalculator(new VeamyIntegrator<Polygon>, constructor, mesh.getPoints().getList());

    calculator->setExtraInformation(this->conditions);

    return calculator->getNorm(mesh);
}
