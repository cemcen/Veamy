#include <veamy/Calculator2D.h>
#include <utilities/Pair.h>
#include <veamy/physics/materials/Material.h>
#include <utilities/UniqueList.h>
#include <veamy/config/VeamyConfig.h>
#include <veamy/models/Element.h>

template <typename T>
Calculator2D<T>::Calculator2D(Conditions *problem, int n_dofs) {
    this->conditions = problem;
    this->DOFs.setNumberOfDOFS(n_dofs);
}

template <typename T>
std::vector<int> Calculator2D<T>::pointToDOFS(int point_index) {
    return this->DOFs.pointToDOFS(point_index);
}

template <typename T>
UniqueList <Point> Calculator2D<T>::getPoints() const {
    return this->points;
}

template <typename T>
UniqueList <Point> Calculator2D<T>::getPoints() {
    return this->points;
}

template <typename T>
void Calculator2D<T>::writeDisplacements(std::string fileName, Eigen::VectorXd u) {
    int dofs = this->DOFs.getNumberOfDOFS();
    
    std::string path = utilities::getPath();
    path = path  + fileName;

    std::ofstream file;
    file.open(path, std::ios::out);

    std::vector<std::string> results(this->points.size());

    for (int k = 0; k < u.rows(); k = k + dofs) {
        int point_index = DOFs.get(k).pointIndex();

        results[point_index] = utilities::toString<int>(point_index);

        for (int i = 0; i < dofs; ++i) {
            double def = u[k + dofs];

            results[point_index] += " " +
                    utilities::toStringWithPrecision(def, VeamyConfig::instance()->getPrecision());
        }
    }

    for (std::string s: results){
        file << s << std::endl;
    }

    file.close();
}

template <typename T>
void Calculator2D<T>::assemble(Eigen::MatrixXd &Kglobal, Eigen::VectorXd &fGlobal) {
    for (Element<T>* e: elements){
        e->computeK(DOFs, this->points);
        e->computeF(DOFs, this->points, conditions);
        e->assemble(DOFs, Kglobal, fGlobal);
    }
}

template <typename T>
Eigen::VectorXd Calculator2D<T>::simulate(Mesh<T> &mesh) {
    Eigen::MatrixXd K;
    Eigen::VectorXd f;
    int n = this->DOFs.size();

    K = Eigen::MatrixXd::Zero(n,n);
    f = Eigen::VectorXd::Zero(n);

    assemble(K, f);

    //Apply constrained_points
    EssentialConstraints essential = this->conditions->constraints.getEssentialConstraints();
    std::vector<int> c = essential.getConstrainedDOF();

    Eigen::VectorXd boundary_values = essential.getBoundaryValues(this->points.getList(), this->DOFs.getDOFS());

    for (int j = 0; j < c.size(); ++j) {
        for (int i = 0; i < K.rows(); ++i) {
            f(i) = f(i) - (K(i,c[j])*boundary_values(j));

            K(c[j],i) = 0;
            K(i,c[j]) = 0;
        }

        K(c[j], c[j]) = 1;
        f(c[j]) = boundary_values(j);
    }

    /*Solve the system: There are various solvers available. The commented one is the slowest but most accurate. We
    leave ldlt as it has the better trade off between speed and accuracy.*/
    //Eigen::VectorXd x = K.fullPivHouseholderQr().solve(f);
    Eigen::VectorXd x = K.ldlt().solve(f);

    return x;
}


template class Calculator2D<Polygon>;
template class Calculator2D<Triangle>;