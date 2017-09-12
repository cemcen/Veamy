#include <veamy/models/Element.h>
#include <veamy/physics/VeamyConditions.h>

template <typename T>
void Element<T>::initializeElement(VeamyConditions &conditions, T &p, UniqueList<Point> &points, DOFS &out) {
    std::vector<int> vertex = p.getPoints();
    int n = vertex.size();

    for(int i=0;i<n;i++) {
        SegmentPair pair(IndexSegment(vertex[(i - 1 + n) % n], vertex[i]),
                         IndexSegment(vertex[i], vertex[(i + 1) % n]));
        Pair<int> indexes = out.addDOF(conditions.constraints, points.getList(), vertex[i], pair);

        dofs.push_back(indexes.first);
        dofs.push_back(indexes.second);
    }

    this->p = p;
}

template <typename T>
T Element<T>::getAssociatedPolygon() {
    return this->p;
}

template <typename T>
void Element<T>::assemble(DOFS out, Eigen::MatrixXd &Kglobal, Eigen::VectorXd &Fglobal) {
    for (int i = 0; i < this->K.rows(); i++) {
        int globalI = out.get(this->dofs[i]).globalIndex();

        for (int j = 0; j < this->K.cols(); j++) {
            int globalJ = out.get(this->dofs[j]).globalIndex();

            Kglobal(globalI, globalJ) = Kglobal(globalI, globalJ) + this->K(i, j);
        }

        Fglobal(globalI) = Fglobal(globalI) + this->f(i);
    }
}
