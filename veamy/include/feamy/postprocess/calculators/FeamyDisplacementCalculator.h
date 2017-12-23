#ifndef VEAMY_FEAMYDISPLACEMENTCALCULATOR_H
#define VEAMY_FEAMYDISPLACEMENTCALCULATOR_H

#include <utilities/Pair.h>
#include <veamy/postprocess/calculators/DisplacementCalculator.h>
#include <feamy/models/FeamyElement.h>

/*
 * Class that models the computation of the approximated displacement for norm computation for FEM (using the nodal
 * values and shape functions)
 */
template <typename T>
class FeamyDisplacementCalculator : public DisplacementCalculator<T>{
private:
    /*
     * List of elements of the system
     */
    std::vector<FeamyElement*> elements;

    /*
     * Index of the polygon inside which the displacement will be calculated
     */
    int polygonIndex;
public:
    /*
     * Constructor
     */
    FeamyDisplacementCalculator(DOFS d, Eigen::VectorXd u,  std::vector<FeamyElement*> elements);

    /* Computes the approximate displacement for a given point
     * @param x y coordinates of the point
     * @param index index of the point (if part of the mesh)
     * @param container element that contains the point
     * @return approximated displacement
     */
    Pair<double> getDisplacement(double x, double y, int index, T container);

    /* Sets the polygon inside which the displacement will be calculated
     * @param polyIndex index of the polygon
     */
    void setPolygonIndex(int polyIndex);
};

#endif