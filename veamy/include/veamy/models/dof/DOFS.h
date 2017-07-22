#ifndef VEAMY_DOFS_H
#define VEAMY_DOFS_H

#include <array>
#include <algorithm>
#include <veamy/utilities/SegmentPair.h>
#include <veamy/models/constraints/ConstraintsContainer.h>

class DOFS {
private:
    UniqueList<DOF> list;
    std::unordered_map<int, int> occupied_point_indexes;
public:
    Pair<int> addDOF(ConstraintsContainer &constraints, std::vector<Point> points, int point_index,
                     SegmentPair pair);
    UniqueList<DOF> getDOFS();
    int size();
    DOF get(int i);

    Pair<int> pointToDOFS(int point);
};


#endif
