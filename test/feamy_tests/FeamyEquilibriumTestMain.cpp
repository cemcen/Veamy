#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleDelaunayGenerator.h>
#include <feamy/Feamer.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/physics/materials/MaterialPlaneStress.h>
#include <feamy/models/constructor/Tri3Constructor.h>
#include <veamy/config/VeamyConfig.h>
#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include <feamy/problem/FeamyLinearElasticityDiscretization.h>

int main(){
    VeamyConfig::instance()->setPrecision(Precision::precision::large);

    std::vector<Point> region_points = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Region square(region_points);
    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 6, 6);

    std::vector<Point> seeds = square.getSeedPoints();
    TriangleDelaunayGenerator delaunayGenerator(seeds, square);
    Mesh<Triangle> delaunay = delaunayGenerator.getConformingDelaunayTriangulation();

    delaunay.printInFile("fem_eq_mesh.txt");

    Material* material = new MaterialPlaneStress(3e7, 0.3);
    LinearElasticityConditions* conditions = new LinearElasticityConditions(material);

    PointSegment downSide(Point(0,0), Point(1,0));
    SegmentConstraint down (downSide, delaunay.getPoints(),  new Constant(0));
    conditions->addEssentialConstraint(down, delaunay.getPoints(), elasticity_constraints::Direction::Vertical);
    Point cornerPoint(Point(1,0));
    PointConstraint corner(cornerPoint, new Constant(0));
    conditions->addEssentialConstraint(corner, elasticity_constraints::Direction::Horizontal);

    PointSegment topSide(Point(0,1), Point(1,1));
    SegmentConstraint top (topSide, delaunay.getPoints(), new Constant(1));
    conditions->addNaturalConstraint(top, delaunay.getPoints(), elasticity_constraints::Direction::Vertical);

    FeamyLinearElasticityDiscretization* problem = new FeamyLinearElasticityDiscretization(conditions);
    Feamer feamer(problem);
    feamer.initProblem(delaunay, new Tri3Constructor());

    Eigen::VectorXd x = feamer.simulate(delaunay);

    feamer.writeDisplacements("fem_eq_results.txt", x);
}