#include <veamy/Veamer.h>
#include <veamy/physics/materials/MaterialPlaneStrain.h>
#include <veamy/config/VeamyConfig.h>
#include <veamy/physics/conditions/PoissonConditions.h>
#include <veamy/problems/VeamyPoissonDiscretization.h>
#include <veamy/models/constraints/values/Constant.h>

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
    std::string meshFileName = "base_poisson_mesh.txt";
    std::string dispFileName = "base_poisson_displacements.txt";

    std::string externalMeshFileName = "poisson_mesh.txt";

    std::cout << "+ Reading mesh from a file ... ";
    Mesh<Polygon> mesh;
    mesh.createFromFile(externalMeshFileName, 1);
    std::cout << "done" << std::endl;

    std::cout << "+ Defining problem conditions ... ";
    PoissonConditions* conditions = new PoissonConditions();
    std::cout << "done" << std::endl;

    std::cout << "+ Defining Dirichlet and Neumann boundary conditions ... ";
    Point cornerPoint(Point(3,1));
    PointConstraint corner(cornerPoint, new Constant(0));
    conditions->addEssentialConstraint(corner);

    PointSegment bottomSide(Point(0,0), Point(3,0));
    SegmentConstraint top (bottomSide, mesh.getPoints(), new Constant(1));
    conditions->addNaturalConstraint(top, mesh.getPoints());
    std::cout << "done" << std::endl;

    std::cout << "+ Preparing the simulation ... ";
    VeamyPoissonDiscretization* problem = new VeamyPoissonDiscretization(conditions);

    Veamer v(problem);
    v.initProblem(mesh);
    std::cout << "done" << std::endl;

    std::cout << "+ Printing mesh to a file ... ";
    mesh.printInFile(meshFileName);
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
    path1 +=  meshFileName;
    path2 +=  dispFileName;
    std::cout << path1 << std::endl;
    std::cout << path2 << std::endl;
    std::cout << "*** Veamy has ended ***" << std::endl;
}
