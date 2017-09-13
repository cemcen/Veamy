#include <delynoi/models/basic/Segment.h>

template <class T>
Segment<T>::Segment(T p1, T p2) {
    if(p1==p2){
        throw std::runtime_error("A segment can not have zero length");
    }

    this->p1 = p1;
    this->p2 = p2;
}

template <class T>
Segment<T>::Segment() {}

template <class T>
Segment<T>::~Segment() {}

template <class T>
T Segment<T>::getFirst() const{
    return this->p1;
}

template <class T>
T Segment<T>::getSecond() const{
    return this->p2;
}

template <class T>
bool Segment<T>::contains(Point point, Point p1, Point p2) {
    DelynoiConfig* config = DelynoiConfig::instance();

    bool test1 = ((point.getX()>=p1.getX() || std::abs(point.getX()-p1.getX())<config->getTolerance()) && (point.getX()<=p2.getX() || std::abs(point.getX()-p2.getX())<config->getTolerance())) ||
                 ((point.getX()>=p2.getX() || std::abs(point.getX()-p2.getX())<config->getTolerance()) && (point.getX()<=p1.getX() || std::abs(point.getX()-p1.getX())<config->getTolerance()));
    bool test2 =  ((point.getY()>=p1.getY() || std::abs(point.getY()-p1.getY())<config->getTolerance()) && (point.getY()<=p2.getY() || std::abs(point.getY()-p2.getY())<config->getTolerance()) ||
                  ((point.getY()>=p2.getY() || std::abs(point.getY()-p2.getY())<config->getTolerance()) && (point.getY()<=p1.getY() || std::abs(point.getY()-p1.getY())<config->getTolerance())));

    return  test1 &&  test2 &&
            std::abs(p1.getX()*(p2.getY()-point.getY()) + p2.getX()*(point.getY()-p1.getY()) + point.getX()*(p1.getY()-p2.getY()))<config->getTolerance();
}

template <class T>
bool Segment<T>::isVertex(T p) {
    return this->p1==p || this->p2==p;
}

template <class T>
double Segment<T>::cartesianAngle(Point p1, Point p2) {
    double dY = p2.getY() - p1.getY();
    double dX = p2.getX() - p1.getX();

    return utilities::degrees(atan2(dY, dX));
}

template <class T>
bool Segment<T>::intersects(Point p1, Point p2, Point o1, Point o2, Point &inter) {
    double tolerance = DelynoiConfig::instance()->getTolerance();

    double s1_x, s1_y, s2_x, s2_y;
    s1_x = p2.getX() - p1.getX();     s1_y = p2.getY() - p1.getY();
    s2_x = o2.getX() - o1.getX();     s2_y = o2.getY() - o1.getY();

    double s, t;
    s = (-s1_y * (p1.getX() - o1.getX()) + s1_x * (p1.getY() - o1.getY())) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p1.getY() - o1.getY()) - s2_y * (p1.getX() - o1.getX())) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= (0-tolerance) && s <= (1+tolerance) && t >= (0-tolerance) && t <= (1+tolerance)){
        double i_x = p1.getX() + (t * s1_x);
        double i_y = p1.getY() + (t * s1_y);

        inter.setX(i_x);
        inter.setY(i_y);

        return true;
    }

    return false;
}

template <class T>
bool Segment<T>::intersectionInfinite(Point p1, Point p2, Point o1, Point o2, Point &inter) {
    double s1_x, s1_y, s2_x, s2_y;
    s1_x = p2.getX() - p1.getX();     s1_y = p2.getY() - p1.getY();
    s2_x = o2.getX() - o1.getX();     s2_y = o2.getY() - o1.getY();

    double s, t;
    s = (-s1_y * (p1.getX() - o1.getX()) + s1_x * (p1.getY() - o1.getY())) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p1.getY() - o1.getY()) - s2_y * (p1.getX() - o1.getX())) / (-s2_x * s1_y + s1_x * s2_y);

    if (t >= 0 && t <= 1){
        double i_x = p1.getX() + (t * s1_x);
        double i_y = p1.getY() + (t * s1_y);

        inter.setX(i_x);
        inter.setY(i_y);

        return true;
    }

    return false;
}

template <class T>
double Segment<T>::length(Point p1, Point p2) {
    return std::sqrt(std::pow(p1.getX() - p2.getX(), 2) + std::pow(p1.getY() - p2.getY(),2));
}

template class Segment<int>;
template class Segment<Point>;
