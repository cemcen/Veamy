#include <veamy/models/Element.h>

Element::Element(ProblemConditions &conditions, Polygon &p, UniqueList<Point> &points, DOFS &out) {
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

Polygon Element::getAssociatedPolygon() {
    return this->p;
}

void Element::computeK(DOFS d, UniqueList<Point> points, ProblemConditions &conditions) {
    std::vector<int> polygonPoints = p.getPoints();
    int n = (int) polygonPoints.size();
    Point average = p.getCentroid();

    double area = p.getArea();

    Eigen::MatrixXd Hr;
    Eigen::MatrixXd Wr;
    Eigen::MatrixXd Hc;
    Eigen::MatrixXd Wc;

    Hr = Eigen::MatrixXd::Zero(2*n, 3);
    Wr = Eigen::MatrixXd::Zero(2*n, 3);
    Hc = Eigen::MatrixXd::Zero(2*n, 3);
    Wc = Eigen::MatrixXd::Zero(2*n, 3);

    for(int vertex_id=0; vertex_id<n; vertex_id++){
        Point vertex = points[polygonPoints[vertex_id]];

        Edge prev (polygonPoints[(n+vertex_id-1)%n], polygonPoints[vertex_id]);
        Edge next (polygonPoints[vertex_id], polygonPoints[(n+vertex_id+1)%n]);

        Pair<double> prevNormal = utilities::normalize(prev.getNormal(points.getList()));
        Pair<double> nextNormal = utilities::normalize(next.getNormal(points.getList()));

        double prevLength = prev.getLength(points.getList());
        double nextLength = next.getLength(points.getList());

        double xDiff = vertex.getX() - average.getX();
        double yDiff = vertex.getY() - average.getY();

        double Qi_x = (prevNormal.first*prevLength + nextNormal.first*nextLength)/(4*area);
        double Qi_y = (prevNormal.second*prevLength + nextNormal.second*nextLength)/(4*area);

        Hr(2*vertex_id, 0) = 1;
        Hr(2*vertex_id, 2) = yDiff;
        Hr(2*vertex_id+1, 1) = 1;
        Hr(2*vertex_id+1, 2) = -xDiff;

        Wr(2*vertex_id, 0) = 1.0/n;
        Wr(2*vertex_id, 2) = Qi_y;
        Wr(2*vertex_id+1, 1) = 1.0/n;
        Wr(2*vertex_id+1, 2) = -Qi_x;

        Hc(2*vertex_id, 0) = xDiff;
        Hc(2*vertex_id, 2) = yDiff;
        Hc(2*vertex_id+1, 1) = yDiff;
        Hc(2*vertex_id+1, 2) = xDiff;

        Wc(2*vertex_id, 0) = 2*Qi_x;
        Wc(2*vertex_id, 2) = Qi_y;
        Wc(2*vertex_id+1, 1) = 2*Qi_y;
        Wc(2*vertex_id+1, 2) = Qi_x;

    }

    Eigen::MatrixXd Pr;
    Eigen::MatrixXd Pc;
    Eigen::MatrixXd Pp;
    Eigen::MatrixXd I;

    I = Eigen::MatrixXd::Identity(2*n, 2*n);

    Pr = Hr*(Wr.transpose());
    Pc = Hc*(Wc.transpose());

    Pp = Pc + Pr;

    Eigen::MatrixXd D = conditions.material.getMaterialMatrix();

    VeamyConfig* config = VeamyConfig::instance();
    double c = (Hc.transpose()*Hc).trace();
    double alphaS = area*conditions.material.trace()/c;
    Eigen::MatrixXd Se;
    Se = config->getGamma()*alphaS*I;

    this->K = area*Wc*D*Wc.transpose() + (I - Pp).transpose()*Se*(I - Pp);
}

void Element::computeF(DOFS d, UniqueList<Point> points, ProblemConditions &conditions) {
    this->f = Eigen::VectorXd::Zero(this->dofs.size());
    NaturalConstraints natural = conditions.constraints.getNaturalConstraints();

    Pair<double> bodyForce = conditions.f->computeVector(p, points.getList());

    for (int i = 0; i < this->dofs.size(); ++i) {
        double bodyForceValue = i%2==0? bodyForce.first: bodyForce.second;
        this->f(i) =  bodyForceValue +


                natural.boundaryVector(points.getList(), p, i / 2, this->dofs[i]);
    }
}

void Element::assemble(DOFS out, Eigen::MatrixXd& Kglobal, Eigen::VectorXd& Fglobal) {
    for (int i = 0; i < this->K.rows(); i++) {
        int globalI = out.get(this->dofs[i]).globalIndex();

        for (int j = 0; j < this->K.cols(); j++) {
            int globalJ = out.get(this->dofs[j]).globalIndex();

            Kglobal(globalI, globalJ) = Kglobal(globalI, globalJ) + this->K(i, j);
        }

        Fglobal(globalI) = Fglobal(globalI) + this->f(i);
    }
}












