#ifndef DELYNOI_ANGLE_H
#define DELYNOI_ANGLE_H

#include <cmath>
#include <delynoi/config/DelynoiConfig.h>

struct Angle{
    double angle;

    Angle(double a){
        a = a - 360.0*int(a/360);
        if(a>=0 && a<180) {
            angle = a;
        }else{
            angle = a - 180;
        }
    }

    bool operator<(const Angle& other) const{
        DelynoiConfig* config = DelynoiConfig::instance();

        if(std::abs(angle-other.angle)<config->getTolerance()){
            return false;
        }

        return angle<other.angle;
    };



};

#endif 
