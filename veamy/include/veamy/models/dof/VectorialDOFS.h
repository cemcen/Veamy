#ifndef VEAMY_VECTORIALDOFS_H
#define VEAMY_VECTORIALDOFS_H

#include "DOFS.h"

class VectorialDOFS : public DOFS {
public:
    Pair<int> addDOF(ConstraintsContainer &constraints, std::vector<Point> points, int point_index,
               SegmentPair pair);
    Pair<int> pointToDOFS(int point);
};

#endif