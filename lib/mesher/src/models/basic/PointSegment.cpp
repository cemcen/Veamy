#include <mesher/models/basic/PointSegment.h>

PointSegment::PointSegment(Point p1, Point p2) : Segment<Point>(p1, p2) {}

PointSegment::PointSegment() : Segment<Point>(){}

double PointSegment::length() {
    return Segment::length(this->p1, this->p2);
}

bool PointSegment::isBoundary(std::vector<Point> p) {
    return this->p1.isInBoundary() && this->p2.isInBoundary();
}

bool PointSegment::contains(Point point) {
    return Segment::contains(point,p1,p2);
}

std::string PointSegment::getString() const {
    return this->getFirst().getString() + " " + this->getSecond().getString();
}

double PointSegment::cartesianAngle() {
    return Segment::cartesianAngle(this->p1, this->p2);
}

bool PointSegment::operator==(const PointSegment other) const {
    return getFirst()==other.getFirst() && getSecond()==other.getSecond() ||
           getFirst()==other.getSecond() && getSecond()==other.getFirst();
}

bool PointSegment::intersection(PointSegment other, Point &inter) {
    return Segment::intersects(this->p1, this->p2, other.getFirst(), other.getSecond(), inter);
}

bool PointSegment::intersectionInfinite(Point p1, Point p2, Point &inter) {
    return Segment::intersectionInfinite(p1,p2,this->p1, this->p2, inter);
}

Pair<double> PointSegment::getSlope() {
    return Pair<double>(getSecond().getX() - getFirst().getX(), getSecond().getY() - getFirst().getY());
}

bool PointSegment::splitSegment(Point splitPoint, std::vector<PointSegment> &newSegments) {
    bool contains = this->contains(splitPoint);

    if(contains && !(splitPoint==this->getFirst() || splitPoint==this->getSecond())){
        newSegments.push_back(PointSegment(this->getFirst(), splitPoint));
        newSegments.push_back(PointSegment(splitPoint, this->getSecond()));

        return true;
    }

    return false;
}
