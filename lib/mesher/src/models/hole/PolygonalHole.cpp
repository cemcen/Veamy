#include <mesher/models/hole/PolygonalHole.h>

PolygonalHole::PolygonalHole(std::vector<Point>& p) : Polygon(p) {
    for(int i=0;i<p.size();i++){
        this->HolePoints.push_back(p.at(i));
    }
    this->center = this->getCentroid();
    Polygon::getSegments(this->segments);
}





