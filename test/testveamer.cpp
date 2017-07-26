#include <gtest/gtest.h>
#include <veamy/models/constraints/Constraint.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/Veamer.h>
#include <mesher/models/Region.h>
#include <mesher/models/generator/functions.h>
#include <mesher/voronoi/TriangleMeshGenerator.h>
#include <veamy/models/constraints/values/Function.h>

double tangencial(double x, double y){
    double P = -1000;
    double D =  4;
    double I = std::pow(D,3)/12;

    return P/(2*I)*(std::pow(D,2)/4-std::pow(y,2));
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



TEST(VeamerTest, OnlyEssentialTest){
    Veamer v;
    std::vector<Point> points = {Point(0,0), Point(2,0), Point(2,1), Point(0,1)};
    Region region(points);
    region.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);

    std::vector<Point> seeds = region.getSeedPoints();
    TriangleMeshGenerator g(seeds, region);
    PolygonalMesh m = g.getMesh();
    m.printInFile("first.txt");

    EssentialConstraints c;
    PointSegment constrained(Point(0,0),Point(0,1));
    PointSegment constrained2 (Point(2,0),Point(2,1));
    Constraint const1 (constrained, m.getPoints(), Constraint::Direction::Total, new Constant(0));

    c.addConstraint(const1, m.getPoints());
    Constraint const2 (constrained2, m.getPoints(), Constraint::Direction::Horizontal, new Constant(1));
    c.addConstraint(const2, m.getPoints());

   /* NaturalConstraints n;
    PointSegment const3(Point(0,0),Point(2,0));
    Constraint constraint3(const3,m.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(2));
    n.addConstraint(constraint3, m.getPoints().getList());*/

    ConstraintsContainer container;
    container.addConstraints(c, m);
    // container.addConstraints(n,m);

    ProblemConditions conditions(container, Material(Materials::material::Steel));

    v.initProblem(m, conditions);

    Eigen::VectorXd x = v.simulate(m);
    m.printInFile("second.txt");
}

TEST(VeamerTest, OnlyNaturalTest){
    Veamer v;
    std::vector<Point> points = {Point(0,0), Point(2,0), Point(2,1), Point(0,1)};
    Region region(points);
    region.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 3, 3);

    std::vector<Point> seeds = region.getSeedPoints();
    TriangleMeshGenerator g(seeds, region);
    PolygonalMesh m = g.getMesh();
    m.printInFile("first.txt");

    EssentialConstraints c;
    PointSegment constrained(Point(0,0),Point(0,1));
    Constraint const1 (constrained, m.getPoints(), Constraint::Direction::Total, new Constant(0));

    c.addConstraint(const1, m.getPoints().getList());

    NaturalConstraints n;
    PointSegment const3(Point(2,0),Point(2,1));
    Constraint constraint3(const3,m.getPoints(), Constraint::Direction::Horizontal, new Constant(1000));
    n.addConstraint(constraint3, m.getPoints());

    ConstraintsContainer container;
    container.addConstraints(c, m);
    container.addConstraints(n,m);

    ProblemConditions conditions(container,  Material(Materials::material::Steel));

    v.initProblem(m, conditions);

    Eigen::VectorXd x = v.simulate(m);
    //std::cout << x << std::endl;
    m.printInFile("second.txt");
}

TEST(VeamerTest, OnlyBodyForceTest){
    Veamer v;
    std::vector<Point> points = {Point(0,0), Point(2,0), Point(2,1), Point(0,1)};
    Region region(points);
    region.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 3, 3);

    class Sum : public VariableBodyForce{
    private:
        double applyX(double x, double y) override {
            return 1;
        }

        double applyY(double x, double y) override {
            return 0;
        }
    };

    VariableBodyForce* f = new Sum();

    std::vector<Point> seeds = region.getSeedPoints();
    TriangleMeshGenerator g(seeds, region);
    PolygonalMesh m = g.getMesh();
    m.printInFile("first.txt");

    EssentialConstraints c;
    PointSegment constrained(Point(0,0),Point(0,1));
    Constraint const1 (constrained, m.getPoints(), Constraint::Direction::Total, new Constant(0));

    c.addConstraint(const1, m.getPoints());

    ConstraintsContainer container;
    container.addConstraints(c, m);

    ProblemConditions conditions(container, f, Material(Materials::material::Steel));

    v.initProblem(m, conditions);

    Eigen::VectorXd x = v.simulate(m);
    std::cout << x << std::endl;
    m.printInFile("second.txt");
}

TEST(VeamerTest, MeshFromFileTest){
    PolygonalMesh mesh;
    mesh.createFromFile("SquareWithHoleMesh.txt");

    Veamer v;
}

TEST(VeamerTest, ParabolicBeamExampleTest){
    std::vector<Point> rectangle4x8_points = {Point(0, -2), Point(8, -2), Point(8, 2), Point(0, 2)};
    Region rectangle4x8(rectangle4x8_points);
    rectangle4x8.generateSeedPoints(PointGenerator(functions::constantAlternating(), functions::constant()), 12, 6);

    std::vector<Point> seeds = rectangle4x8.getSeedPoints();
    TriangleMeshGenerator meshGenerator = TriangleMeshGenerator (seeds, rectangle4x8);
    PolygonalMesh mesh = meshGenerator.getMesh();
    mesh.printInFile("rectangle4x8ConstantAlternating.txt");

    Veamer v;

    EssentialConstraints essential;
    Function* uXConstraint = new Function(uX);
    Function* uYConstraint = new Function(uY);

    PointSegment leftSide(Point(0,-2), Point(0,2));
    Constraint const1 (leftSide, mesh.getPoints(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(const1, mesh.getPoints());

    Constraint const2 (leftSide, mesh.getPoints(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(const2, mesh.getPoints());

    NaturalConstraints natural;

    Function* tangencialLoad = new Function(tangencial);
    PointSegment rightSide(Point(8,-2), Point(8,2));

    Constraint const3 (rightSide, mesh.getPoints(), Constraint::Direction::Vertical, tangencialLoad);
    natural.addConstraint(const3, mesh.getPoints());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);
    container.addConstraints(natural, mesh);

    Material m(1e7, 0.3);
    ProblemConditions conditions(container, m);

    v.initProblem(mesh, conditions);

    Eigen::VectorXd x = v.simulate(mesh);
    std::string fileName = "displacement.txt";
    v.writeDisplacements(fileName, x);


}