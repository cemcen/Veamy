//**************************************************************
// This is basically the same file ParabolicMain.cpp except 
// that we add the time, L2-norm and H1-seminorm calculators
//**************************************************************

#include <veamy/models/constraints/Constraint.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/Veamer.h>
#include <delynoi/models/Region.h>
#include <delynoi/models/generator/functions/functions.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <veamy/models/constraints/values/Function.h>
#include <chrono>
#include <utilities/utilities.h>
#include <veamy/physics/materials/MaterialPlaneStrain.h>
#include <veamy/postprocess/L2NormCalculator.h>
#include <veamy/postprocess/H1NormCalculator.h>
#include <veamy/config/VeamyConfig.h>
#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include <veamy/problems/VeamyLinearElasticityDiscretization.h>

double tangencial(double x, double y){
    double P = -1000;
    double D =  4;
    double I = std::pow(D,3)/12;
    double value = std::pow(D,2)/4-std::pow(y,2);
    return P/(2*I)*value;
}

double uX(double x, double y){
    double P = -1000;
    double Ebar = 1e7/(1 - std::pow(0.3,2));
    double vBar = 0.3/(1 - 0.3);
    double D = 4;
    double L = 8;
    double I = std::pow(D,3)/12;
    return -P*y/(6*Ebar*I)*((6*L - 3*x)*x + (2+vBar)*std::pow(y,2) - 3*std::pow(D,2)/2*(1+vBar));
}

double uY(double x, double y){
    double P = -1000;
    double Ebar = 1e7/(1 - std::pow(0.3,2));
    double vBar = 0.3/(1 - 0.3);
    double D = 4;
    double L = 8;
    double I = std::pow(D,3)/12;
    return P/(6*Ebar*I)*(3*vBar*std::pow(y,2)*(L-x) + (3*L-x)*std::pow(x,2));
}

std::vector<double> exactDisplacement(double x, double y){
    double P = -1000;
    double Ebar = 1e7/(1 - std::pow(0.3,2));
    double vBar = 0.3/(1 - 0.3);
    double D = 4;
    double L = 8;
    double I = std::pow(D,3)/12;

    return {-P*y/(6*Ebar*I)*((6*L - 3*x)*x + (2+vBar)*std::pow(y,2) - 3*std::pow(D,2)/2*(1+vBar)),
                        P/(6*Ebar*I)*(3*vBar*std::pow(y,2)*(L-x) + (3*L-x)*std::pow(x,2))};
}

std::vector<double> exactStrain(double x, double y){
    double P = -1000;
    double Ebar = 1e7/(1 - std::pow(0.3,2));
    double vBar = 0.3/(1 - 0.3);
    double D = 4;
    double L = 8;
    double I = std::pow(D,3)/12;  
    double duxdx = -(P*y*(6*L-6*x))/(6*Ebar*I);
    double duydx = -(P*(3*vBar*std::pow(y,2)-2*x*(3*L-x)+std::pow(x,2)))/(6*Ebar*I);
    double duxdy = -(P*((vBar+2)*std::pow(y,2)+x*(6*L-3*x)-(3*std::pow(D,2)*(vBar+1))/2))/(6*Ebar*I)-(P*std::pow(y,2)*(vBar+2))/(3*Ebar*I);
    double duydy = (P*vBar*y*(L-x))/(Ebar*I);   

    return {duxdx,duydy,0.5*(duxdy+duydx)};
    // the third component is defined as in VEM: 0.5*(dux/dy + duy/dx)
}

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
    // If the path for the output files is not given, they are written to /home/user/ directory by default.
    // Otherwise, include the path. For instance, for /home/user/Documents/Veamy-3.0/output.txt , the path
    // must be "Documents/Veamy-3.0/output.txt"
    // CAUTION: the path must exists either because it is already in your system or becuase it is created
    // by Veamy's configuration files. For instance, Veamy creates the folder "/test" inside "/build", so
    // one can save the output files to "/build/test/" folder, but not to "/build/test/mycustom_folder",
    // since "/mycustom_folder" won't be created by Veamy's configuration files.
    std::string meshFileName = "parabolic_beam_mesh.txt";
    std::string dispFileName = "parabolic_beam_displacements.txt";
    
    // Instead of using Veamy's mesh generator, we read the mesh from a mesh file.
    // In this example, the mesh file does not contain the boundary conditions. We will
    // use the function "createFromFile" to read the mesh file. (Default mesh file is 
    // included inside the folder test/test_files/.)
    // UPDATE PATH ACCORDING TO YOUR FOLDERS: 
    //   in this example folder "Software" is located inside "/home/user/" and "Veamy-3.0" is Veamy's root folder
    std::string externalMeshFileName = "Software/Veamy-3.0/test/test_files/parabolic_main_vem_norms_3000poly_elems.txt";

    std::cout << "*** Starting Veamy ***" << std::endl;
    std::cout << "--> Test: Cantilever beam subjected to a parabolic end load <--" << std::endl;
    std::cout << "..." << std::endl;
    
    std::cout << "+ Reading mesh from a file ... ";
    Mesh<Polygon> mesh;
    mesh.createFromFile(externalMeshFileName, 1);
    std::cout << "done" << std::endl;

    std::cout << "+ Printing mesh to a file ... ";
    mesh.printInFile(meshFileName);
    std::cout << "done" << std::endl;

    std::cout << "+ Defining linear elastic material ... ";
    Material* material = new MaterialPlaneStrain (1e7, 0.3);
    LinearElasticityConditions* conditions = new LinearElasticityConditions(material);
    std::cout << "done" << std::endl;

    std::cout << "+ Defining Dirichlet and Neumann boundary conditions ... ";
    Function* uXConstraint = new Function(uX);
    Function* uYConstraint = new Function(uY);

    PointSegment leftSide(Point(0,-2), Point(0,2));
    SegmentConstraint const1 (leftSide, mesh.getPoints(), uXConstraint);
    conditions->addEssentialConstraint(const1, mesh.getPoints(), elasticity_constraints::Direction::Horizontal);

    SegmentConstraint const2 (leftSide, mesh.getPoints(), uYConstraint);
    conditions->addEssentialConstraint(const2, mesh.getPoints(), elasticity_constraints::Direction::Vertical);

    Function* tangencialLoad = new Function(tangencial);
    PointSegment rightSide(Point(8,-2), Point(8,2));

    SegmentConstraint const3 (rightSide, mesh.getPoints(), tangencialLoad);
    conditions->addNaturalConstraint(const3, mesh.getPoints(), elasticity_constraints::Direction::Vertical);
    std::cout << "done" << std::endl;

    std::cout << "+ Preparing the simulation ... ";
    VeamyLinearElasticityDiscretization* problem = new VeamyLinearElasticityDiscretization(conditions);

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
