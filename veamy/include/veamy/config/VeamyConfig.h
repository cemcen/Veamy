#ifndef VEAMY_VEAMYCONFIG_H
#define VEAMY_VEAMYCONFIG_H

#include <utilities/Precision.h>

class VeamyConfig{
private:
    double double_comparison_tolerance;
    double gamma;
    int precision;

    static VeamyConfig* s_instance;
    VeamyConfig();
public:
    void setTolerance(double t);
    void setPrecision(Precision::precision p);
    void setPrecision(int p);
    void setGamma(double g);

    double getTolerance();
    double getGamma();
    int getPrecision();

    static VeamyConfig* instance();
};

#endif 
