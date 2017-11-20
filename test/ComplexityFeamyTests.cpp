#include <string>
#include <chrono>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <veamy/models/constraints/EssentialConstraints.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/Veamer.h>
#include <veamy/physics/materials/MaterialPlaneStrain.h>
#include <feamy/Feamer.h>
#include <feamy/models/constructor/Tri3Constructor.h>


int main() {
    int n = 10;
    int sizes[] = {2, 5, 8, 10, 7, 10, 15, 20, 25, 25};
    int sizes1[] = {5, 5, 8, 10, 15, 20, 20, 25, 30, 40};
    std::vector<Point> square_points = {Point(0, 0), Point(0, 100), Point(100, 100), Point(100, 0)};
    Region square(square_points);

    std::string voronoiResultsFile = "voronoiResults.txt";
    std::string femResultsFile = "femResults.txt";

    std::string path = utilities::getPath();

    std::ofstream voronoiFile, femFile;
    voronoiFile.open(path + voronoiResultsFile, std::ios::out);
    femFile.open(path + femResultsFile, std::ios::out);

    for (int i = 0; i < n; ++i) {
        square.generateSeedPoints(PointGenerator(functions::random_double(0, 100), functions::random_double(0, 100)),
                                  sizes[i], sizes1[i]);

        std::vector<Point> seeds = square.getSeedPoints();

        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        TriangleDelaunayGenerator g(square, seeds);
        Mesh<Triangle> m = g.getConformingDelaunayTriangulation();
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        voronoiFile << utilities::toString(sizes[i] * sizes1[i]) << " " << duration << std::endl;

        Feamer feamer;
        FeamyElementConstructor* constructor = new Tri3Constructor();

        EssentialConstraints c_vem;
        PointSegment constrained(Point(0, 0), Point(0, 100));
        SegmentConstraint const1_vem(constrained, m.getPoints().getList(), Constraint::Direction::Total, new Constant(0));

        c_vem.addConstraint(const1_vem, m.getPoints());

        NaturalConstraints natural_vem;
        PointSegment const3(Point(100, 0), Point(100, 100));
        SegmentConstraint constraint3_vem(const3, m.getPoints().getList(), Constraint::Direction::Horizontal,
                                      new Constant(1000));

        natural_vem.addConstraint(constraint3_vem, m.getPoints().getList());

        ConstraintsContainer container_vem;
        container_vem.addConstraints(c_vem, m.getPoints());
        container_vem.addConstraints(natural_vem, m.getPoints());

        Material *material = new MaterialPlaneStrain(Materials::material::Steel);
        Conditions conditions_vem(container_vem, material);

        t1 = std::chrono::high_resolution_clock::now();
        feamer.initProblem(m, conditions_vem, constructor);
        Eigen::VectorXd x_vem = feamer.simulate(m);
        t2 = std::chrono::high_resolution_clock::now();

        duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        femFile << utilities::toString(sizes[i] * sizes1[i]) << " " << duration << std::endl;
     }
}