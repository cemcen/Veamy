#ifndef VEAMY_CONSTRAINTSCONTAINER_H
#define VEAMY_CONSTRAINTSCONTAINER_H

#include <mesher/models/PolygonalMesh.h>
#include "EssentialConstraints.h"
#include "NaturalConstraints.h"

class ConstraintsContainer {
private:
    EssentialConstraints essential;
    NaturalConstraints natural;

    bool areConsistent(NaturalConstraints n, EssentialConstraints e, PolygonalMesh mesh);
public:
    ConstraintsContainer();
    void addConstraints(NaturalConstraints c, PolygonalMesh mesh);
    void addConstraints(EssentialConstraints c, PolygonalMesh mesh);

    void addConstrainedDOF(std::vector<Point> points, int DOF_index,DOF::Axis axis, SegmentPair pair);

    EssentialConstraints getEssentialConstraints();
    NaturalConstraints getNaturalConstraints();
};


#endif
