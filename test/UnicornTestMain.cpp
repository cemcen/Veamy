#include <mesher/models/basic/Point.h>
#include <mesher/models/Region.h>
#include <mesher/models/generator/functions.h>
#include <mesher/voronoi/TriangleMeshGenerator.h>
#include <veamy/Veamer.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/physics/MaterialPlaneStrain.h>
#include <utilities/utilities.h>
#include <veamy/physics/MaterialPlaneStrain.h>
#include <veamy/config/VeamyConfig.h>

int main(){
    VeamyConfig::instance()->setPrecision(Precision::precision::small);
    
    std::cout << "*** Starting Veamy ***" << std::endl;
    std::cout << "--> Test: Unicorn <--" << std::endl;
    std::cout << "..." << std::endl;

    // DEFINING PATH FOR THE OUTPUT FILES:
    // If the path for the output files is not given, they are written to /home directory by default.
    // Otherwise, include the path. For instance, for /home/user/Documents/Veamy/output.txt , the path
    // must be "Documents/Veamy/output.txt"
    // CAUTION: the path must exists either because it is already in your system or becuase it is created
    // by Veamy's configuration files. For instance, Veamy creates the folder "/test" inside "/build", so
    // one can save the output files to "/build/test/" folder, but not to "/build/test/mycustom_folder",
    // since "/mycustom_folder" won't be created by Veamy's configuration files.
    std::string meshFileName = "Software/Veamy-master/build/test/unicorn_mesh.txt";
    std::string dispFileName = "Software/Veamy-master/build/test/unicorn_displacements.txt";
    std::string geoFileName = "Software/Veamy-master/build/test/unicorn_geometry.txt";

    std::cout << "+ Defining the domain ... ";
    VeamyConfig::instance()->setPrecision(Precision::precision::large);

    std::vector<Point> unicorn_points = {Point(2,0), Point(3,0.5), Point(3.5,2), Point(4,4), Point(6,4), Point(8.5,4),
                                         Point(9,2), Point(9.5,0.5), Point(10,0), Point(10.5,0.5), Point(11.2,2.5),
                                         Point(11.5,4.5), Point(11.8,8.75), Point(11.8,11.5), Point(13.5,11), Point(14.5,11.2),
                                         Point(15,12), Point(15,13), Point(15,14.5), Point(14,16.5), Point(15,19.5), Point(15.2,20),
                                         Point(14.5,19.7), Point(11.8,18.2), Point(10.5,18.3), Point(10,18), Point(8,16),
                                         Point(7.3,15.3), Point(7,13.8), Point(6.7,11.5), Point(3.3,11.3), Point(1,10.5),
                                         Point(0.4,8.8), Point(0.3,6.8), Point(0.4,4), Point(0.8,2.1), Point(1.3,0.4)};
    Region unicorn(unicorn_points);
    std::cout << "done" << std::endl;

    std::cout << "+ Printing geometry to a file ... ";
    unicorn.printInFile(geoFileName);
    std::cout << "done" << std::endl;

    std::cout << "+ Generating polygonal mesh ... ";
    unicorn.generateSeedPoints(PointGenerator(functions::constantAlternating(), functions::constantAlternating()), 20, 25);
    std::vector<Point> seeds = unicorn.getSeedPoints();
    TriangleMeshGenerator g(seeds, unicorn);
    PolygonalMesh mesh = g.getMesh();
    std::cout << "done" << std::endl;

    std::cout << "+ Printing mesh to a file ... ";
    mesh.printInFile(meshFileName);
    std::cout << "done" << std::endl;

    std::cout << "+ Defining Dirichlet and Neumann boundary conditions ... ";
    EssentialConstraints essential;
    Point leftFoot(2,0);
    PointConstraint left(leftFoot, Constraint::Direction::Total, new Constant(0));
    Point rightFoot(10,0);
    PointConstraint right(rightFoot, Constraint::Direction::Total, new Constant(0));
    essential.addConstraint(left);
    essential.addConstraint(right);

    NaturalConstraints natural;
    PointSegment backSegment(Point(6.7,11.5), Point(3.3,11.3));
    SegmentConstraint back (backSegment, mesh.getPoints(), Constraint::Direction::Total, new Constant(-200));
    natural.addConstraint(back, mesh.getPoints());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);
    container.addConstraints(natural, mesh);
    std::cout << "done" << std::endl;

    std::cout << "+ Defining linear elastic material ... ";
    Material* material = new MaterialPlaneStrain (1e4, 0.25);
    ProblemConditions conditions(container, material);
    std::cout << "done" << std::endl;

    std::cout << "+ Preparing the simulation ... ";
    Veamer v;
    v.initProblem(mesh, conditions);
    std::cout << "done" << std::endl;

    std::cout << "+ Simulating ... ";
    Eigen::VectorXd x = v.simulate(mesh);
    std::cout << "done" << std::endl;

    std::cout << "+ Printing nodal displacement solution to a file ... ";
    v.writeDisplacements(dispFileName, x);
    std::cout << "done" << std::endl;
    std::cout << "+ Problem finished successfully" << std::endl;
    std::cout << "..." << std::endl;
    std::cout << "Check output files:" << std::endl;
    std::string path1 = utilities::getPath();
    std::string path2 = utilities::getPath();
    std::string path3 = utilities::getPath();
    path1 +=  meshFileName;
    path2 +=  dispFileName;
    path3 +=  geoFileName;
    std::cout << path1 << std::endl;
    std::cout << path2 << std::endl;
    std::cout << path3 << std::endl;
    std::cout << "*** Veamy has ended ***" << std::endl;
}
