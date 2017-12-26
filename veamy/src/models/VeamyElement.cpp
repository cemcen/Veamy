#include <veamy/models/elements/VeamyElement.h>
#include <veamy/physics/traction/VeamyTractionVector.h>
#include <veamy/config/VeamyConfig.h>

VeamyElement::VeamyElement(Conditions &conditions, Polygon &p, UniqueList<Point> &points, DOFS &out) {
    initializeElement(conditions, p, points, out);
}

void VeamyElement::computeK(DOFS d, UniqueList<Point> points, Conditions &conditions) {
    std::vector<int> polygonPoints = p.getPoints();
    int n = (int) polygonPoints.size();
    Point average = p.getAverage(points.getList());

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

        Point middleP = prev.middlePoint(points.getList());
        Point middleN = next.middlePoint(points.getList());

        double p = delynoi_utilities::crossProduct(middleP, Point(prevNormal.first, prevNormal.second));
        double ne = delynoi_utilities::crossProduct(middleN, Point(nextNormal.first, nextNormal.second));

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

    Eigen::MatrixXd D = conditions.material->getMaterialMatrix();

    VeamyConfig* config = VeamyConfig::instance();
    double c = (Hc.transpose()*Hc).trace();
    double alphaS = area*conditions.material->trace()/c;

    Eigen::MatrixXd Se;
    Se = config->getGamma()*alphaS*I;

    this->K = area*Wc*D*Wc.transpose() + (I - Pp).transpose()*Se*(I - Pp);
}

void VeamyElement::computeF(DOFS d, UniqueList<Point> points, Conditions &conditions) {
    BodyForceVector* bodyForceVector = new VeamyBodyForceVector(this->p, points);
    TractionVector* tractionVector = new VeamyTractionVector(this->p, points, conditions.constraints.getNaturalConstraints());

    Element::computeF(d, points, conditions, bodyForceVector, tractionVector);

    delete bodyForceVector;
    delete tractionVector;
}













