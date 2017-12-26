#include <veamy/models/dof/ScalarDOFS.h>

int
ScalarDOFS::addDOF(ConstraintsContainer &constraints, std::vector<Point> points, int point_index, SegmentPair pair) {
    std::unordered_map<int,int>::iterator it = occupied_point_indexes.find(point_index);

    if(it!=occupied_point_indexes.end()){
        int outerDOF_index = it->second;

        return outerDOF_index;
    }

    DOF newDOF = DOF(list.size(),point_index);

    int newIndex = list.push_back(newDOF);

    constraints.addConstrainedDOF(points, newIndex, pair, point_index);

    occupied_point_indexes[point_index] = newIndex;
    return newIndex;
}

int ScalarDOFS::pointToDOFS(int point) {
    return this->occupied_point_indexes[point];
}
