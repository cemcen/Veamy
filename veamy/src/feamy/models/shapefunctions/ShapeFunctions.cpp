#include <feamy/models/shapefunctions/ShapeFunctions.h>

ShapeFunctions::ShapeFunctions() {}

ShapeFunctions::ShapeFunctions(Triangle elem, std::vector<Point> meshPoints) {
    this->area = elem.getArea();

    std::vector<Point> points = elem.getPoints(meshPoints);
    this->p.assign(points.begin(), points.end());
}

int ShapeFunctions::numberOfShapeFunctions() {
    return this->p.size();
}
