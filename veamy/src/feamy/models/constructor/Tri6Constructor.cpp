#include <feamy/models/constructor/Tri6Constructor.h>
#include <feamy/models/element/Tri6Element.h>

FemElement *Tri6Constructor::createElement(Conditions& conditions, Triangle t, UniqueList<Point> &points, DOFS &out) {
    return new Tri6Element(conditions, t, points, out);
}
