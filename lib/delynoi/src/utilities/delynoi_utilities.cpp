#define _USE_MATH_DEFINES

#include <vector>
#include <math.h>
#include <delynoi/models/basic/Point.h>
#include <utilities/Pair.h>
#include <delynoi/config/DelynoiConfig.h>

namespace delynoi_utilities {
    void TrivialIndexVector(std::vector<int>& index_vector, int n){
        for(int i=0;i<n; i++){
            index_vector.push_back(i);
        }
    }

    double crossProduct(Point a, Point b){
        return a.getX()*b.getY() - a.getY()*b.getX();
    }

    double squareNorm(Point p){
        return pow(p.getX(),2) + pow(p.getY(),2);
    }

    double norm(Point p){
        return sqrt(squareNorm(p));
    }

    double orientation(Point p, Point q, Point r){
        return delynoi_utilities::crossProduct((q-p),(r-p));
    }

    std::vector<Point> generateArcPoints(Point center, double radius, double initAngle, double endAngle){
        std::vector<Point> arcPoints;

        int steps = DelynoiConfig::instance()->getDiscretizationGrade();
        double delta = (endAngle - initAngle)/steps;

        for(int i=0; i<=steps;i++){
            double angle = initAngle + delta*i;

            double x = center.getX() + radius*std::cos(utilities::radian(angle));
            double y = center.getY() + radius*std::sin(utilities::radian(angle));

            Point point (x, y);
            arcPoints.push_back(point);
        }

        return arcPoints;
    }

    void checkTriangleIntegrity(std::vector<int>& trianglePoints){
        if(trianglePoints.size() != 3 || trianglePoints[0] == trianglePoints[1] || trianglePoints[1] == trianglePoints[2]
                || trianglePoints[2] == trianglePoints[0]){
            throw std::invalid_argument("Invalid triangle detected. Stopping meshing.");
        }


    }
}
