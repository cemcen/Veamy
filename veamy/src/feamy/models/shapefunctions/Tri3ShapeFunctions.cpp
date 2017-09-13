#include <feamy/models/shapefunctions/Tri3ShapeFunctions.h>

Tri3ShapeFunctions::Tri3ShapeFunctions(Triangle t, std::vector<Point> points) : ShapeFunctions(t, points){}

std::vector<double> Tri3ShapeFunctions::evaluateShapeFunction(Point point) {
    double N1 = ((p[1].getX()*p[2].getY() - p[2].getX()*p[1].getY()) + (p[1].getY() - p[2].getY())*point.getX()
                 + (p[2].getX() - p[1].getX())*point.getY())/(2*area);
    double N2 = ((p[2].getX()*p[0].getY() - p[0].getX()*p[2].getY()) + (p[2].getY() - p[0].getY())*point.getX()
                 + (p[0].getX() - p[2].getX())*point.getY())/(2*area);
    double N3 = ((p[0].getX()*p[1].getY() - p[1].getX()*p[0].getY()) + (p[0].getY() - p[1].getY())*point.getX()
                 + (p[1].getX() - p[0].getX())*point.getY())/(2*area);

    std::vector<double> results = {N1, N2, N3};

    return results;
}

std::vector<Pair<double>> Tri3ShapeFunctions::evaluateDerivatives(Point point) {
    Pair<double> dN1 ((p[1].getY() - p[2].getY())/(2*area), (p[2].getX() - p[1].getX())/(2*area));
    Pair<double> dN2 ((p[2].getY() - p[0].getY())/(2*area), (p[0].getX() - p[2].getX())/(2*area));
    Pair<double> dN3 ((p[0].getY() - p[1].getY())/(2*area), (p[1].getX() - p[0].getX())/(2*area));

    std::vector<Pair<double>> results = {dN1, dN2, dN3};

    return results;
}
