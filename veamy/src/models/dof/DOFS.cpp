#include <veamy/models/dof/DOFS.h>

Pair<int> DOFS::addDOF(ConstraintsContainer &constraints, std::vector<Point> points, int point_index,
                       SegmentPair pair) {

    std::unordered_map<int,int>::iterator it = occupied_point_indexes.find(point_index);

    if(it!=occupied_point_indexes.end()){
        int outerDOF_index = it->second;

        return Pair<int>(outerDOF_index, outerDOF_index+1);
    }

    DOF newDOF = DOF(list.size(),point_index, DOF::Axis::x);
    DOF newDOF2 = DOF(list.size()+1,point_index, DOF::Axis::y);

    int newIndex = list.push_back(newDOF);
    list.push_back(newDOF2);

    constraints.addConstrainedDOF(points, newIndex, DOF::Axis::x, pair, point_index);
    constraints.addConstrainedDOF(points, newIndex + 1, DOF::Axis::y, pair, point_index);

    occupied_point_indexes[point_index] = newIndex;
    Pair<int> dofPair(newIndex, newIndex+1);

    return dofPair;
}

UniqueList<DOF> DOFS:: getDOFS() {
    return this->list;
}

int DOFS::size() {
    return list.size();
}

DOF DOFS::get(int i) {
    return list[i];
}

Pair<int> DOFS::pointToDOFS(int point) {
    int dofIndex = occupied_point_indexes[point];

    return Pair<int>(dofIndex, dofIndex+1);
}





