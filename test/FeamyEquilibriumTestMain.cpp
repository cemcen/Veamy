#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleDelaunayGenerator.h>
#include <feamy/Feamer.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/physics/materials/MaterialPlaneStress.h>
#include <feamy/models/constructor/Tri3Constructor.h>

int main(){
    VeamyConfig::instance()->setPrecision(Precision::precision::large);

    std::vector<Point> region_points = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Region square(region_points);
    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 6, 6);

    std::vector<Point> seeds = square.getSeedPoints();
    TriangleDelaunayGenerator delaunayGenerator(square, seeds);
    Mesh<Triangle> delaunay = delaunayGenerator.getDelaunayTriangulation();

    delaunay.printInFile("fem_eq_mesh.txt");

    LinearElasticityConditions* conditions = new LinearElasticityConditions();

    Feamer feamer;

    EssentialConstraints essential;
    PointSegment downSide(Point(0,0), Point(1,0));
    SegmentConstraint down (downSide, delaunay.getPoints(), Constraint::Direction::Vertical, new Constant(0));
    essential.addConstraint(down, delaunay.getPoints());
    Point cornerPoint(Point(1,0));
    PointConstraint corner(cornerPoint, Constraint::Direction::Horizontal, new Constant(0));
    essential.addConstraint(corner);

    NaturalConstraints natural;
    PointSegment topSide(Point(0,1), Point(1,1));
    SegmentConstraint top (topSide, delaunay.getPoints(), Constraint::Direction::Vertical, new Constant(1));
    natural.addConstraint(top, delaunay.getPoints());

    ConstraintsContainer container;
    container.addConstraints(essential, delaunay.getPoints());
    container.addConstraints(natural, delaunay.getPoints());

    Material* material = new MaterialPlaneStress(3e7, 0.3);
    Conditions conditions(container, material);

    feamer.initProblem(delaunay, conditions, new Tri3Constructor());
    Eigen::VectorXd x = feamer.simulate(delaunay);

    feamer.writeDisplacements("fem_eq_results.txt", x);
}