#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleDelaunayGenerator.h>
#include <veamy/models/constraints/EssentialConstraints.h>
#include <veamy/models/constraints/values/Function.h>
#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/physics/conditions/Conditions.h>
#include <veamy/physics/materials/MaterialPlaneStrain.h>
#include <feamy/Feamer.h>
#include <feamy/models/constructor/Tri3Constructor.h>
#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include <feamy/problem/FeamyLinearElasticityDiscretization.h>

double tangencial(double x, double y){
    double P = -1000;
    double D =  4;
    double I = std::pow(D,3)/12;
    double value = std::pow(D,2)/4-std::pow(y,2);
    return P/(2*I)*value;
}

double uX(double x, double y){
    double P = -1000;
    double Ebar = 1e7/(1 - std::pow(0.3,2));
    double vBar = 0.3/(1 - 0.3);
    double D = 4;
    double L = 8;
    double I = std::pow(D,3)/12;
    return -P*y/(6*Ebar*I)*((6*L - 3*x)*x + (2+vBar)*std::pow(y,2) - 3*std::pow(D,2)/2*(1+vBar));
}

double uY(double x, double y){
    double P = -1000;
    double Ebar = 1e7/(1 - std::pow(0.3,2));
    double vBar = 0.3/(1 - 0.3);
    double D = 4;
    double L = 8;
    double I = std::pow(D,3)/12;
    return P/(6*Ebar*I)*(3*vBar*std::pow(y,2)*(L-x) + (3*L-x)*std::pow(x,2));
}

int main(){
    std::vector<Point> rectangle4x8_points = {Point(0, -2), Point(8, -2), Point(8, 2), Point(0, 2)};
    Region rectangle4x8(rectangle4x8_points);
    rectangle4x8.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 24, 12);

    std::vector<Point> seeds = rectangle4x8.getSeedPoints();
    TriangleDelaunayGenerator generator(seeds, rectangle4x8);

    Mesh<Triangle> mesh = generator.getConformingDelaunayTriangulation();
    mesh.printInFile("parabolic_fem_mesh.txt");

    Material* material = new MaterialPlaneStrain (1e7, 0.3);
    LinearElasticityConditions* conditions = new LinearElasticityConditions(material);

    Function* uXConstraint = new Function(uX);
    Function* uYConstraint = new Function(uY);

    PointSegment leftSide(Point(0,-2), Point(0,2));
    SegmentConstraint const1 (leftSide, mesh.getPoints(), uXConstraint);
    conditions->addEssentialConstraint(const1, mesh.getPoints(), elasticity_constraints::Direction::Horizontal);

    SegmentConstraint const2 (leftSide, mesh.getPoints(), uYConstraint);
    conditions->addEssentialConstraint(const2, mesh.getPoints(), elasticity_constraints::Direction::Vertical);

    Function* tangencialLoad = new Function(tangencial);
    PointSegment rightSide(Point(8,-2), Point(8,2));

    SegmentConstraint const3 (rightSide, mesh.getPoints(), tangencialLoad);
    conditions->addNaturalConstraint(const3, mesh.getPoints(), elasticity_constraints::Direction::Vertical);

    FeamyLinearElasticityDiscretization* problem = new FeamyLinearElasticityDiscretization(conditions);

    Feamer feamer(problem);
    feamer.initProblem(mesh, new Tri3Constructor());
    Eigen::VectorXd x = feamer.simulate(mesh);
    feamer.writeDisplacements("parabolic_fem_results.txt", x);
}