#ifndef VEAMY_SCALARDOFS_H
#define VEAMY_SCALARDOFS_H

#include "DOFS.h"

class ScalarDOFS : public DOFS<int>{
public:
    int addDOF(ConstraintsContainer &constraints, std::vector<Point> points, int point_index,
             SegmentPair pair);
    int pointToDOFS(int point);
};

#endif