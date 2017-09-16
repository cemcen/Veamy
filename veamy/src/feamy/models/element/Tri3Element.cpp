#include <feamy/models/element/Tri3Element.h>

Tri3Element::Tri3Element(Conditions& conditions, Triangle t, UniqueList<Point>& points, DOFS& out) {
    ShapeFunctions* N = new Tri3ShapeFunctions(t, points.getList());
    FemElement::initializeElement(conditions, t, points, out, N);
}

