#ifndef THESIS_MATERIALS_H
#define THESIS_MATERIALS_H

#include <map>

struct material_info{
    double E;
    double v;

    material_info(double En, double vn){
        E = En;
        v = vn;
    }

    material_info(){}
};

namespace Materials{
    enum class material {Steel, Aluminium, Cooper, Unitary};

    static std::map<Materials::material, material_info> properties = {{Materials::material::Steel, material_info(210000000000,0.3)},
                                                                      {Materials::material::Aluminium, material_info(70000000000,0.35)},
                                                                      {Materials::material::Cooper, material_info(1150000000000,0.36)},
                                                                      {Materials::material::Unitary, material_info(1,0)}};

}



#endif
