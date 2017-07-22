#include <veamy/models/dof/DOF.h>

DOF::DOF(int index, int point_index, DOF::Axis a) {
    this->index = index;
    this->point_index = point_index;
    this->d = a;
}

int DOF::globalIndex() const{
    return this->index;
}

int DOF::pointIndex() {
    return this->point_index;
}

bool DOF::operator==(const DOF &other) const {
    return this->index == other.index && this->d == other.d;
}

bool DOF::operator<(const DOF &other) const {
    if(this->index==other.index){
        return this->d<other.d;
    }

    return this->index<other.index;
}

DOF::Axis DOF::getAxis() {
    return this->d;
}



