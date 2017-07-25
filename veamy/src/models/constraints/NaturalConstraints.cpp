#include <veamy/models/constraints/NaturalConstraints.h>

NaturalConstraints::NaturalConstraints() {}

double NaturalConstraints::boundaryVector(std::vector<Point> points, Polygon p, int point, int DOF_index) {
    if(isConstrained(DOF_index)){
        double integral = 0;

        std::vector<int> polygonPoints = p.getPoints();
        int n = (int) polygonPoints.size();

        IndexSegment prev (polygonPoints[(n + point -1)%n], polygonPoints[point]);
        IndexSegment next (polygonPoints[point], polygonPoints[(n + point + 1)%n]);

        isConstrainedInfo prevConst = isConstrained(points, prev);
        isConstrainedInfo nextConst = isConstrained(points, next);

        if(prevConst.isConstrained){
            Constraint c = segment_map[prevConst.container];

            

            integral += (0.5*c.getValue(points[prev.getFirst()]) + 0.5*c.getValue(points[prev.getSecond()]))*prev.length(points);
        }

        if(nextConst.isConstrained){
            Constraint c = segment_map[nextConst.container];

            integral += (0.5*c.getValue(points[next.getFirst()]) + 0.5*c.getValue(points[next.getSecond()]))*next.length(points);
        }

        return integral;
    }

    return 0;
}

