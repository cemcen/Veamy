#ifndef VEAMY_NORMRESULT_H
#define VEAMY_NORMRESULT_H

/*
 * Structure that contains the results of a norm calculation
 */
struct NormResult{
    /*
     * Value of the norm
     */
    double NormValue;

    /*
     * Maximum edge of the mesh (x-axis for the norm graph)
     */
    double MaxEdge;

    /*
     * Constructor
     */
    NormResult(double norm, double edge){
        NormValue = norm;
        MaxEdge = edge;
    }
};

#endif