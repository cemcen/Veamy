#include <veamy/utilities/veamy_functions.h>
#include <delynoi/models/polygon/Polygon.h>
#include <veamy/postprocess/utilities/norm_utilities.h>


namespace veamy_functions{
    double gauss_integration(Polygon poly, std::vector<Point>& points, int nGauss, Computable<Polygon>* computable){
        std::vector<Triangle> triangles;
        double result = 0;

        try {
            triangles = CenterTriangulationGenerator().triangulate(poly, points);
        } catch (std::invalid_argument& ex){
            triangles = EarTriangulationGenerator().triangulate(poly, points);
        }

        for (Triangle t: triangles){
            Eigen::MatrixXd gaussPoints;
            std::vector<double> weights;

            norm_utilities::triangle_rules(gaussPoints, t, weights, nGauss, points);

            for (int i = 0; i < gaussPoints.size(); ++i) {
                Point p = gaussPoints[i];

                result += computable->apply(p.getX(), p.getY(), 0, t)*weights[i];
            }
        }

        return result;

    }

    double none_function(double x, double y){
        return 0;
    }
}