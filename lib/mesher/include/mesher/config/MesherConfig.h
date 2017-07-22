#ifndef MESHER_MESHERCONFIG_H
#define MESHER_MESHERCONFIG_H

class MesherConfig {
private:
    int circle_discretization_grade;
    double double_comparison_tolerance;
    int scale_for_clipper;

    static MesherConfig* s_instance;

    MesherConfig();
    MesherConfig(const MesherConfig& other) = delete;
    MesherConfig& operator=(const MesherConfig& copy) = delete;
public:
    void setDiscretizationGrade(int d);
    void setTolerance(double t);
    void setScale(int s);

    int getDiscretizationGrade();
    double getTolerance();
    int getScale();

    static MesherConfig* instance();
};


#endif 
