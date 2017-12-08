#ifndef DELYNOI_CONFIG_H
#define DELYNOI_CONFIG_H

#include <utilities/Precision.h>
/* This class contains all global configuration parameters of the Delynoi
 * library, which default values can be changed by the user*/
class DelynoiConfig {
private:
    /*
     * Number of points used to discretize a circle
     */
    int circle_discretization_grade;

    /*
     * Precision value used to compare doubles
     */
    double double_comparison_tolerance;

    /*
     * Parameter used to scale double numbers to integers to be used in Clipper
     */
    int scale_for_clipper;

    /*
     * Number of decimals used for output files
     */
    int precision;

    static DelynoiConfig* s_instance;

    /*
     * Constructor. Sets the default parameter value.
     */
    DelynoiConfig();

    /*
     * Deletes the copy constructor following the singleton pattern
     */
    DelynoiConfig(const DelynoiConfig& other) = delete;
    /*
    * Deletes the assignment operator following the singleton pattern
    */
    DelynoiConfig& operator=(const DelynoiConfig& copy) = delete;
public:
    /*
     * Sets the value of the circle discretization grade
     * @param d new value
     */
    void setDiscretizationGrade(int d);

    /*
     * Sets the value of the tolerance for doubles comparison
     * @param t new value
     */
    void setTolerance(double t);

    /*
     * Sets the value of the scale for Clipper
     * @param t new value
     */
    void setScale(int s);

    /*
     * Sets the value of the output precision using a predefined Precision value (small, mid or large)
     * @param s new value
     */
    void setPrecision(Precision::precision p);

    /*
     * Sets the value of the circle discretization grade
     * @param p new value
     */
    void setPrecision(int p);

    /*
     * @return value of the circle discretization grade
     */
    int getDiscretizationGrade();

    /*
     * @return the double comparison tolerance value
     */
    double getTolerance();

    /*
     * @return the value of the scale used for Clipper
     */
    int getScale();

    /*
     * @return the number of decimals of the numbers in the output files
     */
    int getPrecision();

    /*
     * @return the DelynoiConfig instance
     */
    static DelynoiConfig* instance();
};


#endif 
