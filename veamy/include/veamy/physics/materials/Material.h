#ifndef THESIS_MATERIAL_H
#define THESIS_MATERIAL_H

#include <veamy/lib/Eigen/Dense>
#include <veamy/physics/materials/Materials.h>

/*
 * Class that models the material of the domain, including its mechanical properties
 */
class Material{
protected:
    /*
     * Young module
     */
    double material_E;

    /*
     * Poisson ratio
     */
    double material_v;
    /*
     * Multiplicative factor that differs between the implementation of VEM and FEM. Assign as needed.
     */
    double factor;
public:
    /*
     * Constructor. Creates a material from the list of predefined materials included in Veamy
     */
    Material(Materials::material m);

    /*
     * Constructor. Creates a material given its properties
     */
    Material(double young, double poisson);

    /*
     * Default constructor
     */
    Material();

    /*
     * @return the material matrix (also called stress/strain tensor)
     */
    virtual Eigen::MatrixXd getMaterialMatrix()=0;

    /*
     * @return trace of the material matrix
     */
    virtual double trace()=0;

    /*
     * @return
     */
    double k();

    /*
     * @return Poisson ratio
     */
    double v();

    /*
     * @return Young module
     */
    double E();

    /* Equality operator
     * @param other Material instance to compare against
     * @return if the two instances are equal
     */
    bool operator==(const Material& other) const;

    /* Sets the multiplicative factor
     * @param f factor to set
     */
    void setMultiplicativeFactor(double f);
};

#endif
