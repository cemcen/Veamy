#ifndef VEAMY_NORMRESULT_H
#define VEAMY_NORMRESULT_H

struct NormResult{
    double NormValue;
    double MaxEdge;

    NormResult(double norm, double edge){
        NormValue = norm;
        MaxEdge = edge;
    }
};

#endif