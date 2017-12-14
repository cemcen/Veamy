#ifndef VEAMY_DISPCOMPUTABLE_H
#define VEAMY_DISPCOMPUTABLE_H

#include <veamy/postprocess/analytic/DisplacementValue.h>
#include <veamy/postprocess/computables/Computable.h>
#include <delynoi/models/polygon/Polygon.h>
#include <delynoi/models/polygon/Triangle.h>

/*
 * Class that computes the term u dot u of the L2 norm
 */
template <typename T>
class DisplacementComputable : public Computable<T> {
private:
    /*
     * Analytical displacement solution
     */
    DisplacementValue* value;
public:
    /*
     * Constructor
     */
    DisplacementComputable(DisplacementValue* value);

    /* Calculates the value of the displacement dot product on a point
     * @param x y coordinates of the point
     * @param index index of the point (if part of the mesh)
     * @param container geometric container of the point
     * @return value of the computable
     */
    double apply(double x, double y, int index, T container);
};

#endif