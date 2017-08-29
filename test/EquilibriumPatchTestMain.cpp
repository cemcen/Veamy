#include <veamy/models/constraints/EssentialConstraints.h>
#include <mesher/models/PolygonalMesh.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/physics/Material.h>
#include <veamy/Veamer.h>
#include <veamy/physics/MaterialPlaneStress.h>

int main(){
    PolygonalMesh mesh;
    mesh.createFromFile("equilibriumTest_mesh.txt");
    mesh.printInFile("equilibrium_mesh.txt");

    EssentialConstraints essential;
    PointSegment downSide(Point(0,0), Point(1,0));
    SegmentConstraint down (downSide, mesh.getPoints(), Constraint::Direction::Vertical, new Constant(0));
    essential.addConstraint(down, mesh.getPoints());
    Point cornerPoint(Point(1,0));
    PointConstraint corner(cornerPoint, Constraint::Direction::Horizontal, new Constant(0));
    essential.addConstraint(corner);

    NaturalConstraints natural;
    PointSegment topSide(Point(0,1), Point(1,1));
    SegmentConstraint top (topSide, mesh.getPoints(), Constraint::Direction::Vertical, new Constant(1));
    natural.addConstraint(top, mesh.getPoints());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);
    container.addConstraints(natural, mesh);

    Material* m = new MaterialPlaneStress(3e7, 0.3);
    ProblemConditions conditions(container, m);

    Veamer v;
    v.initProblem(mesh, conditions);
    Eigen::VectorXd x = v.simulate(mesh);
    //By default, the file is created in home/, to create somewhere else, for example, /home/user/Documents/Veamy,
    //create the fileName variable as "/Documents/Veamy/equilibriumPatchTest.txt"
    std::string fileName = "equilibriumPatchTest.txt";
    v.writeDisplacements(fileName, x);
}
