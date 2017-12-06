#ifndef VEAMY_FEAMYCONFIG_H
#define VEAMY_FEAMYCONFIG_H

class FeamyConfig {
private:
    int gaussPoints;
    static FeamyConfig* s_instance;
    FeamyConfig();
public:
    void setNumberOfGaussPoints(int gauss);

    int getNumberOfGaussPoints();

    static  FeamyConfig* instance();
};

#endif