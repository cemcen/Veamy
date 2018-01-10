#include <veamy/models/dof/DOFS.h>

DOFS::DOFS() {}

std::vector<int>
DOFS::addDOF(ConstraintsContainer &constraints, std::vector<Point> &points, int point_index, SegmentPair pair) {
    std::unordered_map<int,int>::iterator it = occupied_point_indexes.find(point_index);

    if(it!=occupied_point_indexes.end()){
        int outerDOF_index = it->second;
        std::vector<int> returnVector;

        for (int i = 0; i < n_dofs; ++i) {
            returnVector.push_back(outerDOF_index + i);
        }

        return returnVector;
    }

    std::vector<int> DOF_indexes;

    for (int j = 0; j < n_dofs; ++j) {
        DOF newDOF = DOF(list.size(),point_index, j);

        int newIndex = list.push_back(newDOF);
        constraints.addConstrainedDOF(points, newIndex, j, pair, point_index);

        DOF_indexes.push_back(newIndex);

        if(j==0){
            occupied_point_indexes[point_index] = newIndex;
        }
    }

    return DOF_indexes;
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

std::vector<int> DOFS::pointToDOFS(int point) {
    std::vector<int> indexes;
    int dofIndex = this->occupied_point_indexes[point];

    for (int i = 0; i < n_dofs; ++i) {
        indexes.push_back(dofIndex + i);
    }

    return indexes;
}

void DOFS::setNumberOfDOFS(int n_dofs) {
    this->n_dofs = n_dofs;
}

int DOFS::getNumberOfDOFS() {
    return this->n_dofs;
}


