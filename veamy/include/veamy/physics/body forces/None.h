#ifndef THESIS_NONE_H
#define THESIS_NONE_H

class None : public BodyForce{
private:
    double apply(double x, double y){
        return 0;
    }
};

#endif