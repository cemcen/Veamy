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

Point Tri3ShapeFunctions::evaluateRealPoint(Point point) {
    double x = p[2].getX() + (p[0].getX() - p[2].getX())*point.getX() + (p[1].getX() - p[2].getX())*point.getY();
    double y = p[2].getY() + (p[0].getY() - p[2].getY())*point.getX() + (p[1].getY() - p[2].getY())*point.getY();

    return Point(x,y);
}

std::vector<double> Tri3ShapeFunctions::evaluateShapeFunctionCartesian(Point point) {
    double N1 = (p[1].getX()*p[2].getY() - p[2].getX()*p[1].getY()) + (p[1].getY() - p[2].getY())*point.getX() + (p[2].getX() - p[1].getX())*point.getY();
    double N2 = (p[2].getX()*p[0].getY() - p[0].getX()*p[2].getY()) + (p[2].getY() - p[0].getY())*point.getX() + (p[0].getX() - p[2].getX())*point.getY();
    double N3 = (p[0].getX()*p[1].getY() - p[1].getX()*p[0].getY()) + (p[0].getY() - p[1].getY())*point.getX() + (p[1].getX() - p[0].getX())*point.getY();

    std::vector<double> results = {N1/(2*area), N2/(2*area), N3/(2*area)};

    return results;
}
