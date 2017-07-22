#include <veamy/models/Edge.h>

Edge::Edge(int p1, int p2) {
    this->p1 = p1;
    this->p2 = p2;
}

Pair<double> Edge::getNormal(std::vector<Point> points) {
    Point P1 = points[p1];
    Point P2 = points[p2];

    return Pair<double>((P2.getY()-P1.getY()), -(P2.getX()-P1.getX()));
}

double Edge::getLength(std::vector<Point> points) {
    Point P1 = points[p1];
    Point P2 = points[p2];

    return sqrt(pow(P1.getX() - P2.getX(),2) + pow(P1.getY() - P2.getY(), 2));
}
