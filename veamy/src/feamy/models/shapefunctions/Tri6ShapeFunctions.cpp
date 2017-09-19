#include <feamy/models/shapefunctions/Tri6ShapeFunctions.h>

Tri6ShapeFunctions::Tri6ShapeFunctions(Triangle t, std::vector<Point> points) : ShapeFunctions(t, points) {}

std::vector<double> Tri6ShapeFunctions::evaluateShapeFunction(Point p) {
    double L = 1 - p.getX() - p.getY();

    double N1 = p.getX()*(2*p.getX() - 1);
    double N2 = p.getY()*(2*p.getY() - 1);
    double N3 = L*(2*L - 1);
    double N4 = 4*p.getX()*p.getY();
    double N5 = 4*p.getY()*L;
    double N6 = 4*L*p.getX();

    std::vector<double> N = {N1, N4, N2, N5, N3, N6};

    return N;
}

std::vector<Pair<double>> Tri6ShapeFunctions::evaluateDerivatives(Point p) {
    Pair<double> dN1(4*p.getX() - 1, 0);
    Pair<double> dN2(0, 4*p.getY() - 1);
    Pair<double> dN3(-3 + 4*p.getX() + 4*p.getY(), -3 + 4*p.getX() + 4*p.getY());
    Pair<double> dN4(4*p.getY(), 4*p.getX());
    Pair<double> dN5(-4*p.getY(), 4 - 4*p.getX() - 8*p.getY());
    Pair<double> dN6(4 - 4*p.getY() - 8*p.getX(), -4*p.getX());

    std::vector<Pair<double>> dN = {dN1, dN4, dN2, dN5, dN3, dN6};
    return dN;
}

Point Tri6ShapeFunctions::evaluateRealPoint(Point point) {
    std::vector<double> N = evaluateShapeFunction(point);

    double x = N[0]*p[0].getX() + N[1]*p[1].getX() + N[2]*p[2].getX() + N[3]*p[3].getX() + N[4]*p[4].getX() + N[5]*p[5].getX();
    double y = N[0]*p[0].getY() + N[1]*p[1].getY() + N[2]*p[2].getY() + N[3]*p[3].getY() + N[4]*p[4].getY() + N[5]*p[5].getY();

    return Point(x,y);
}

std::vector<double> Tri6ShapeFunctions::evaluateShapeFunctionCartesian(Point point) {
    return std::vector<double>();
}
