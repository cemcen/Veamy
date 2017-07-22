#define _USE_MATH_DEFINES

#include <vector>
#include <math.h>
#include <mesher/models/basic/Point.h>
#include <utilities/Pair.h>

namespace xpoly_utilities {
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
        return xpoly_utilities::crossProduct((q-p),(r-p));
    }
}

