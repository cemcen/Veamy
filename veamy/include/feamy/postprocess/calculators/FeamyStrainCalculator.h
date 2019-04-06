#ifndef VEAMY_FEAMYSTRAINCALCULATOR_H
#define VEAMY_FEAMYSTRAINCALCULATOR_H

#include <veamy/postprocess/calculators/StrainCalculator.h>
#include <delynoi/models/polygon/Triangle.h>
#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <feamy/models/FeamyElement.h>

/*
 * Class that models the computation of the approximated strain for norm computation for FEM (using the nodal
 * values and shape functions)
 */
template <typename T>
class FeamyStrainCalculator : public StrainCalculator<T> {
private:
    /*
     * List of elements of the system
     */
    std::vector<FeamyElement*> elements;
public:
    /*
     * Constructor
     */
    FeamyStrainCalculator(std::vector<Point> &points, std::vector<FeamyElement *>& elements, Eigen::VectorXd& u, DOFS &d);

    /* Computes the approximate strain for a given point
     * @param x y coordinates of the point
     * @param container element that contains the point
     * @param containerIndex index of the container element
     * @return approximated strain
     */
    Eigen::VectorXd getStrain(double x, double y, T container, int containerIndex);
};

#endif