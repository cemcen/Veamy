#include <feamy/models/shapefunctions/Tri3ShapeFunctions.h>

Tri3ShapeFunctions::Tri3ShapeFunctions(Triangle t, std::vector<Point> points) : ShapeFunctions(t, points){}

std::vector<double> Tri3ShapeFunctions::evaluateShapeFunction(Point point) {
    double N1 = point.getX();
    double N2 = point.getY();
    double N3 = 1 - point.getX() - point.getY();

    std::vector<double> results = {N1, N2, N3};

    return results;
}

std::vector<Pair<double>> Tri3ShapeFunctions::evaluateDerivatives(Point point) {
    Pair<double> dN1 (1, 0);
    Pair<double> dN2 (0, 1);
    Pair<double> dN3 (-1, -1);

    std::vector<Pair<double>> results = {dN1, dN2, dN3};

    return results;
}
