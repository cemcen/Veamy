#ifndef VEAMY_ELASTICITY_CONSTRAINTS_H
#define VEAMY_ELASTICITY_CONSTRAINTS_H

#include <vector>
#include <map>

namespace elasticity_constraints{
    enum Direction{Horizontal, Vertical, Total};

    static std::map<elasticity_constraints::Direction, std::vector<int>> constraints = {
            {elasticity_constraints::Direction::Horizontal, {0}},
            {elasticity_constraints::Direction::Vertical, {1}},
            {elasticity_constraints::Direction::Total, {0,1}}
    };
}
#endif