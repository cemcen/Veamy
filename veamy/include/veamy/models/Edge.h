#ifndef VEAMY_EDGE_H
#define VEAMY_EDGE_H

#include <mesher/models/basic/Point.h>
#include <utilities/Pair.h>
#include <vector>
#include <veamy/models/dof/DOF.h>

class Edge {
private:
    int p1;
    int p2;
public:
    Edge(int p1, int p2);

    Pair<double> getNormal(std::vector<Point> points);
    double getLength(std::vector<Point> points);
};


#endif