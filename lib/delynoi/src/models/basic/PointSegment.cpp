#include <delynoi/models/basic/PointSegment.h>

PointSegment::PointSegment(Point p1, Point p2) : Segment<Point>(p1, p2) {}

PointSegment::PointSegment() : Segment<Point>(){}

bool PointSegment::contains(Point point) {
    return Segment::contains(point,p1,p2);
}

double PointSegment::length() {
    return Segment::length(this->p1, this->p2);
}

std::string PointSegment::getString() const {
    return this->getFirst().getString() + " " + this->getSecond().getString();
}

double PointSegment::cartesianAngle() {
    return Segment::cartesianAngle(this->p1, this->p2);
}

bool PointSegment::operator==(const PointSegment& other) const {
    return getFirst()==other.getFirst() && getSecond()==other.getSecond() ||
           getFirst()==other.getSecond() && getSecond()==other.getFirst();
}


