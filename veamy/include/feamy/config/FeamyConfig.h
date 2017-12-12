#ifndef VEAMY_FEAMYCONFIG_H
#define VEAMY_FEAMYCONFIG_H

/*
 * Class that encapsulates all configuration parameters of the Feamy module
 */
class FeamyConfig {
private:
    /*
     * Number of gauss points used for the integration of the stiffness matrix and load vector
     */
    int gaussPoints;

    /*
     * Unique instance of FeamyConfig (following the Singleton pattern)
     */
    static FeamyConfig* s_instance;

    /*
     * Constructor
     */
    FeamyConfig();
public:
    /* Sets a new value for the number of gauss points
     * @param gauss value to set
     */
    void setNumberOfGaussPoints(int gauss);

    /*
     * @return number of gauss points
     */
    int getNumberOfGaussPoints();

    /*
     * @return instance of FeamyConfig
     */
    static  FeamyConfig* instance();
};

#endif