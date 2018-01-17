//**************************************************************
// Solve the cantilever beam subjected to a parabolic end load
// using standard 3-node triangular finite elements
//**************************************************************

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleDelaunayGenerator.h>
#include <veamy/models/constraints/EssentialConstraints.h>
#include <veamy/models/constraints/values/Function.h>
#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/physics/conditions/Conditions.h>
#include <veamy/physics/materials/MaterialPlaneStrain.h>
#include <feamy/Feamer.h>
#include <feamy/models/constructor/Tri3Constructor.h>
#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include <feamy/problem/FeamyLinearElasticityDiscretization.h>
#include <chrono>
#include <veamy/postprocess/analytic/DisplacementValue.h>
#include <veamy/postprocess/L2NormCalculator.h>
#include <veamy/postprocess/analytic/StrainValue.h>
#include <veamy/postprocess/H1NormCalculator.h>

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

    return {duxdx,duydy,duxdy+duydx};
    // the third component is defined as in classical FEM: dux/dy + duy/dx 
}


int main(){
    // DEFINING PATH FOR THE OUTPUT FILES:
    // If the path for the output files is not given, they are written to /home directory by default.
    // Otherwise, include the path. For instance, for /home/user/Documents/Veamy/output.txt , the path
    // must be "Documents/Veamy/output.txt"
    // CAUTION: the path must exists either because it is already in your system or becuase it is created
    // by Veamy's configuration files. For instance, Veamy creates the folder "/test" inside "/build", so
    // one can save the output files to "/build/test/" folder, but not to "/build/test/mycustom_folder",
    // since "/mycustom_folder" won't be created by Veamy's configuration files.
    std::string meshFileName = "parabolic_beam_mesh.txt";
    std::string dispFileName = "parabolic_beam_displacements.txt";

    std::cout << "*** Starting Veamy ***" << std::endl;
    std::cout << "--> Test: Cantilever beam subjected to a parabolic end load <--" << std::endl;
    std::cout << "..." << std::endl;

    std::cout << "+ Defining the domain ... ";
    std::vector<Point> rectangle4x8_points = {Point(0, -2), Point(8, -2), Point(8, 2), Point(0, 2)};
    Region rectangle4x8(rectangle4x8_points);
    std::cout << "done" << std::endl;

    std::cout << "+ Generating 3-node triangular mesh ... ";
    //rectangle4x8.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 12, 6);
    //rectangle4x8.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 18, 9);
    rectangle4x8.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 24, 12);
    //rectangle4x8.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 30, 15);
    //rectangle4x8.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 36, 18);
    std::vector<Point> seeds = rectangle4x8.getSeedPoints();
    TriangleDelaunayGenerator meshGenerator (seeds, rectangle4x8);
    Mesh<Triangle> mesh = meshGenerator.getConformingDelaunayTriangulation();
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
    FeamyLinearElasticityDiscretization* problem = new FeamyLinearElasticityDiscretization(conditions);

    Feamer v(problem);
    v.initProblem(mesh, new Tri3Constructor);
    std::cout << "done" << std::endl;

    std::cout << "+ Simulating ... ";
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    Eigen::VectorXd x = v.simulate(mesh);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "done" << std::endl;
    std::cout << "  Elapsed simulation time: " << duration/1e6 << " s" <<std::endl;

    std::cout << "+ Printing nodal displacement solution to a file ... ";
    v.writeDisplacements(dispFileName, x);
    std::cout << "done" << std::endl;

    std::cout << "+ Calculating norms of the error ... ";
    DisplacementValue* exactDisplacementSolution = new DisplacementValue(exactDisplacement);
    L2NormCalculator<Triangle>* L2 = new L2NormCalculator<Triangle>(exactDisplacementSolution, x, v.DOFs);
    NormResult L2norm = v.computeErrorNorm(L2, mesh);
    StrainValue* exactStrainSolution = new StrainValue(exactStrain);
    H1NormCalculator<Triangle>* H1 = new H1NormCalculator<Triangle>(exactStrainSolution, x, v.DOFs);
    NormResult H1norm = v.computeErrorNorm(H1, mesh);
    std::cout << "done" << std::endl;
    std::cout << "  Relative L2-norm    : " << utilities::toString(L2norm.NormValue) << std::endl;
    std::cout << "  Relative H1-seminorm: " << utilities::toString(H1norm.NormValue) << std::endl;
    std::cout << "  Element size        : " << utilities::toString(L2norm.MaxEdge) << std::endl;

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
