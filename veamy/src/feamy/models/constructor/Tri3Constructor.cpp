#include <feamy/models/constructor/Tri3Constructor.h>
#include <feamy/models/element/Tri3Element.h>

FemElement *Tri3Constructor::createElement(Conditions& conditions, Triangle t, UniqueList<Point> &points, DOFS &out) {
    return new Tri3Element(conditions, t, points, out);
}
