#ifndef DELYNOI_ANGLE_H
#define DELYNOI_ANGLE_H

#include <cmath>
#include <delynoi/config/DelynoiConfig.h>

/*
 * Structure modeling a cartesian angle for segments comparison. Its value is bounded between 0 and 180.
 */
struct Angle{
    /*
     * Value of the angle
     */
    double angle;

    /*
     * Constructor. Takes an angle value and obtains the equivalent between 0 and 180.
     */
    Angle(double a){
        a = a - 360.0*int(a/360);
        if(a>=0 && a<180) {
            angle = a;
        }else{
            angle = a - 180;
        }
    }

    /*
     * Compares the value of two angles.
     * @param angle to compare against
     * @return whether this angle is lesser than the given one
     */
    bool operator<(const Angle& other) const{
        DelynoiConfig* config = DelynoiConfig::instance();

        if(std::abs(angle-other.angle)<config->getTolerance()){
            return false;
        }

        return angle<other.angle;
    };
};

#endif 
