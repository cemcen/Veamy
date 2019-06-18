#include <veamy/config/VeamyConfig.h>
#include <chrono>
#include <string>
#include <delynoi/models/generator/PointGenerator.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <veamy/physics/conditions/PoissonConditions.h>
#include <veamy/models/constraints/values/Function.h>
#include <veamy/problems/VeamyPoissonDiscretization.h>
#include <veamy/postprocess/analytic/DisplacementValue.h>
#include <veamy/postprocess/L2NormCalculator.h>
#include <veamy/postprocess/analytic/StrainValue.h>
#include <veamy/postprocess/H1NormCalculator.h>
#include <veamy/models/constraints/values/Constant.h>

double sourceTerm(double x, double y){
    return (32*y*(1-y) + 32*x*(1-x));
}

std::vector<double> exactScalarField(double x, double y){
    return {16*x*y*(1-x)*(1-y)};
}

std::vector<double> exactGradScalarField(double x, double y){
    return {16*y*(1-y)*(1-2*x),16*x*(1-x)*(1-2*y)};
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
    std::string meshFileName = "poisson_source_test_mesh.txt";
    std::string scalarFieldFileName = "poisson_source_test_scalarfield.txt";
    
    // Instead of using Veamy's mesh generator, we read the mesh from a mesh file.
    // In this example, the mesh file does not contain the boundary conditions. We will
    // use the function "createFromFile" to read the mesh file. (Default mesh file is 
    // included inside the folder test/test_files/.)
    // UPDATE PATH ACCORDING TO YOUR FOLDERS: 
    //   in this example folder "Software" is located inside "/home/user/" and "Veamy-3.0" is Veamy's root folder
    std::string externalMeshFileName = "Software/Veamy-3.0/test/test_files/poisson_source_test_createfromfile.txt";

    std::cout << "*** Starting Veamy ***" << std::endl;
    std::cout << "--> Test: Poisson source test from file containing a mesh without boundary conditions <--" << std::endl;
    std::cout << "..." << std::endl;  

    std::cout << "+ Reading mesh from a file ... ";
    Mesh<Polygon> mesh;
    mesh.createFromFile(externalMeshFileName, 1);
    std::cout << "done" << std::endl;

    std::cout << "+ Printing mesh to a file ... ";
    mesh.printInFile(meshFileName);
    std::cout << "done" << std::endl;

    std::cout << "+ Defining problem conditions ... ";
    BodyForce* f = new BodyForce(sourceTerm);
    PoissonConditions* conditions = new PoissonConditions(f);
    std::cout << "done" << std::endl;

    std::cout << "+ Defining Dirichlet and Neumann boundary conditions ... ";
    PointSegment leftSide(Point(0,0), Point(0,1));
    SegmentConstraint left (leftSide, mesh.getPoints(), new Constant(0)); // u=0;
    conditions->addEssentialConstraint(left, mesh.getPoints());

    PointSegment downSide(Point(0,0), Point(1,0));
    SegmentConstraint down (downSide, mesh.getPoints(), new Constant(0)); // u=0;
    conditions->addEssentialConstraint(down, mesh.getPoints());

    PointSegment rightSide(Point(1,0), Point(1, 1));
    SegmentConstraint right (rightSide, mesh.getPoints(), new Constant(0)); // u=0;
    conditions->addEssentialConstraint(right, mesh.getPoints());

    PointSegment topSide(Point(0, 1), Point(1, 1));
    SegmentConstraint top (topSide, mesh.getPoints(), new Constant(0)); // u=0;
    conditions->addEssentialConstraint(top, mesh.getPoints());
    std::cout << "done" << std::endl;

    std::cout << "+ Preparing the simulation ... ";
    VeamyPoissonDiscretization* problem = new VeamyPoissonDiscretization(conditions);

    Veamer v(problem);
    v.initProblem(mesh);
    std::cout << "done" << std::endl;

    std::cout << "+ Simulating ... ";
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    Eigen::VectorXd x = v.simulate(mesh);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();    
    std::cout << "done" << std::endl;
    std::cout << "  Elapsed simulation time: " << duration/1e6 << " s" <<std::endl;

    std::cout << "+ Calculating norms of the error ... ";
    DisplacementValue* exactScalarFieldSolution = new DisplacementValue(exactScalarField);
    L2NormCalculator<Polygon>* L2 = new L2NormCalculator<Polygon>(exactScalarFieldSolution, x, v.DOFs);
    NormResult L2norm = v.computeErrorNorm(L2, mesh);
    StrainValue* exactGradScalarFieldSolution = new StrainValue(exactGradScalarField);
    H1NormCalculator<Polygon>* H1 = new H1NormCalculator<Polygon>(exactGradScalarFieldSolution, x, v.DOFs);
    NormResult H1norm = v.computeErrorNorm(H1, mesh);
    std::cout << "done" << std::endl;
    std::cout << "  Relative L2-norm    : " << utilities::toString(L2norm.NormValue) << std::endl;
    std::cout << "  Relative H1-seminorm: " << utilities::toString(H1norm.NormValue) << std::endl;
    std::cout << "  Element size        : " << utilities::toString(L2norm.MaxEdge) << std::endl;

    std::cout << "+ Printing nodal field solution to a file ... ";
    v.writeDisplacements(scalarFieldFileName, x);
    std::cout << "done" << std::endl;
    std::cout << "+ Problem finished successfully" << std::endl;
    std::cout << "..." << std::endl;
    std::cout << "Check output files:" << std::endl;
    std::string path1 = utilities::getPath();
    std::string path2 = utilities::getPath();
    path1 +=  meshFileName;
    path2 +=  scalarFieldFileName;
    std::cout << path1 << std::endl;
    std::cout << path2 << std::endl;
    std::cout << "*** Veamy has ended ***" << std::endl;
}
