#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/models/generator/functions/functions.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <veamy/Veamer.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/physics/materials/MaterialPlaneStrain.h>
#include <utilities/utilities.h>
#include <veamy/physics/materials/MaterialPlaneStrain.h>
#include <veamy/config/VeamyConfig.h>
#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include <veamy/problems/VeamyLinearElasticityDiscretization.h>

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
    std::string meshFileName = "unicorn_mesh.txt";
    std::string dispFileName = "unicorn_displacements.txt";
    std::string geoFileName = "unicorn_geometry.txt";
	
    std::cout << "*** Starting Veamy ***" << std::endl;
    std::cout << "--> Test: Unicorn <--" << std::endl;
    std::cout << "..." << std::endl;

    std::cout << "+ Defining the domain ... ";
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
    TriangleVoronoiGenerator g(seeds, unicorn);
    Mesh<Polygon> mesh = g.getMesh();
    std::cout << "done" << std::endl;

    std::cout << "+ Printing mesh to a file ... ";
    mesh.printInFile(meshFileName);
    std::cout << "done" << std::endl;


    std::cout << "+ Defining linear elastic material ... ";
    Material* material = new MaterialPlaneStrain (1e4, 0.25);
    LinearElasticityConditions* conditions = new LinearElasticityConditions(material);
    std::cout << "done" << std::endl;


    std::cout << "+ Defining Dirichlet and Neumann boundary conditions ... ";
    Point leftFoot(2,0);
    PointConstraint left(leftFoot, new Constant(0));
    Point rightFoot(10,0);
    PointConstraint right(rightFoot, new Constant(0));

    conditions->addEssentialConstraint(left, elasticity_constraints::Direction::Total);
    conditions->addEssentialConstraint(right, elasticity_constraints::Direction::Total);

    NaturalConstraints natural;
    PointSegment backSegment(Point(6.7,11.5), Point(3.3,11.3));
    SegmentConstraint back (backSegment, mesh.getPoints(), new Constant(-200));
    conditions->addNaturalConstraint(back, mesh.getPoints(), elasticity_constraints::Direction::Total);

    std::cout << "done" << std::endl;

    std::cout << "+ Preparing the simulation ... ";
    VeamyLinearElasticityDiscretization*  problem = new VeamyLinearElasticityDiscretization(conditions);

    Veamer v(problem);
    v.initProblem(mesh);
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
