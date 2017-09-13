#include <feamy/models/element/Tri6Element.h>


Tri6Element::Tri6Element(Conditions conditions, Triangle t, UniqueList<Point> &points, DOFS &out) {
    ShapeFunctions* N = new Tri6ShapeFunctions(t, points.getList());

    std::vector<IndexSegment> segments;
    t.getSegments(segments);

    std::vector<int> trianglePoints = t.getPoints();
    std::vector<int> newTrianglePoints;

    int i = 0, n = trianglePoints.size();
    for(IndexSegment s: segments){
        Point middlePoint = s.middlePoint(points.getList());

        int index = points.push_back(middlePoint);
        newTrianglePoints.push_back(trianglePoints[i]);
        newTrianglePoints.push_back(index);
    }

    Triangle newTriangle(newTrianglePoints, points.getList());
    FemElement::initializeElement(conditions, newTriangle, points, out, N);
}

void Tri6Element::computeK(DOFS d, UniqueList<Point> points, Conditions &conditions) {

}
