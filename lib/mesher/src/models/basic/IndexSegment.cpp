#include <mesher/models/basic/IndexSegment.h>

IndexSegment::IndexSegment(int i1, int i2) : Segment<int>(i1, i2) {}

IndexSegment::IndexSegment(const IndexSegment &other) {
    this->p1 = other.p1;
    this->p2 = other.p2;
}

IndexSegment::IndexSegment() : Segment<int>(){}

IndexSegment::~IndexSegment() {}

bool IndexSegment::isBoundary(std::vector<Point> p) {
    return p[this->p1].isInBoundary() && p[this->p2].isInBoundary();
}

bool IndexSegment::contains(std::vector<Point> &p, Point point) {
    return Segment::contains(point,p[this->p1],p[this->p2]);
}

bool IndexSegment::contains(std::vector<Point> p, IndexSegment s) {
    return this->contains(p, p[s.getFirst()]) && this->contains(p, p[s.getSecond()]);
}

Point IndexSegment::middlePoint(std::vector<Point> p) {
    return Point((p[this->p1].getX() + p[this->p2].getX())/2, (p[this->p1].getY() + p[this->p2].getY())/2);
}

double IndexSegment::cartesianAngle(std::vector<Point> p) {
    return Segment::cartesianAngle(p[this->p1], p[this->p2]);
}

bool IndexSegment::intersection(std::vector<Point> points, PointSegment other, Point &inter) {
    return Segment::intersects(points[this->p1],points[this->p2],other.getFirst(),other.getSecond(), inter);
}

bool IndexSegment::intersection(std::vector<Point> points, IndexSegment other, Point &inter) {
    return Segment::intersects(points[this->p1],points[this->p2], points[other.getFirst()], points[other.getSecond()], inter);
}

void IndexSegment::orderCCW(std::vector<Point> points, Point center) {
    if(!this->isCCW(points, center)){
        int tmp = this->p1;
        this->p1 = this->p2;
        this->p2 = tmp;
    }
}

bool IndexSegment::isCCW(std::vector<Point> points, Point center) {
    Point p1 = points[this->p1];
    Point p2 = points[this->p2];

    return xpoly_utilities::orientation(p1,p2,center)>0;
}

std::string IndexSegment::getString() const {
    return utilities::toString<double>(this->getFirst()) + " " + utilities::toString<double>(this->getSecond());
}

bool IndexSegment::operator==(const IndexSegment& other) const {
    return getFirst()==other.getFirst() && getSecond()==other.getSecond() ||
           getFirst()==other.getSecond() && getSecond()==other.getFirst();
}

bool IndexSegment::operator<(const IndexSegment &other) const {
    if(this->p1==other.p1){
        return this->p2<other.p2;
    }

    return this->p1<other.p1;
}

double IndexSegment::length(std::vector<Point>& points) {
    return Segment::length(points[this->p1], points[this->p2]);
}

bool IndexSegment::isInCorner(Point p, std::vector<Point> points, int& i) {
    if(points[this->p1]==p){
        i = this->p1;
        return true;
    }

    if(points[this->p2]==p){
        i = this->p2;
        return true;
    }

    return false;
}

bool IndexSegment::isContained(PointSegment s, std::vector<Point> p) {
    return s.contains(p[this->p1]) && s.contains(p[this->p2]);
}

IndexSegment IndexSegment::add(int o) {
    return IndexSegment(this->p1 + o, this->p2 + o);
}

bool IndexSegment::isEndPoint(Point p, std::vector<Point> points) {
    return p == points[this->getFirst()] || p == points[this->getSecond()];
}

PointSegment IndexSegment::toPointSegment(std::vector<Point> points) {
    return PointSegment(points[this->getFirst()], points[this->getSecond()]);
}
