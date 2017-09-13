#ifndef VEAMY_CONSTRAINTSCONTAINER_H
#define VEAMY_CONSTRAINTSCONTAINER_H

#include <delynoi/models/Mesh.h>
#include "EssentialConstraints.h"
#include "NaturalConstraints.h"

class ConstraintsContainer {
private:
    EssentialConstraints essential;
    NaturalConstraints natural;

    bool areConsistent(NaturalConstraints n, EssentialConstraints e, UniqueList<Point> points);
public:
    ConstraintsContainer();
    void addConstraints(NaturalConstraints c, UniqueList<Point> points);
    void addConstraints(EssentialConstraints c, UniqueList<Point> points);

    void addConstrainedDOF(std::vector<Point> points, int DOF_index, DOF::Axis axis, SegmentPair pair,
                               int point_index);

    EssentialConstraints getEssentialConstraints();
    NaturalConstraints getNaturalConstraints();
};


#endif
