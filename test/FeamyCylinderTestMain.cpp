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
#include <veamy/physics/Conditions.h>
#include <veamy/Veamer.h>
#include <feamy/Feamer.h>
#include <feamy/models/constructor/Tri3Constructor.h>
#include <veamy/config/VeamyConfig.h>

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
    VeamyConfig::instance()->setPrecision(Precision::precision::mid);

    std::vector<Point> quarter_circle_points = {Point(0,0)};
    std::vector<Point> quarter = delynoi_utilities::generateArcPoints(Point(0,0), 9, 0, 90.0);
    quarter_circle_points.insert(quarter_circle_points.end(), quarter.begin(), quarter.end());

    Region quarter_circle(quarter_circle_points);
    Hole circular = CircularHole(Point(0,0), 3);
    quarter_circle.addHole(circular);

    quarter_circle.printInFile("quarter_file.txt");

    std::vector<Point> regionPoints = quarter_circle.getRegionPoints();
    std::vector<PointSegment> segments = {PointSegment(regionPoints[12], regionPoints[13]), PointSegment(regionPoints[13], regionPoints[14]),
                                          PointSegment(regionPoints[14], regionPoints[15])};

    quarter_circle.generateSeedPoints(PointGenerator(functions::constantAlternating(), functions::constant()), 10, 10);
    std::vector<Point> seeds = quarter_circle.getSeedPoints();
    TriangleDelaunayGenerator meshGenerator = TriangleDelaunayGenerator (seeds, quarter_circle);
    Mesh<Triangle> mesh = meshGenerator.getConformingDelaunayTriangulation();

    mesh.printInFile("cylinderMesh_fem.txt");

    EssentialConstraints essential;
    PointSegment downSide(Point(3,0), Point(9,0));
    SegmentConstraint const1 (downSide, mesh.getPoints(), Constraint::Direction::Vertical, new Constant(0));
    essential.addConstraint(const1, mesh.getPoints());

    PointSegment leftSide(Point(0,3), Point(0,9));
    SegmentConstraint const2 (leftSide, mesh.getPoints(), Constraint::Direction::Horizontal, new Constant(0));
    essential.addConstraint(const2, mesh.getPoints());

    NaturalConstraints natural;

    Function* innerX = new Function(innerForceX);
    Function* innerY = new Function(innerForceY);

    SegmentConstraint const3 (segments, mesh.getPoints(), Constraint::Direction::Horizontal, innerX);
    SegmentConstraint const4 (segments, mesh.getPoints(), Constraint::Direction::Vertical, innerY);
    natural.addConstraint(const3, mesh.getPoints());
    natural.addConstraint(const4, mesh.getPoints());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh.getPoints());
    container.addConstraints(natural, mesh.getPoints());

    Material* material = new MaterialPlaneStrain (1000, 0.3);
    Conditions conditions(container, material);

    Feamer f;
    FeamyElementConstructor* constructor = new Tri3Constructor();
    f.initProblem(mesh, conditions, constructor);

    Eigen::VectorXd x = f.simulate(mesh);
    f.writeDisplacements("cylinder_displacements_fem.txt", x);
}