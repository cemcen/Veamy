#include <delynoi/utilities/xpolyutilities.h>
#include <delynoi/models/polygon/Circle.h>
#include <delynoi/config/DelynoiConfig.h>

Circle::Circle(double r, Point c) {
    this->radius = r;
    this->center = c;
}

std::vector<Point> Circle::discretizeCircle() {
    DelynoiConfig* config = DelynoiConfig::instance();

    std::vector<Point> points;
    double delta = 360 / config->getDiscretizationGrade();

    double angle = 0;
    while (angle < 360) {
        double x = center.getX() + radius * cos(utilities::radian(angle));
        double y = center.getY() + radius * sin(utilities::radian(angle));

        points.push_back(Point(x, y));

        angle += delta;
    }

    return points;
}
