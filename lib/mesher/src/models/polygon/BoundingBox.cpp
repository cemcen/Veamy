#include <mesher/models/polygon/BoundingBox.h>
#include <mesher/models/polygon/Polygon.h>
#include <climits>

BoundingBox::BoundingBox(Point p1, Point p2) {
    this->p1 = p1;
    this->p2 = p2;
}

Point BoundingBox::getFirst() const {
    return this->p1;
}

Point BoundingBox::getSecond() const {
    return this->p2;
}

double BoundingBox::getWidth() {
    return std::abs(p1.getX() - p2.getX());
}

double BoundingBox::getHeight() {
    return std::abs(p1.getY() - p2.getY());
}

double BoundingBox::xMin() {
    return std::min(p1.getX(), p2.getX());
}

double BoundingBox::yMin() {
    return std::min(p1.getY(), p2.getY());
}

double BoundingBox::xMax() {
    return std::max(p1.getX(), p2.getX());
}

double BoundingBox::yMax() {
    return std::max(p1.getY(), p2.getY());
}

bool BoundingBox::operator==(const BoundingBox &other) const {
    return getFirst()==other.getFirst() && getSecond()==other.getSecond() ||
           getSecond()==other.getFirst() && getFirst()==other.getSecond();
}

void BoundingBox::getSegments(std::vector<PointSegment> &segments) {
    Point p3 (p2.getX(), p1.getY());
    Point p4 (p1.getX(), p2.getY());

    segments.push_back(PointSegment(p1,p3));
    segments.push_back(PointSegment(p3,p2));
    segments.push_back(PointSegment(p2,p4));
    segments.push_back(PointSegment(p4,p1));
}

bool BoundingBox::fitsInsidePolygon(Polygon poly, std::vector<Point> points) {
    bool result = true;
    std::vector<PointSegment> segs;
    this->getSegments(segs);

    if(!poly.containsPoint(points, this->centroid())){
        return false;
    }

    for(PointSegment segment: segs){
        result = !poly.intersectsSegment(segment, points) && result;
    }

    if(result){
        return !contains(points[poly.getPoint(0)]);
    } else{
        return false;
    }


}

bool BoundingBox::intersects(BoundingBox box) {
    MesherConfig* config = MesherConfig::instance();

    double left1 = this->xMin();
    double left2 = box.xMin();

    double right1 = this->xMax();
    double right2 = box.xMax();

    double up1 = this->yMax();
    double up2 = box.yMax();

    double down1 = this->yMin();
    double down2 = box.yMin();

    bool val = left1>right2 || std::abs(left1-right2)<config->getTolerance() ||
               right1<left2 || std::abs(left2-right1)<config->getTolerance() ||
               up1<down2 || std::abs(up1-down2)<config->getTolerance() ||
               down1>up2 || std::abs(up2-down1)<config->getTolerance();

    return !val;
}

Point BoundingBox::getClosestTo(Point p) {
    std::vector<Point> points = getPoints();
    double minDistance = LLONG_MAX;
    Point closest;

    for(Point point : points){
        double distance = p.distance(point);
        if(distance<minDistance){
            minDistance = distance;
            closest = point;
        }
    }

    return closest;
}

Point BoundingBox::centroid() {
    return Point(xMin() + getWidth()/2, yMin() + getHeight()/2);
}

std::vector<Point> BoundingBox::getPoints() {
    std::vector<Point> points;

    points.push_back(this->p1);
    points.push_back(Point(this->p2.getX(), this->p1.getY()));
    points.push_back(this->p2);
    points.push_back(Point(this->p1.getX(), this->p2.getY()));

    return points;
}

bool BoundingBox::contains(Point p) {
    return p.getX()>=xMin() && p.getX()<=xMax() && p.getY()>=yMin() && p.getY()<=yMax();
}
