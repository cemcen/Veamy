#include <vector>
#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleDelaunayGenerator.h>
#include <feamy/Feamer.h>
#include <veamy/models/constraints/values/Function.h>
#include <veamy/physics/materials/MaterialPlaneStrain.h>
#include <feamy/models/constructor/Tri3Constructor.h>
#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include <feamy/problem/FeamyLinearElasticityDiscretization.h>
#include <utilities/utilities.h>
#include <veamy/config/VeamyConfig.h>
#include <veamy/postprocess/L2NormCalculator.h>
#include <veamy/postprocess/H1NormCalculator.h>

double uXPatch(double x, double y){
    return x;
}

double uYPatch(double x, double y){
    return x + y;
}

std::vector<double> exactDisplacement(double x, double y){
    return {x, x+y};
}

std::vector<double> exactStrain(double x, double y){
    return {1,1,1};
    // the third component is defined as in FEM: 2*1/2*(dux/dy + duy/dx)   
}

int main() {
    
    // Usage example of Feamy, the FEM module of Veamy, to solve problems with 3-node triangular FE elements
    // Problem: displacement patch test   

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
    std::string meshFileName = "disp_patch_test_fem_mesh.txt";
    std::string dispFileName = "disp_patch_test_fem_displacements.txt";
	
    std::cout << "*** Starting Veamy --> Feamy module ***" << std::endl;
    std::cout << "--> Test: Displacement patch test using 3-node triangular elements  <--" << std::endl;
    std::cout << "..." << std::endl;       
    
    std::vector<Point> region_points = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Region square(region_points);
    square.generateSeedPoints(PointGenerator(functions::constant(), functions::displace_points(0.1)), 10, 10);

    std::vector<Point> seeds = square.getSeedPoints();
    TriangleDelaunayGenerator delaunayGenerator(seeds, square);
    Mesh<Triangle> delaunay = delaunayGenerator.getConformingDelaunayTriangulation();

    delaunay.printInFile(meshFileName);

    Material* material = new MaterialPlaneStrain (1, 0.2);
    LinearElasticityConditions* conditions = new LinearElasticityConditions(material);

    Function* uXConstraint = new Function(uXPatch);
    Function* uYConstraint = new Function(uYPatch);

    PointSegment leftSide(Point(0,0), Point(1,0));
    SegmentConstraint leftX (leftSide, delaunay.getPoints(), uXConstraint);
    conditions->addEssentialConstraint(leftX, delaunay.getPoints(), elasticity_constraints::Direction::Horizontal);
    SegmentConstraint  leftY (leftSide, delaunay.getPoints(), uYConstraint);
    conditions->addEssentialConstraint(leftY, delaunay.getPoints(), elasticity_constraints::Direction::Vertical);

    PointSegment downSide(Point(1,0), Point(1,1));
    SegmentConstraint downX (downSide, delaunay.getPoints(), uXConstraint);
    conditions->addEssentialConstraint(downX, delaunay.getPoints(), elasticity_constraints::Direction::Horizontal);
    SegmentConstraint  downY (downSide, delaunay.getPoints(), uYConstraint);
    conditions->addEssentialConstraint(downY, delaunay.getPoints(), elasticity_constraints::Direction::Vertical);

    PointSegment rightSide(Point(1,1), Point(0, 1));
    SegmentConstraint rightX (rightSide, delaunay.getPoints(), uXConstraint);
    conditions->addEssentialConstraint(rightX, delaunay.getPoints(), elasticity_constraints::Direction::Horizontal);
    SegmentConstraint  rightY (rightSide, delaunay.getPoints(), uYConstraint);
    conditions->addEssentialConstraint(rightY, delaunay.getPoints(), elasticity_constraints::Direction::Vertical);

    PointSegment topSide(Point(0, 1), Point(0, 0));
    SegmentConstraint topX (topSide, delaunay.getPoints(), uXConstraint);
    conditions->addEssentialConstraint(topX, delaunay.getPoints(), elasticity_constraints::Direction::Horizontal);
    SegmentConstraint  topY (topSide, delaunay.getPoints(), uYConstraint);
    conditions->addEssentialConstraint(topY, delaunay.getPoints(), elasticity_constraints::Direction::Vertical);

    FeamyElementConstructor* constructor = new Tri3Constructor();

    FeamyLinearElasticityDiscretization* problem = new FeamyLinearElasticityDiscretization(conditions);
    Feamer feamer(problem);
    feamer.initProblem(delaunay, constructor);

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
