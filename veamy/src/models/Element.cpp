#include <veamy/models/Element.h>

template <typename T>
void Element<T>::initializeElement(Conditions *conditions, T &p, UniqueList<Point> &points, DOFS &out, int n_dofs) {
    std::vector<int> vertex = p.getPoints();
    int n = vertex.size();

    for(int i=0;i<n;i++) {
        SegmentPair pair(IndexSegment(vertex[(i - 1 + n) % n], vertex[i]),
                         IndexSegment(vertex[i], vertex[(i + 1) % n]));
        std::vector<int> indexes = out.addDOF(conditions->constraints, points.getList(), vertex[i], pair);

        for (int j = 0; j < indexes.size(); ++j) {
            dofs.push_back(indexes[j]);
        }
    }

    this->p = p;
    this->n_dofs = n_dofs;
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

template <typename T>
void Element<T>::computeF(DOFS d, UniqueList<Point> points, Conditions *conditions, BodyForceVector *bodyForceVector,
                          TractionVector *tractionVector) {
    int n = this->p.numberOfSides();
    int m = this->dofs.size();
    std::vector<IndexSegment> segments;
    this->p.getSegments(segments);

    this->f = Eigen::VectorXd::Zero(m);
    Eigen::VectorXd bodyForce = bodyForceVector->computeForceVector(conditions->f);

    for (int i = 0; i < n; ++i) {
        Eigen::VectorXd naturalConditions = tractionVector->computeTractionVector(segments[i]);

        for (int j = 0; j < this->n_dofs; ++j) {
            this->f((n_dofs*i + j)%m) = this->f((n_dofs*i + j)%m) + bodyForce(n_dofs*i + j) + naturalConditions(j);
        }

        for (int j = n_dofs; j < 2*this->n_dofs; ++j) {
            this->f((n_dofs*i  + j)%m) = this->f((n_dofs*i  + j)%m) + naturalConditions(j);
        }
    }
}

template class Element<Triangle>;
template class Element<Polygon>;