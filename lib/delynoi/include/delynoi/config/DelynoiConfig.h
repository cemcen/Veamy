#ifndef DELYNOI_CONFIG_H
#define DELYNOI_CONFIG_H

#include <utilities/Precision.h>

class DelynoiConfig {
private:
    int circle_discretization_grade;
    double double_comparison_tolerance;
    int scale_for_clipper;
    int precision;

    static DelynoiConfig* s_instance;

    DelynoiConfig();
    DelynoiConfig(const DelynoiConfig& other) = delete;
    DelynoiConfig& operator=(const DelynoiConfig& copy) = delete;
public:
    void setDiscretizationGrade(int d);
    void setTolerance(double t);
    void setScale(int s);
    void setPrecision(Precision::precision p);
    void setPrecision(int p);

    int getDiscretizationGrade();
    double getTolerance();
    int getScale();
    int getPrecision();

    static DelynoiConfig* instance();
};


#endif 
