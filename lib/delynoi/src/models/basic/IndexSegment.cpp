#include <delynoi/models/basic/IndexSegment.h>

IndexSegment::IndexSegment(int i1, int i2) : Segment<int>(i1, i2) {
    this->hash = utilities::hash32(i1) + utilities::hash32(i2);
}

IndexSegment::IndexSegment(const IndexSegment &other) {
    this->p1 = other.p1;
    this->p2 = other.p2;

    this->hash = utilities::hash32(this->p1) + utilities::hash32(this->p2);
}

IndexSegment::IndexSegment() : Segment<int>(){}

bool IndexSegment::contains(const std::vector<Point> &p, Point point) {
    return Segment::contains(point,p[this->p1],p[this->p2]);
}

bool IndexSegment::contains(const std::vector<Point>& p, IndexSegment s) {
    return this->contains(p, p[s.getFirst()]) && this->contains(p, p[s.getSecond()]);
}

Point IndexSegment::middlePoint(const std::vector<Point>& p) {
    return Point((p[this->p1].getX() + p[this->p2].getX())/2, (p[this->p1].getY() + p[this->p2].getY())/2);
}

double IndexSegment::cartesianAngle(const std::vector<Point>& p) {
    return Segment::cartesianAngle(p[this->p1], p[this->p2]);
}

bool IndexSegment::intersection(const std::vector<Point>& points, PointSegment other, Point &inter) {
    return Segment::intersects(points[this->p1],points[this->p2],other.getFirst(),other.getSecond(), inter);
}

bool IndexSegment::intersection(const std::vector<Point>& points, IndexSegment other, Point &inter) {
    return Segment::intersects(points[this->p1],points[this->p2], points[other.getFirst()], points[other.getSecond()], inter);
}

void IndexSegment::orderCCW(const std::vector<Point>& points, Point center) {
    if(!this->isCCW(points, center)){
        int tmp = this->p1;
        this->p1 = this->p2;
        this->p2 = tmp;
    }
}

bool IndexSegment::isCCW(const std::vector<Point>& points, Point center) {
    Point p1 = points[this->p1];
    Point p2 = points[this->p2];

    return delynoi_utilities::orientation(p1,p2,center)>0;
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

double IndexSegment::length(const std::vector<Point>& points) {
    return Segment::length(points[this->p1], points[this->p2]);
}

bool IndexSegment::isContained(PointSegment s, const std::vector<Point>& p) {
    return s.contains(p[this->p1]) && s.contains(p[this->p2]);
}

IndexSegment IndexSegment::add(int o) {
    return IndexSegment(this->p1 + o, this->p2 + o);
}

