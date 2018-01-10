#include <vector>
#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleDelaunayGenerator.h>
#include <feamy/Feamer.h>
#include <veamy/models/constraints/values/Function.h>
#include <veamy/physics/materials/MaterialPlaneStrain.h>
#include <feamy/models/constructor/Tri3Constructor.h>
#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include <feamy/problem/FeamyLinearElasticityDiscretization.h>

double uXPatch(double x, double y){
    return x;
}

double uYPatch(double x, double y){
    return x + y;
}

int main() {
    std::vector<Point> region_points = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Region square(region_points);
    square.generateSeedPoints(PointGenerator(functions::constant(), functions::displace_points(0.1)), 10, 10);

    std::vector<Point> seeds = square.getSeedPoints();
    TriangleDelaunayGenerator delaunayGenerator(seeds, square);
    Mesh<Triangle> delaunay = delaunayGenerator.getConformingDelaunayTriangulation();

    delaunay.printInFile("fem_example.txt");

    Material* material = new MaterialPlaneStrain (1, 0.2);
    LinearElasticityConditions* conditions = new LinearElasticityConditions(material);

    Function* uXConstraint = new Function(uXPatch);
    Function* uYConstraint = new Function(uYPatch);

    PointSegment leftSide(Point(0,0), Point(1,0));
    SegmentConstraint leftX (leftSide, delaunay.getPoints(), uXConstraint);
    conditions->addEssentialConstraint(leftX, delaunay.getPoints(), elasticity_constraints::Direction::Horizontal);
    SegmentConstraint  leftY (leftSide, delaunay.getPoints(), uYConstraint);
    conditions->addEssentialConstraint(leftY, delaunay.getPoints(), elasticity_constraints::Direction::Vertical);

    PointSegment downSide(Point(1,0), Point(1,1));
    SegmentConstraint downX (downSide, delaunay.getPoints(), uXConstraint);
    conditions->addEssentialConstraint(downX, delaunay.getPoints(), elasticity_constraints::Direction::Horizontal);
    SegmentConstraint  downY (downSide, delaunay.getPoints(), uYConstraint);
    conditions->addEssentialConstraint(downY, delaunay.getPoints(), elasticity_constraints::Direction::Vertical);

    PointSegment rightSide(Point(1,1), Point(0, 1));
    SegmentConstraint rightX (rightSide, delaunay.getPoints(), uXConstraint);
    conditions->addEssentialConstraint(rightX, delaunay.getPoints(), elasticity_constraints::Direction::Horizontal);
    SegmentConstraint  rightY (rightSide, delaunay.getPoints(), uYConstraint);
    conditions->addEssentialConstraint(rightY, delaunay.getPoints(), elasticity_constraints::Direction::Vertical);

    PointSegment topSide(Point(0, 1), Point(0, 0));
    SegmentConstraint topX (topSide, delaunay.getPoints(), uXConstraint);
    conditions->addEssentialConstraint(topX, delaunay.getPoints(), elasticity_constraints::Direction::Horizontal);
    SegmentConstraint  topY (topSide, delaunay.getPoints(), uYConstraint);
    conditions->addEssentialConstraint(topY, delaunay.getPoints(), elasticity_constraints::Direction::Vertical);

    FeamyElementConstructor* constructor = new Tri3Constructor();

    FeamyLinearElasticityDiscretization* problem = new FeamyLinearElasticityDiscretization(conditions);
    Feamer feamer(problem);
    feamer.initProblem(delaunay, constructor);

    Eigen::VectorXd x = feamer.simulate(delaunay);
    feamer.writeDisplacements("femresults.txt", x);
}