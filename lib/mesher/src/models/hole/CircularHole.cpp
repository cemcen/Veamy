#include <mesher/models/hole/CircularHole.h>

CircularHole::CircularHole(Point p, double r) : Circle(r, p){
    this->HolePoints = discretizeCircle();
    Hole::center = Circle::center;
    computeSegments();
}

void CircularHole::computeSegments() {
    std::vector<int> indexes;
    xpoly_utilities::TrivialIndexVector(indexes, (int) this->HolePoints.size());

    Polygon discretePolygon (indexes, this->HolePoints);
    discretePolygon.getSegments(this->segments);
}








