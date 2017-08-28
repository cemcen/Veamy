#include <mesher/models/basic/Point.h>
#include <mesher/models/Region.h>
#include <mesher/models/generator/functions.h>
#include <mesher/voronoi/TriangleMeshGenerator.h>
#include <veamy/Veamer.h>
#include <veamy/models/constraints/values/Constant.h>

int main(){
    std::vector<Point> unicorn_points = {Point(2,0), Point(3,0.5), Point(3.5,2), Point(4,4), Point(6,4), Point(8.5,4),
                                         Point(9,2), Point(9.5,0.5), Point(10,0), Point(10.5,0.5), Point(11.2,2.5),
                                         Point(11.5,4.5), Point(11.8,8.75), Point(11.8,11.5), Point(13.5,11), Point(14.5,11.2),
                                         Point(15,12), Point(15,13), Point(15,14.5), Point(14,16.5), Point(15,19.5), Point(15.2,20),
                                         Point(14.5,19.7), Point(11.8,18.2), Point(10.5,18.3), Point(10,18), Point(8,16),
                                         Point(7.3,15.3), Point(7,13.8), Point(6.7,11.5), Point(3.3,11.3), Point(1,10.5),
                                         Point(0.4,8.8), Point(0.3,6.8), Point(0.4,4), Point(0.8,2.1), Point(1.3,0.4)};
    Region unicorn(unicorn_points);
    unicorn.generateSeedPoints(PointGenerator(functions::constantAlternating(), functions::constant()), 5, 5);
    std::vector<Point> seeds = unicorn.getSeedPoints();
    TriangleMeshGenerator g(seeds, unicorn);
    PolygonalMesh mesh = g.getMesh();
    mesh.printInFile("unicornMesh.txt");

    Veamer v;
    EssentialConstraints essential;
    Point leftFoot(2,0);
    PointConstraint left(leftFoot, Constraint::Direction::Total, new Constant(0));
    Point rightFoot(10,0);
    PointConstraint right(rightFoot, Constraint::Direction::Total, new Constant(0));
    essential.addConstraint(left);
    essential.addConstraint(right);

    NaturalConstraints natural;
    PointSegment backSegment(Point(6.7,11.5), Point(3.3,11.3));
    SegmentConstraint back (backSegment, mesh.getPoints(), Constraint::Direction::Total, new Constant(-100));
    natural.addConstraint(back, mesh.getPoints());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);
    container.addConstraints(natural, mesh);

    Material* material = new MaterialPlaneStrain (1e7, 0.3);
    ProblemConditions conditions(container, material);

    v.initProblem(mesh, conditions);
    Eigen::VectorXd x = v.simulate(mesh);
    std::string fileName = "unicornLoadTest.txt";
    v.writeDisplacements(fileName, x);
}



