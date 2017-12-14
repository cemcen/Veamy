#ifndef THESIS_MATERIALS_H
#define THESIS_MATERIALS_H

#include <map>

/*
 * Structure that contains the properties of a material
 */
struct material_info{
    /*
     * Young module and Poisson ratio
     */
    double E;
    double v;

    /*
     * Constructor
     */
    material_info(double En, double vn){
        E = En;
        v = vn;
    }

    /*
     * Default constructor
     */
    material_info(){}
};

/*
 * Namespace that contains a list of predefined material properties for Material instance creation
 */
namespace Materials{
    /*
     * List of the names of the materials
     */
    enum class material {Steel, Aluminium, Cooper, Unitary};

    /*
     * Map relating material name with their properties
     */
    static std::map<Materials::material, material_info> properties = {{Materials::material::Steel, material_info(210000000000,0.3)},
                                                                      {Materials::material::Aluminium, material_info(70000000000,0.35)},
                                                                      {Materials::material::Cooper, material_info(1150000000000,0.36)},
                                                                      {Materials::material::Unitary, material_info(1,0)}};

}



#endif
