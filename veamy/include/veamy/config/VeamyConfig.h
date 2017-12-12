#ifndef VEAMY_VEAMYCONFIG_H
#define VEAMY_VEAMYCONFIG_H

#include <utilities/Precision.h>

/*
 * Class that encapsulates all cnfiguration parameters of the Veamy library
 */
class VeamyConfig{
private:
    /*
     * Tolerance for comparison of double precision numbers
     */
    double double_comparison_tolerance;

    /*
     * Value of gamma in the formula for the computation of the elemental stiffness matrix for linear elasticity in VEM
     */
    double gamma;

    /*
     * Number of decimals used when printing numbers in output text files
     */
    int precision;

    /*
     * Unique instance of VeamyConfig (following the Singleton pattern)
     */
    static VeamyConfig* s_instance;

    /*
     * Constructor
     */
    VeamyConfig();
public:
    /* Sets the value of the tolerance for double precision number comparison
     * @param t value to set
     */
    void setTolerance(double t);

    /* Sets the number of decimals to print in output files using a predefined precision value
     * @param p value to set
     */
    void setPrecision(Precision::precision p);

    /* Sets the number of decimals to print in output files
     * @param p value to set
     */
    void setPrecision(int p);

    /* Sets the value of gamma for stiffness matrix calculation
     * @param g value to set
     */
    void setGamma(double g);

    /*
     * @return tolerance for double precision numbers comparison
     */
    double getTolerance();

    /*
     * @return get gamma value for VEM stiffness matrix calculation
     */
    double getGamma();

    /*
     * @return number of decimals that will be used when printing too output files
     */
    int getPrecision();

    /*
     * @return instance of VeamyConfig
     */
    static VeamyConfig* instance();
};

#endif 
