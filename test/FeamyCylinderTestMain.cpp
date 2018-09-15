#include <delynoi/models/basic/Point.h>
#include <delynoi/utilities/delynoi_utilities.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <delynoi/models/hole/CircularHole.h>
#include <veamy/models/constraints/EssentialConstraints.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/models/constraints/values/Function.h>
#include <veamy/physics/materials/Material.h>
#include <veamy/physics/materials/MaterialPlaneStrain.h>
#include <veamy/physics/conditions/Conditions.h>
#include <veamy/Veamer.h>
#include <feamy/Feamer.h>
#include <feamy/models/constructor/Tri3Constructor.h>
#include <veamy/config/VeamyConfig.h>
#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include <feamy/problem/FeamyLinearElasticityDiscretization.h>
#include <utilities/utilities.h>

double innerForceX(double x, double y){
    if(x==0){
        return 0;
    }else{
        double alpha = std::atan2(y, x);
        return std::cos(alpha);
    }
}

double innerForceY(double x, double y){
    if(x==0){
        return 1;
    }else{
        double alpha = std::atan2(y, x);
        return std::sin(alpha);
    }
}

int main(){
    
    // Usage example of Feamy, the FEM module of Veamy, to solve problems with 3-node triangular FE elements
    // Problem: infinite cylinder subjected to internal pressure   
    
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
    std::string geoFileName = "quarter_circle_geo_file.txt";    
    std::string meshFileName = "cylinder_fem_mesh.txt";
    std::string dispFileName = "cylinder_fem_displacements.txt";
	
    std::cout << "*** Starting Veamy --> Feamy module ***" << std::endl;
    std::cout << "--> Test: Infinite cylinder subjected to internal pressure using 3-node triangular elements  <--" << std::endl;
    std::cout << "..." << std::endl;

    std::vector<Point> quarter_circle_points = {Point(0,0)};
    std::vector<Point> quarter = delynoi_utilities::generateArcPoints(Point(0,0), 9, 0, 90.0);
    quarter_circle_points.insert(quarter_circle_points.end(), quarter.begin(), quarter.end());

    Region quarter_circle(quarter_circle_points);
    Hole circular = CircularHole(Point(0,0), 3);
    quarter_circle.addHole(circular);

    quarter_circle.printInFile(geoFileName);

    std::vector<Point> regionPoints = quarter_circle.getRegionPoints();
    std::vector<PointSegment> segments = {PointSegment(regionPoints[12], regionPoints[13]), PointSegment(regionPoints[13], regionPoints[14]),
                                          PointSegment(regionPoints[14], regionPoints[15])};

    quarter_circle.generateSeedPoints(PointGenerator(functions::constantAlternating(), functions::constant()), 10, 10);
    std::vector<Point> seeds = quarter_circle.getSeedPoints();
    TriangleDelaunayGenerator meshGenerator = TriangleDelaunayGenerator (seeds, quarter_circle);
    Mesh<Triangle> mesh = meshGenerator.getConformingDelaunayTriangulation();

    mesh.printInFile(meshFileName);

    Material* material = new MaterialPlaneStrain (1000, 0.3);
    LinearElasticityConditions* conditions = new LinearElasticityConditions(material);

    PointSegment downSide(Point(3,0), Point(9,0));
    SegmentConstraint const1 (downSide, mesh.getPoints(), new Constant(0));
    conditions->addEssentialConstraint(const1, mesh.getPoints(), elasticity_constraints::Direction::Vertical);

    PointSegment leftSide(Point(0,3), Point(0,9));
    SegmentConstraint const2 (leftSide, mesh.getPoints(), new Constant(0));
    conditions->addEssentialConstraint(const2, mesh.getPoints(), elasticity_constraints::Direction::Horizontal);

    Function* innerX = new Function(innerForceX);
    Function* innerY = new Function(innerForceY);

    SegmentConstraint const3 (segments, mesh.getPoints(), innerX);
    SegmentConstraint const4 (segments, mesh.getPoints(), innerY);
    conditions->addNaturalConstraint(const3, mesh.getPoints(), elasticity_constraints::Direction::Horizontal);
    conditions->addNaturalConstraint(const4, mesh.getPoints(), elasticity_constraints::Direction::Vertical);

    FeamyLinearElasticityDiscretization* problem = new FeamyLinearElasticityDiscretization(conditions);

    Feamer f(problem);
    FeamyElementConstructor* constructor = new Tri3Constructor();
    f.initProblem(mesh, constructor);

    Eigen::VectorXd x = f.simulate(mesh);
    
    std::cout << "+ Printing nodal displacement solution to a file ... ";
    f.writeDisplacements(dispFileName, x);
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
