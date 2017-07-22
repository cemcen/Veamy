#ifndef VEAMY_VEAMYCONFIG_H
#define VEAMY_VEAMYCONFIG_H

class VeamyConfig{
private:
    double double_comparison_tolerance;
    double gamma;

    static VeamyConfig* s_instance;
    VeamyConfig();
public:
    void setTolerance(double t);
    void setGamma(double g);

    double getTolerance();
    double getGamma();

    static VeamyConfig* instance();
};

#endif 
