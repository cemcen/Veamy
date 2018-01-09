#ifndef VEAMY_FEAMYSTRAINCALCULATOR_H
#define VEAMY_FEAMYSTRAINCALCULATOR_H

#include <veamy/postprocess/calculators/StrainCalculator.h>
#include <delynoi/models/polygon/Triangle.h>
#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <feamy/models/FeamyElement.h>

template <typename T>
class FeamyStrainCalculator : public StrainCalculator<T> {
private:
    std::vector<Point> points;
    std::vector<FeamyElement*> elements;
public:
    FeamyStrainCalculator(std::vector<Point> &points, std::vector<FeamyElement *> elements, Eigen::VectorXd u, DOFS &d);
    Eigen::VectorXd getStrain(double x, double y, T container, int containerIndex);
};

#endif