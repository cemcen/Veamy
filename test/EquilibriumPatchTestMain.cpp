#include <veamy/models/constraints/EssentialConstraints.h>
#include <delynoi/models/Mesh.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/physics/materials/Material.h>
#include <veamy/Veamer.h>
#include <utilities/utilities.h>
#include <veamy/physics/materials/MaterialPlaneStress.h>
#include <veamy/config/VeamyConfig.h>
#include <veamy/postprocess/L2NormCalculator.h>
#include <veamy/postprocess/H1NormCalculator.h>
#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include <veamy/problems/VeamyLinearElasticityDiscretization.h>

std::vector<double> exactDisplacement(double x, double y){
    double E = 3e7, v = 0.3;
    return {(v/E)*(1-x), y/E};
}

std::vector<double> exactStrain(double x, double y){
    double E = 3e7, v = 0.3;
    return {-v/E, 1.0/E, 0.0};
    // the third component is defined as in VEM: 1/2*(dux/dy + duy/dx) 
}

int main(){
    // Set precision for plotting to output files:
    // OPTION 1: in "VeamyConfig::instance()->setPrecision(Precision::precision::mid)"
    // use "small" for 6 digits; "mid" for 10 digits; "large" for 16 digits.
    // OPTION 2: set the desired precision, for instance, as:
    // VeamyConfig::instance()->setPrecision(12) for 12 digits. Change "12" by the desired precision.
    // OPTION 3: Omit any instruction "VeamyConfig::instance()->setPrecision(.....)"
    // from this file. In this case, the default precision, which is 6 digits, will be used.
    VeamyConfig::instance()->setPrecision(Precision::precision::large);
    
    // DEFINING PATH FOR THE OUTPUT FILES:
    // If the path for the output files is not given, they are written to /home/user/ directory by default.
    // Otherwise, include the path. For instance, for /home/user/Documents/Veamy-3.0/output.txt , the path
    // must be "Documents/Veamy-3.0/output.txt"
    // CAUTION: the path must exists either because it is already in your system or becuase it is created
    // by Veamy's configuration files. For instance, Veamy creates the folder "/test" inside "/build", so
    // one can save the output files to "/build/test/" folder, but not to "/build/test/mycustom_folder",
    // since "/mycustom_folder" won't be created by Veamy's configuration files.
    std::string meshFileName = "equi_patch_test_mesh.txt";
    std::string dispFileName = "equi_patch_test_displacements.txt";
    
    std::cout << "*** Starting Veamy ***" << std::endl;
    std::cout << "--> Test: Equilibrium patch test / Reading a mesh from a file without boundary conditions <--" << std::endl;
    std::cout << "..." << std::endl;

    // File that contains an external mesh (default file is included inside the folder test/test_files/). 
    // UPDATE PATH ACCORDING TO YOUR FOLDERS: 
    //   in this example folder "Software" is located inside "/home/user/" and "Veamy" is Veamy's root folder
    std::string externalMeshFileName = "Software/Veamy/test/test_files/equilibriumTest_mesh.txt";

    std::cout << "+ Reading mesh from a file ... ";
    Mesh<Polygon> mesh;
    mesh.createFromFile(externalMeshFileName, 1);
    std::cout << "done" << std::endl;

    std::cout << "+ Printing mesh to a file ... ";
    mesh.printInFile(meshFileName);
    std::cout << "done" << std::endl;

    std::cout << "+ Defining linear elastic material ... ";
    Material* material = new MaterialPlaneStress(3e7, 0.3);
    LinearElasticityConditions* conditions = new LinearElasticityConditions(material);
    std::cout << "done" << std::endl;

    std::cout << "+ Defining Dirichlet and Neumann boundary conditions ... ";
    PointSegment downSide(Point(0,0), Point(1,0));
    SegmentConstraint down (downSide, mesh.getPoints(), new Constant(0));
    conditions->addEssentialConstraint(down, mesh.getPoints(), elasticity_constraints::Direction::Vertical);
    Point cornerPoint(Point(1,0));
    PointConstraint corner(cornerPoint, new Constant(0));
    conditions->addEssentialConstraint(corner, elasticity_constraints::Direction::Horizontal);

    PointSegment topSide(Point(0,1), Point(1,1));
    SegmentConstraint top (topSide, mesh.getPoints(), new Constant(1));
    conditions->addNaturalConstraint(top, mesh.getPoints(), elasticity_constraints::Direction::Vertical);
    std::cout << "done" << std::endl;

    std::cout << "+ Preparing the simulation ... ";
    VeamyLinearElasticityDiscretization* problem = new VeamyLinearElasticityDiscretization(conditions);

    Veamer v(problem);
    v.initProblem(mesh);
    std::cout << "done" << std::endl;

    std::cout << "+ Simulating ... ";
    Eigen::VectorXd x = v.simulate(mesh);
    std::cout << "done" << std::endl;

    std::cout << "+ Calculating norms of the error ... ";
    DisplacementValue* exactDisplacementSolution = new DisplacementValue(exactDisplacement);
    L2NormCalculator<Polygon>* L2 = new L2NormCalculator<Polygon>(exactDisplacementSolution, x, v.DOFs);
    NormResult L2norm = v.computeErrorNorm(L2, mesh);
    StrainValue* exactStrainSolution = new StrainValue(exactStrain);
    H1NormCalculator<Polygon>* H1 = new H1NormCalculator<Polygon>(exactStrainSolution, x, v.DOFs);
    NormResult H1norm = v.computeErrorNorm(H1, mesh);   
    std::cout << "done" << std::endl; 
    std::cout << "  Relative L2-norm    : " << utilities::toString(L2norm.NormValue) << std::endl;
    std::cout << "  Relative H1-seminorm: " << utilities::toString(H1norm.NormValue) << std::endl;
    std::cout << "  Element size        : " << utilities::toString(L2norm.MaxEdge) << std::endl;

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
