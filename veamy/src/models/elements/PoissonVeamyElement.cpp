#include <veamy/models/elements/PoissonVeamyElement.h>

PoissonVeamyElement::PoissonVeamyElement(PoissonConditions *conditions, Polygon &p, UniqueList<Point> &points, DOFS &out,
                                         int n_dofs) : VeamyElement(conditions, p, points, out, n_dofs) {
    this->conditions = conditions;
}

void PoissonVeamyElement::computeK(DOFS &d, UniqueList<Point> &points) {
    std::vector<int> polygonPoints = p.getPoints();
    int n = (int) polygonPoints.size();
    Point average = p.getAverage(points.getList());

    double area = p.getArea();

    Eigen::MatrixXd H, W;
    H = Eigen::MatrixXd::Zero(n, 3);
    W = Eigen::MatrixXd::Zero(n, 3);

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

        H(vertex_id, 0) = 1;
        H(vertex_id, 1) = xDiff;
        H(vertex_id, 2) = yDiff;
        W(vertex_id, 0) = 1.0/n;
        W(vertex_id, 1) = 2*Qi_x;
        W(vertex_id, 2) = 2*Qi_y;
    }

    Eigen::MatrixXd P, I, Ic;

    I = Eigen::MatrixXd::Identity(n, n);
    Ic = Eigen::MatrixXd::Identity(3,3);
    Ic(0,0) = 0;

    P = H*(W.transpose());

    this->K = area*W*Ic*W.transpose() + (I - P).transpose()*I*(I - P);
}
