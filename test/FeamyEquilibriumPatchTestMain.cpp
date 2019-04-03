#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleDelaunayGenerator.h>
#include <feamy/Feamer.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/physics/materials/MaterialPlaneStress.h>
#include <feamy/models/constructor/Tri3Constructor.h>
#include <veamy/config/VeamyConfig.h>
#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include <feamy/problem/FeamyLinearElasticityDiscretization.h>
#include <utilities/utilities.h>
#include <veamy/postprocess/L2NormCalculator.h>
#include <veamy/postprocess/H1NormCalculator.h>

std::vector<double> exactDisplacement(double x, double y){
    double E = 3e7, v = 0.3;
    return {(v/E)*(1-x), y/E};
}

std::vector<double> exactStrain(double x, double y){
    double E = 3e7, v = 0.3;
    return {-v/E, 1.0/E, 0.0};
    // the third component is defined as in FEM: 2*1/2*(dux/dy + duy/dx)
}

int main(){
    
    // Usage example of Feamy, the FEM module of Veamy, to solve problems with 3-node triangular FE elements
    // Problem: equilibrium patch test       
    
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
    // Otherwise, include the path. For instance, for /home/user/Documents/Veamy-2.1/output.txt , the path
    // must be "Documents/Veamy-2.1/output.txt"
    // CAUTION: the path must exists either because it is already in your system or becuase it is created
    // by Veamy's configuration files. For instance, Veamy creates the folder "/test" inside "/build", so
    // one can save the output files to "/build/test/" folder, but not to "/build/test/mycustom_folder",
    // since "/mycustom_folder" won't be created by Veamy's configuration files. 
    std::string meshFileName = "equi_patch_test_fem_mesh.txt";
    std::string dispFileName = "equi_patch_test_fem_displacements.txt";
	
    std::cout << "*** Starting Veamy --> Feamy module ***" << std::endl;
    std::cout << "--> Test: Displacement patch test using 3-node triangular elements  <--" << std::endl;
    std::cout << "..." << std::endl; 

    std::vector<Point> region_points = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Region square(region_points);
    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 6, 6);

    std::vector<Point> seeds = square.getSeedPoints();
    TriangleDelaunayGenerator delaunayGenerator(seeds, square);
    Mesh<Triangle> delaunay = delaunayGenerator.getConformingDelaunayTriangulation();

    delaunay.printInFile(meshFileName);

    Material* material = new MaterialPlaneStress(3e7, 0.3);
    LinearElasticityConditions* conditions = new LinearElasticityConditions(material);

    PointSegment downSide(Point(0,0), Point(1,0));
    SegmentConstraint down (downSide, delaunay.getPoints(),  new Constant(0));
    conditions->addEssentialConstraint(down, delaunay.getPoints(), elasticity_constraints::Direction::Vertical);
    Point cornerPoint(Point(1,0));
    PointConstraint corner(cornerPoint, new Constant(0));
    conditions->addEssentialConstraint(corner, elasticity_constraints::Direction::Horizontal);

    PointSegment topSide(Point(0,1), Point(1,1));
    SegmentConstraint top (topSide, delaunay.getPoints(), new Constant(1));
    conditions->addNaturalConstraint(top, delaunay.getPoints(), elasticity_constraints::Direction::Vertical);

    FeamyLinearElasticityDiscretization* problem = new FeamyLinearElasticityDiscretization(conditions);
    Feamer feamer(problem);
    feamer.initProblem(delaunay, new Tri3Constructor());

    Eigen::VectorXd x = feamer.simulate(delaunay);
    
    std::cout << "+ Calculating norms of the error ... ";
    DisplacementValue* exactDisplacementSolution = new DisplacementValue(exactDisplacement);
    L2NormCalculator<Triangle>* L2 = new L2NormCalculator<Triangle>(exactDisplacementSolution, x, feamer.DOFs);
    NormResult L2norm = feamer.computeErrorNorm(L2, delaunay);
    StrainValue* exactStrainSolution = new StrainValue(exactStrain);
    H1NormCalculator<Triangle>* H1 = new H1NormCalculator<Triangle>(exactStrainSolution, x, feamer.DOFs);
    NormResult H1norm = feamer.computeErrorNorm(H1, delaunay);   
    std::cout << "done" << std::endl; 
    std::cout << "  Relative L2-norm    : " << utilities::toString(L2norm.NormValue) << std::endl;
    std::cout << "  Relative H1-seminorm: " << utilities::toString(H1norm.NormValue) << std::endl;
    std::cout << "  Element size        : " << utilities::toString(L2norm.MaxEdge) << std::endl;    
    
    std::cout << "+ Printing nodal displacement solution to a file ... ";
    feamer.writeDisplacements(dispFileName, x);
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
