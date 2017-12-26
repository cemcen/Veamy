#include <veamy/models/dof/DOFS.h>

UniqueList<DOF> DOFS:: getDOFS() {
    return this->list;
}

int DOFS::size() {
    return list.size();
}

DOF DOFS::get(int i) {
    return list[i];
}






