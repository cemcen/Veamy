#include <veamy/config/VeamyConfig.h>
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

double uDirichlet(double x, double y){
    return x + y;
}

std::vector<double> exactScalarField(double x, double y){
    return {x+y};
}

std::vector<double> exactGradScalarField(double x, double y){
    return {1,1};
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
    std::string meshFileName = "poisson_patch_test_mesh.txt";
    std::string scalarFieldFileName = "poisson_patch_test_scalarfield.txt";

    std::cout << "*** Starting Veamy ***" << std::endl;
    std::cout << "--> Test: Poisson patch test <--" << std::endl;
    std::cout << "..." << std::endl;

    std::cout << "+ Defining the domain ... ";
    std::vector<Point> rectangle1x1_points = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Region rectangle1x1(rectangle1x1_points);
    std::cout << "done" << std::endl;

    std::cout << "+ Generating polygonal mesh ... ";
    rectangle1x1.generateSeedPoints(PointGenerator(functions::constantAlternating(), functions::constant()), 6, 6);
    std::vector<Point> seeds = rectangle1x1.getSeedPoints();
    TriangleVoronoiGenerator meshGenerator (seeds, rectangle1x1);
    Mesh<Polygon> mesh = meshGenerator.getMesh();
    std::cout << "done" << std::endl;

    std::cout << "+ Printing mesh to a file ... ";
    mesh.printInFile(meshFileName);
    std::cout << "done" << std::endl;

    std::cout << "+ Defining problem conditions ... ";
    PoissonConditions* conditions = new PoissonConditions();
    std::cout << "done" << std::endl;

    std::cout << "+ Defining Dirichlet and Neumann boundary conditions ... ";
    Function* uConstraint = new Function(uDirichlet);

    PointSegment leftSide(Point(0,0), Point(0,1));
    SegmentConstraint left (leftSide, mesh.getPoints(), uConstraint);
    conditions->addEssentialConstraint(left, mesh.getPoints());

    PointSegment downSide(Point(0,0), Point(1,0));
    SegmentConstraint down (downSide, mesh.getPoints(), uConstraint);
    conditions->addEssentialConstraint(down, mesh.getPoints());

    PointSegment rightSide(Point(1,0), Point(1, 1));
    SegmentConstraint right (rightSide, mesh.getPoints(), uConstraint);
    conditions->addEssentialConstraint(right, mesh.getPoints());

    PointSegment topSide(Point(0, 1), Point(1, 1));
    SegmentConstraint top (topSide, mesh.getPoints(), uConstraint);
    conditions->addEssentialConstraint(top, mesh.getPoints());
    std::cout << "done" << std::endl;

    std::cout << "+ Preparing the simulation ... ";
    VeamyPoissonDiscretization* problem = new VeamyPoissonDiscretization(conditions);

    Veamer v(problem);
    v.initProblem(mesh);
    std::cout << "done" << std::endl;

    std::cout << "+ Simulating ... ";
    Eigen::VectorXd x = v.simulate(mesh);
    std::cout << "done" << std::endl;

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
