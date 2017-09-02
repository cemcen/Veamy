#include <mesher/models/basic/Point.h>
#include <mesher/config/MesherConfig.h>

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

Point::Point() {
    this->x = 0;
    this->y = 0;
}

double Point::getX() const{
    return this->x;
}

double Point::getY() const{
    return this->y;
}

std::string Point::getString() const{
    return utilities::toStringWithPrecision(this->getX(), MesherConfig::instance()->getPrecision())
           + " " + utilities::toStringWithPrecision(this->getY(), MesherConfig::instance()->getPrecision());
}

double Point::squareNorm() {
    return pow(this->getX(),2) + pow(this->getY(),2);
}

bool Point::operator==(const Point &other) const{
    MesherConfig* config = MesherConfig::instance();

    return std::abs(this->x-other.x)<config->getTolerance() &&
           std::abs(this->y-other.y)<config->getTolerance();
}


Point Point::operator-(const Point &other) {
    return Point(this->x - other.x, this->y - other.y);
}

bool Point::isInBoundary() {
    return this->isBoundaryPoint;
}

void Point::setBoundary() {
    this->isBoundaryPoint = true;
}

void Point::setX(double newX) {
    this->x = newX;
}

void Point::setY(double newY) {
    this->y = newY;
}

bool Point::operator<(const Point &other) const {
    MesherConfig* config = MesherConfig::instance();

    if(std::abs(this->x-other.x)<config->getTolerance()){
        if(std::abs(this->y-other.y)<config->getTolerance()){
            return false;
        }
        return this->y<other.y;
    }

    return this->x<other.x;
}

void Point::deform(double dX, double dY) {
    this->x = this->x + dX;
    this->y = this->y + dY;
}

double Point::distance(Point p) {
    return (*this - p).squareNorm();
}
