#ifndef VEAMY_FEAMYDISPLACEMENTCALCULATOR_H
#define VEAMY_FEAMYDISPLACEMENTCALCULATOR_H

#include <utilities/Pair.h>
#include <veamy/postprocess/calculators/DisplacementCalculator.h>
#include <feamy/models/FeamyElement.h>


template <typename T>
class FeamyDisplacementCalculator : public DisplacementCalculator<T>{
private:
    std::vector<FeamyElement*> elements;
    int polygonIndex;
public:
    FeamyDisplacementCalculator(DOFS d, Eigen::VectorXd u,  std::vector<FeamyElement*> elements);
    Pair<double> getDisplacement(double x, double y, int index, T container);
    void setPolygonIndex(int polyIndex);
};

#endif