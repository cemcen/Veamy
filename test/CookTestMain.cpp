#include <vector>
#include <mesher/models/basic/Point.h>
#include <mesher/models/Region.h>
#include <mesher/models/hole/CircularHole.h>
#include <mesher/models/generator/functions.h>
#include <mesher/voronoi/TriangleMeshGenerator.h>
#include <veamy/Veamer.h>
#include <veamy/models/constraints/values/Constant.h>

int main(){
    std::vector<Point> TBeam_points = {Point(0,0), Point(48,44), Point(48,64), Point(0,44)};
    Region TBeam(TBeam_points);

    Hole hole1 = CircularHole(Point(8,28), 5);
    Hole hole2 = CircularHole(Point(24,38), 5);
    Hole hole3 = CircularHole(Point(40,48), 5);
    TBeam.addHole(hole1);
    TBeam.addHole(hole2);
    TBeam.addHole(hole3);

    TBeam.printInFile("TBeam_region.txt");
    TBeam.generateSeedPoints(PointGenerator(functions::constantAlternating(), functions::constant()), 10, 10);
    std::vector<Point> seeds = TBeam.getSeedPoints();
    TriangleMeshGenerator g(seeds, TBeam);
    PolygonalMesh mesh = g.getMesh();
    mesh.printInFile("TBeam.txt");

    Veamer v;
    EssentialConstraints essential;
    PointSegment leftSide(Point(0,0), Point(0,44));
    SegmentConstraint left(leftSide, mesh.getPoints(), Constraint::Direction::Total, new Constant(0));
    essential.addConstraint(left, mesh.getPoints());

    NaturalConstraints natural;
    PointSegment rightSide(Point(48,44), Point(48,64));
    SegmentConstraint right(rightSide, mesh.getPoints(), Constraint::Direction::Vertical, new Constant(100));
    natural.addConstraint(right, mesh.getPoints());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);
    container.addConstraints(natural, mesh);

    Material material(1e7, 0.3);
    ProblemConditions conditions(container, material);

    v.initProblem(mesh, conditions);
    Eigen::VectorXd x = v.simulate(mesh);
    std::string fileName = "CookTest.txt";
    v.writeDisplacements(fileName, x);
}