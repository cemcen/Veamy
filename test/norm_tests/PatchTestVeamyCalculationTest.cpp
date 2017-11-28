#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleDelaunayGenerator.h>
#include <veamy/models/constraints/values/Function.h>
#include <veamy/physics/materials/MaterialPlaneStrain.h>
#include <veamy/postprocess/L2NormCalculator.h>
#include <veamy/Veamer.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <veamy/postprocess/analytic/StrainValue.h>
#include <veamy/postprocess/analytic/StressValue.h>
#include <veamy/postprocess/H1NormCalculator.h>

double uXPatch(double x, double y){
    return x;
}

double uYPatch(double x, double y){
    return x + y;
}

Pair<double> analyticSolution(double x, double y){
    return Pair<double>(x, x+y);
}

Trio<double> strain(double x, double y){
    return Trio<double>(1,1,1);
}

Trio<double> stress(double x, double y){
    double E = 1;
    double v = 0.2;

    double constant = E/((1+v)*(1-2*v));

    return Trio<double>(constant, constant, constant*(1-2*v)/2);
}


int main() {
    std::vector<Point> region_points = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Region square(region_points);
    int n = 5;
    square.generateSeedPoints(PointGenerator(functions::constantAlternating(), functions::constant()), n , n);

    std::vector<Point> seeds = square.getSeedPoints();
    TriangleVoronoiGenerator generator (seeds, square);
    Mesh<Polygon> mesh = generator.getMesh();

    mesh.printInFile("mesh_vem.txt");

    Veamer veamer;
    EssentialConstraints essential;
    Function* uXConstraint = new Function(uXPatch);
    Function* uYConstraint = new Function(uYPatch);

    PointSegment leftSide(Point(0,0), Point(1,0));
    SegmentConstraint leftX (leftSide, mesh.getPoints(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(leftX, mesh.getPoints());
    SegmentConstraint  leftY (leftSide, mesh.getPoints(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(leftY, mesh.getPoints());

    PointSegment downSide(Point(1,0), Point(1,1));
    SegmentConstraint downX (downSide, mesh.getPoints(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(downX, mesh.getPoints());
    SegmentConstraint  downY (downSide, mesh.getPoints(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(downY, mesh.getPoints());

    PointSegment rightSide(Point(1,1), Point(0, 1));
    SegmentConstraint rightX (rightSide, mesh.getPoints(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(rightX, mesh.getPoints());
    SegmentConstraint  rightY (rightSide, mesh.getPoints(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(rightY, mesh.getPoints());

    PointSegment topSide(Point(0, 1), Point(0, 0));
    SegmentConstraint topX (topSide, mesh.getPoints(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(topX, mesh.getPoints());
    SegmentConstraint  topY (topSide, mesh.getPoints(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(topY, mesh.getPoints());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh.getPoints());

    Material* material = new MaterialPlaneStrain(1, 0.2);
    Conditions conditions(container, material);

    veamer.initProblem(mesh, conditions);

    Eigen::VectorXd x = veamer.simulate(mesh);
    veamer.writeDisplacements("vemresults.txt", x);

    DisplacementValue* realSolution = new DisplacementValue(analyticSolution);
    L2NormCalculator<Polygon>* l2 = new L2NormCalculator<Polygon>(realSolution, x, veamer.DOFs);
    double norm = veamer.computeErrorNorm(l2, mesh);
    std::cout << "L2 norm: " << norm << std::endl;

    StrainValue* strainValue = new StrainValue(strain);
    StressValue* stressValue = new StressValue(stress);

    H1NormCalculator<Polygon>* h1 = new H1NormCalculator<Polygon>(strainValue, stressValue, realSolution, x, veamer.DOFs, mesh.getPoints().getList());
    double h1norm = veamer.computeErrorNorm(h1, mesh);
    std::cout << "H1 norm: " << h1norm << std::endl;
}