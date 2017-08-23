
#include <mesher/voronoi/TriangleMeshGenerator.h>
#include <veamy/Veamer.h>
#include <veamy/models/constraints/values/Function.h>
#include <mesher/models/generator/functions.h>

double uXPatch(double x, double y){
    return x;
}

double uYPatch(double x, double y){
    return x + y;
}

int main(){
    std::vector<Point> rectangle4x8_points = {Point(0, -2), Point(8, -2), Point(8, 2), Point(0, 2)};
    Region rectangle4x8(rectangle4x8_points);
    rectangle4x8.generateSeedPoints(PointGenerator(functions::constantAlternating(), functions::constant()), 24, 12);

    std::vector<Point> seeds = rectangle4x8.getSeedPoints();
    TriangleMeshGenerator meshGenerator = TriangleMeshGenerator (seeds, rectangle4x8);
    PolygonalMesh mesh = meshGenerator.getMesh();
    mesh.printInFile("rectangle4x8ConstantAlternating.txt");

    Veamer v;

    EssentialConstraints essential;
    Function* uXConstraint = new Function(uXPatch);
    Function* uYConstraint = new Function(uYPatch);

    PointSegment leftSide(Point(0,-2), Point(0,2));
    SegmentConstraint leftX (leftSide, mesh.getPoints(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(leftX, mesh.getPoints());
    SegmentConstraint  leftY (leftSide, mesh.getPoints(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(leftY, mesh.getPoints());

    PointSegment downSide(Point(0,-2), Point(8,-2));
    SegmentConstraint downX (downSide, mesh.getPoints(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(downX, mesh.getPoints());
    SegmentConstraint  downY (downSide, mesh.getPoints(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(downY, mesh.getPoints());

    PointSegment rightSide(Point(8,-2), Point(8, 2));
    SegmentConstraint rightX (rightSide, mesh.getPoints(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(rightX, mesh.getPoints());
    SegmentConstraint  rightY (rightSide, mesh.getPoints(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(rightY, mesh.getPoints());

    PointSegment topSide(Point(0, 2), Point(8, 2));
    SegmentConstraint topX (topSide, mesh.getPoints(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(topX, mesh.getPoints());
    SegmentConstraint  topY (topSide, mesh.getPoints(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(topY, mesh.getPoints());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);

    Material m(1e7, 0.3);
    ProblemConditions conditions(container, m);

    v.initProblem(mesh, conditions);

    Eigen::VectorXd x = v.simulate(mesh);
    //By default, the file is created in home/, to create somewhere else, for example, /home/user/Documents/Veamy,
    //create the fileName variable as "/Documents/Veamy/displacement.txt"
    std::string fileName = "displacement.txt";
    v.writeDisplacements(fileName, x);
}