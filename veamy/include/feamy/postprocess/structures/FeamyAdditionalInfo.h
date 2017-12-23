#ifndef VEAMY_FEAMYADDITIONALINFO_H
#define VEAMY_FEAMYADDITIONALINFO_H

#include <feamy/models/FeamyElement.h>
#include <delynoi/models/basic/Point.h>
#include <vector>
#include <veamy/lib/Eigen/Dense>

/*
 * Structure that constains element information important in FEM
 */
struct FeamyAdditionalInfo{
    /*
     * List of elements of the system
     */
    std::vector<FeamyElement*> elements;

    /*
     * Mesh points
     */
    std::vector<Point> points;

    /*
     * Material (stress/strain) matrix
     */
    Eigen::MatrixXd C;

    /*
     * Constructor
     */
    FeamyAdditionalInfo(std::vector<FeamyElement*> e, std::vector<Point> p, Eigen::MatrixXd CMatrix){
        elements = e;
        points = p;
        C = CMatrix;
    }
};

#endif