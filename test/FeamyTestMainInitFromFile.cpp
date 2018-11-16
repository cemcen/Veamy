#include <feamy/Feamer.h>
#include <veamy/physics/materials/MaterialPlaneStrain.h>
#include <veamy/config/VeamyConfig.h>
#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include <feamy/problem/FeamyLinearElasticityDiscretization.h>
#include <feamy/models/constructor/Tri3Constructor.h>

int main(){
    
    // Usage example of Feamy, the FEM module of Veamy, to solve problems with 3-node triangular FE elements
    // Problem: reading T3 elements from file containing a mesh and boundary conditions     
    
    // Set precision for plotting to output files:    
    // OPTION 1: in "VeamyConfig::instance()->setPrecision(Precision::precision::mid)"
    // use "small" for 6 digits; "mid" for 10 digits; "large" for 16 digits.
    // OPTION 2: set the desired precision, for instance, as:
    // VeamyConfig::instance()->setPrecision(12) for 12 digits. Change "12" by the desired precision.
    // OPTION 3: Omit any instruction "VeamyConfig::instance()->setPrecision(.....)"
    // from this file. In this case, the default precision, which is 6 digits, will be used.
    VeamyConfig::instance()->setPrecision(Precision::precision::mid);

    // DEFINING PATH FOR THE OUTPUT FILES:
    // If the path for the output files is not given, they are written to /home/user/ directory by default.
    // Otherwise, include the path. For instance, for /home/user/Documents/Veamy-2.1/output.txt , the path
    // must be "Documents/Veamy-2.1/output.txt"
    // CAUTION: the path must exists either because it is already in your system or becuase it is created
    // by Veamy's configuration files. For instance, Veamy creates the folder "/test" inside "/build", so
    // one can save the output files to "/build/test/" folder, but not to "/build/test/mycustom_folder",
    // since "/mycustom_folder" won't be created by Veamy's configuration files.
    std::string meshFileName = "feamy_test_initfromfile_fem_mesh.txt";
    std::string dispFileName = "feamy_test_initfromfile_fem_displacements.txt";

    // Instead of using Veamy's mesh generator, we read the mesh from a mesh file.
    // In this example, the mesh file also contains the boundary conditions. We will
    // use the function "initProblemFromFile" to read the mesh file containing 
    // boundary conditions. (Default mesh file is included inside the folder test/test_files/.)
    // UPDATE PATH ACCORDING TO YOUR FOLDERS: 
    //   in this example folder "Software" is located inside "/home/user/" and "Veamy-2.1" is Veamy's root folder
    std::string externalMeshFileName = "Software/Veamy-2.1/test/test_files/feamy_test_initfromfile.txt";

    std::cout << "*** Starting Veamy --> Feamy module ***" << std::endl;
    std::cout << "--> Test: Reading T3 elements from file containing a mesh and boundary conditions <--" << std::endl;
    std::cout << "..." << std::endl;

    std::cout << "+ Defining linear elastic material ... ";
    Material* material = new MaterialPlaneStrain(1e7, 0.3);
    LinearElasticityConditions* conditions = new LinearElasticityConditions(material);
    std::cout << "done" << std::endl;

    std::cout << "+ Preparing the simulation from a file containing a mesh and boundary conditions ... ";
    FeamyLinearElasticityDiscretization* problem = new FeamyLinearElasticityDiscretization(conditions);

    Feamer v(problem);
    Mesh<Triangle> mesh = v.initProblemFromFile(externalMeshFileName, new Tri3Constructor);
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
