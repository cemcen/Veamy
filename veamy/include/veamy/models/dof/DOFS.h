#ifndef VEAMY_DOFS_H
#define VEAMY_DOFS_H

#include <array>
#include <algorithm>
#include <veamy/utilities/SegmentPair.h>
#include <veamy/models/constraints/ConstraintsContainer.h>

class DOFS {
protected:
    UniqueList<DOF> list;
    std::unordered_map<int, int> occupied_point_indexes;
    int n_dofs;
public:
    DOFS(int n_dofs);

    std::vector<int> addDOF(ConstraintsContainer &constraints, std::vector<Point> points, int point_index,
                     SegmentPair pair);
    UniqueList<DOF> getDOFS();
    int size();
    DOF get(int i);

    std::vector<int> pointToDOFS(int point);
};


#endif
