#include <algorithm>
#include <delynoi/models/polygon/Triangle.h>

Triangle::Triangle() {}

Triangle::Triangle(std::vector<int> points, std::vector<Point>& p) : Polygon(points, p) {
    this->circumcenter = this->calculateCircumcenter(p);
}

Point Triangle::getCircumcenter() {
    return this->circumcenter;
}

Point Triangle::calculateCircumcenter(std::vector<Point>& p){
    Point A = p[this->points[0]];
    Point B = p[this->points[1]];
    Point C = p[this->points[2]];

    double d = 2*(A.getX()*(B.getY() - C.getY()) + B.getX()*(C.getY() - A.getY()) + C.getX()*(A.getY() - B.getY()));

    double uX = (A.squareNorm()*(B.getY() - C.getY()) + B.squareNorm()*(C.getY() - A.getY()) + C.squareNorm()*(A.getY() - B.getY()))/d;
    double uY = (A.squareNorm()*(C.getX() - B.getX()) + B.squareNorm()*(A.getX() - C.getX()) + C.squareNorm()*(B.getX() - A.getX()))/d;

    return Point(uX,uY);
}

int Triangle::nextEdge(int center, EdgeData edge, std::unordered_map<Key, int, KeyHasher> edgeMap) {
    Key nextEdge = Key(center, thirdPoint(edge));

    return edgeMap[nextEdge];
}

int Triangle::thirdPoint(EdgeData edge) {
    if(this->points[0]==edge.p1){
        if(this->points[1]==edge.p2){
            return this->points[2];
        }
        return this->points[1];
    } else if(this->points[1]==edge.p1) {
        if(this->points[0]==edge.p2){
            return this->points[2];
        }
        return this->points[0];
    } else {
        if(this->points[0]==edge.p2){
            return this->points[1];
        }
        return this->points[0];
    }
}

bool Triangle::isNull() {
    return this->points.size()==0;
}
