#ifndef MESHER_MESHERCONFIG_H
#define MESHER_MESHERCONFIG_H

#include <utilities/Precision.h>

class MesherConfig {
private:
    int circle_discretization_grade;
    double double_comparison_tolerance;
    int scale_for_clipper;
    int precision;

    static MesherConfig* s_instance;

    MesherConfig();
    MesherConfig(const MesherConfig& other) = delete;
    MesherConfig& operator=(const MesherConfig& copy) = delete;
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

    static MesherConfig* instance();
};


#endif 
