#include <feamy/models/constructor/Tri3Constructor.h>
#include <feamy/models/shapefunctions/Tri3ShapeFunctions.h>

ShapeFunctions *Tri3Constructor::getShapeFunctions(Triangle &t, UniqueList<Point> &meshPoints) {
    return new Tri3ShapeFunctions(t, meshPoints.getList());
}

