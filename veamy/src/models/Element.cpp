#include <veamy/models/Element.h>
#include <veamy/physics/bodyforces/BodyForceVector.h>

template <typename T>
void Element<T>::initializeElement(Conditions &conditions, T &p, UniqueList<Point> &points, DOFS &out) {
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

template <typename T>
void Element<T>::computeF(DOFS d, UniqueList<Point> points, Conditions &conditions, BodyForceVector *bodyForceVector,
                       TractionVector *tractionVector) {
    int n = this->p.numberOfSides();
    int m = this->dofs.size();
    std::vector<IndexSegment> segments;
    this->p.getSegments(segments);

    this->f = Eigen::VectorXd::Zero(m);
    Eigen::VectorXd bodyForce = bodyForceVector->computeForceVector(conditions.f);

    NaturalConstraints natural = conditions.constraints.getNaturalConstraints();

    for (int i = 0; i < n; ++i) {
        Eigen::VectorXd naturalConditions = tractionVector->computeTractionVector(segments[i]);

        this->f(2*i) = this->f(2*i) + bodyForce(2*i) + naturalConditions(0);
        this->f((2*i + 1)%m) = this->f((2*i + 1)%m) + bodyForce(2*i+1) + naturalConditions(1);
        this->f((2*(i+1))%m) =  this->f((2*(i+1))%m) + naturalConditions(2);
        this->f((2*(i+1) + 1)%m) =  this->f((2*(i+1) + 1)%m) + naturalConditions(3);
    }
}

template class Element<Triangle>;
template class Element<Polygon>;