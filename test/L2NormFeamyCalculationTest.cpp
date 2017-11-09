#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleDelaunayGenerator.h>
#include <feamy/Feamer.h>
#include <veamy/models/constraints/values/Function.h>
#include <veamy/physics/materials/MaterialPlaneStrain.h>
#include <feamy/models/constructor/Tri3Constructor.h>
#include <veamy/postprocess/L2NormCalculator.h>

double uXPatch(double x, double y){
    return x;
}

double uYPatch(double x, double y){
    return x + y;
}

Pair<double> analyticSolution(double x, double y){
    return Pair<double>(x, x+y);
}

int main() {
    std::vector<Point> region_points = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Region square(region_points);
    square.generateSeedPoints(PointGenerator(functions::constant(), functions::displace_points(0.3)), 3, 3);

    std::vector<Point> seeds = square.getSeedPoints();
    TriangleDelaunayGenerator delaunayGenerator(square, seeds);
    Mesh<Triangle> delaunay = delaunayGenerator.getConformingDelaunayTriangulation();

    delaunay.printInFile("fem_example.txt");

    Feamer feamer;
    EssentialConstraints essential;
    Function* uXConstraint = new Function(uXPatch);
    Function* uYConstraint = new Function(uYPatch);

    PointSegment leftSide(Point(0,0), Point(1,0));
    SegmentConstraint leftX (leftSide, delaunay.getPoints(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(leftX, delaunay.getPoints());
    SegmentConstraint  leftY (leftSide, delaunay.getPoints(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(leftY, delaunay.getPoints());

    PointSegment downSide(Point(1,0), Point(1,1));
    SegmentConstraint downX (downSide, delaunay.getPoints(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(downX, delaunay.getPoints());
    SegmentConstraint  downY (downSide, delaunay.getPoints(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(downY, delaunay.getPoints());

    PointSegment rightSide(Point(1,1), Point(0, 1));
    SegmentConstraint rightX (rightSide, delaunay.getPoints(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(rightX, delaunay.getPoints());
    SegmentConstraint  rightY (rightSide, delaunay.getPoints(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(rightY, delaunay.getPoints());

    PointSegment topSide(Point(0, 1), Point(0, 0));
    SegmentConstraint topX (topSide, delaunay.getPoints(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(topX, delaunay.getPoints());
    SegmentConstraint  topY (topSide, delaunay.getPoints(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(topY, delaunay.getPoints());

    ConstraintsContainer container;
    container.addConstraints(essential, delaunay.getPoints());

    Material* material = new MaterialPlaneStrain(1, 0.2);
    Conditions conditions(container, material);

    FeamyElementConstructor* constructor = new Tri3Constructor();
    feamer.initProblem(delaunay, conditions, constructor);

    Eigen::VectorXd x = feamer.simulate(delaunay);
    feamer.writeDisplacements("femresults.txt", x);

    DisplacementValue* realSolution = new DisplacementValue(analyticSolution);
    L2NormCalculator<Triangle>* l2 = new L2NormCalculator<Triangle>(realSolution, x, feamer.DOFs);
    double norm = feamer.computeErrorNorm(l2, delaunay);
    std::cout << norm;
}