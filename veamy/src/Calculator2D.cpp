#include <veamy/Calculator2D.h>
#include <utilities/Pair.h>
#include <veamy/physics/materials/Material.h>
#include <utilities/UniqueList.h>

template <typename T>
Pair<int> Calculator2D<T>::pointToDOFS(int point_index) {
    return this->DOFs.pointToDOFS(point_index);
}

template <typename T>
Material *Calculator2D<T>::getMaterial() {
    return conditions.material;
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
    std::string path = utilities::getPath();
    path = path  + fileName;

    std::ofstream file;
    file.open(path, std::ios::out);

    std::vector<std::string> results(this->points.size());
    VeamyConfig* config = VeamyConfig::instance();

    for (int k = 0; k < u.rows(); k = k + 2) {
        int point_index = DOFs.get(k).pointIndex();
        double def_x = u[k];
        double def_y = u[k+1];

        results[point_index] = utilities::toString<int>(point_index) + " " +
                               utilities::toStringWithPrecision(def_x, VeamyConfig::instance()->getPrecision()) + " " +
                               utilities::toStringWithPrecision(def_y, VeamyConfig::instance()->getPrecision());
    }

    for (std::string s: results){
        file << s << std::endl;
    }

    file.close();
}

template <typename T>
Eigen::VectorXd Calculator2D<T>::simulate(Mesh<T> &mesh) {
    Eigen::MatrixXd K;
    Eigen::VectorXd f;
    int n = this->DOFs.size();

    K = Eigen::MatrixXd::Zero(n,n);
    f = Eigen::VectorXd::Zero(n);

    createAndAssemble(K, f);

    //Apply constrained_points
    EssentialConstraints essential = this->conditions.constraints.getEssentialConstraints();
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

    // Deform mesh
    for (int k = 0; k < x.rows(); k = k + 2) {
        int point_index = DOFs.get(k).pointIndex();
        double def_x = x[k];
        double def_y = x[k+1];

        //mesh.deformPoint(point_index, def_x, def_y);
    }

    //mesh.update();

    return x;
}

template class Calculator2D<Polygon>;
template class Calculator2D<Triangle>;