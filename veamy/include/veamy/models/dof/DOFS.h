#ifndef VEAMY_DOFS_H
#define VEAMY_DOFS_H

#include <array>
#include <algorithm>
#include <veamy/utilities/SegmentPair.h>
#include <veamy/models/constraints/ConstraintsContainer.h>

template <class T>
class DOFS {
protected:
    UniqueList<DOF> list;
    std::unordered_map<int, int> occupied_point_indexes;
public:
    virtual T addDOF(ConstraintsContainer &constraints, std::vector<Point> points, int point_index,
                     SegmentPair pair) = 0;
    UniqueList<DOF> getDOFS();
    int size();
    DOF get(int i);

    virtual T pointToDOFS(int point) = 0;
};


#endif
