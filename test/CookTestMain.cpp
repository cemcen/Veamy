#include <vector>
#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/models/hole/CircularHole.h>
#include <delynoi/models/generator/functions/functions.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <veamy/Veamer.h>
#include <veamy/models/constraints/values/Constant.h>
#include <utilities/utilities.h>
#include <veamy/physics/materials/MaterialPlaneStrain.h>
#include <veamy/config/VeamyConfig.h>

int main(){
    // Set precision for plotting to output files:   
    // OPTION 1: in "VeamyConfig::instance()->setPrecision(Precision::precision::mid)"    
    // use "small" for 6 digits; "mid" for 10 digits; "large" for 16 digits.    
    // OPTION 2: set the desired precision, for instance, as:    
    // VeamyConfig::instance()->setPrecision(12) for 12 digits. Change "12" by the desired precision.    
    // OPTION 3: Omit any instruction "VeamyConfig::instance()->setPrecision(.....)"    
    // from this file. In this case, the default precision, which is 6 digits, will be used.   
    VeamyConfig::instance()->setPrecision(Precision::precision::mid);    
    
    // DEFINING PATH FOR THE OUTPUT FILES:
    // If the path for the output files is not given, they are written to /home directory by default.
    // Otherwise, include the path. For instance, for /home/user/Documents/Veamy/output.txt , the path
    // must be "Documents/Veamy/output.txt"
    // CAUTION: the path must exists either because it is already in your system or becuase it is created
    // by Veamy's configuration files. For instance, Veamy creates the folder "/test" inside "/build", so
    // one can save the output files to "/build/test/" folder, but not to "/build/test/mycustom_folder",
    // since "/mycustom_folder" won't be created by Veamy's configuration files.
    std::string meshFileName = "cook_membrane_mesh.txt";
    std::string dispFileName = "cook_membrane_displacements.txt";
    std::string geoFileName = "cook_membrane_geometry.txt";
    
    std::cout << "*** Starting Veamy ***" << std::endl;
    std::cout << "--> Test: Cook's membrane <--" << std::endl;
    std::cout << "..." << std::endl;
    
    std::cout << "+ Defining the domain ... ";
    std::vector<Point> TBeam_points = {Point(0,0), Point(48,44), Point(48,64), Point(0,44)};
    Region TBeam(TBeam_points);

    Hole hole1 = CircularHole(Point(8,30), 5);
    Hole hole2 = CircularHole(Point(24,40), 4);
    Hole hole3 = CircularHole(Point(40,50), 3);
    TBeam.addHole(hole1);
    TBeam.addHole(hole2);
    TBeam.addHole(hole3);
    std::cout << "done" << std::endl;

    std::cout << "+ Printing geometry to a file ... ";
    TBeam.printInFile(geoFileName);
    std::cout << "done" << std::endl;

    std::cout << "+ Generating polygonal mesh ... ";
    TBeam.generateSeedPoints(PointGenerator(functions::constantAlternating(), functions::constant()), 25, 25);
    std::vector<Point> seeds = TBeam.getSeedPoints();
    TriangleVoronoiGenerator g(seeds, TBeam);
    Mesh<Polygon> mesh = g.getMesh();
    std::cout << "done" << std::endl;

    std::cout << "+ Printing mesh to a file ... ";
    mesh.printInFile(meshFileName);
    std::cout << "done" << std::endl;

    std::cout << "+ Defining Dirichlet and Neumann boundary conditions ... ";
    EssentialConstraints essential;
    PointSegment leftSide(Point(0,0), Point(0,44));
    SegmentConstraint left(leftSide, mesh.getPoints(), Constraint::Direction::Total, new Constant(0));
    essential.addConstraint(left, mesh.getPoints());

    NaturalConstraints natural;
    PointSegment rightSide(Point(48,44), Point(48,64));
    SegmentConstraint right(rightSide, mesh.getPoints(), Constraint::Direction::Vertical, new Constant(6.25));
    natural.addConstraint(right, mesh.getPoints());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh.getPoints());
    container.addConstraints(natural, mesh.getPoints());
    std::cout << "done" << std::endl;

    std::cout << "+ Defining linear elastic material ... ";
    Material* material = new MaterialPlaneStrain(240, 0.3);
    Conditions conditions(container, material);
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
