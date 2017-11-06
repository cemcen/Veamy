#include <veamy/utilities/veamy_functions.h>
#include <delynoi/models/polygon/Polygon.h>

namespace veamy_functions{
    double nodal_quadrature(Polygon poly, std::vector<Point> points, Computable *f) {
        double result = 0;
        std::vector<int> polygonPoints = poly.getPoints();
        int n = (int) polygonPoints.size();

        IndexSegment prev;
        IndexSegment next;

        for (int i = 0; i < n; ++i) {
            prev = IndexSegment(polygonPoints[(n+i-1)%n], polygonPoints[i]);
            next = IndexSegment(polygonPoints[i], polygonPoints[(i+1)%n]);

            Point point = points[polygonPoints[i]];
            std::vector<Point> smallPolygon = {prev.middlePoint(points), points[polygonPoints[i]],
                                               next.middlePoint(points), poly.getCentroid()};

            double area = geometry_functions::area(smallPolygon);

            result += area*f->(point.getX(), point.getY(), polygonPoints[i]);
        }

        return result;
    }
}