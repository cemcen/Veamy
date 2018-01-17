#ifndef VEAMY_ELASTICITY_CONSTRAINTS_H
#define VEAMY_ELASTICITY_CONSTRAINTS_H

#include <vector>
#include <map>

/*
 * Namespace that contains the possible direction of the constraints in a linear elasticity problem
 */
namespace elasticity_constraints{
    /*
     * Name of the different directions: Horizontal (x), Vertical (y) and Total (x and y)
     */
    enum Direction{Horizontal, Vertical, Total};

    /*
     * Map that relates each direction with the index of the dofs (per point) that it affects
     */
    static std::map<elasticity_constraints::Direction, std::vector<int>> constraints = {
            {elasticity_constraints::Direction::Horizontal, {0}},
            {elasticity_constraints::Direction::Vertical, {1}},
            {elasticity_constraints::Direction::Total, {0,1}}
    };
}
#endif