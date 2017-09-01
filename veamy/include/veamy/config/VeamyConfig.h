#ifndef VEAMY_VEAMYCONFIG_H
#define VEAMY_VEAMYCONFIG_H

class VeamyConfig{
private:
    double double_comparison_tolerance;
    double gamma;
    int precision;

    static VeamyConfig* s_instance;
    VeamyConfig();
public:
    enum Precision{Small=4, Mid=8, Large=14};

    void setTolerance(double t);
    void setPrecision(VeamyConfig::Precision p);
    void setPrecision(int p);
    void setGamma(double g);

    double getTolerance();
    double getGamma();
    int getPrecision();

    static VeamyConfig* instance();
};

#endif 
