#include <delynoi/utilities/delynoi_utilities.h>
#include <delynoi/models/generator/Functor.h>
#include <ctime>
#include <utilities/UniqueList.h>
#include <float.h>

class Constant : public Functor {
public:
    Constant() {}
    inline double apply(double x){ return x;}
};

class Uniform : public Functor {
private:
    double delta;
public:
    Uniform(double delta){ this->delta = delta;}
    inline double apply(double x){ return x*delta;}
};

class Sine : public Functor {
private:
    double amplitude;
    double frecuency;
    double phase;
public:
    Sine(double a, double f, double p){
        this->amplitude = a;
        this->frecuency = f;
        this->phase = p;
    }

    inline double apply(double x){
        return amplitude*std::sin(utilities::radian(frecuency*x*180) + utilities::radian(phase));
    };
};

class Cosine : public Functor {
private:
    double amplitude;
    double frecuency;
    double phase;
public:
    Cosine(double a, double f, double p){
        this->amplitude = a;
        this->frecuency = f;
        this->phase = p;
    }

    inline double apply(double x){
        return amplitude*std::cos(utilities::radian(frecuency*x*180) + utilities::radian(phase));;
    };
};

class DisplaceDelta: public Functor{
private:
    double delta;
    bool alternating = false;
public:
    DisplaceDelta(double delta){
        this->delta = delta;
    }

    inline double apply(double x) {
        alternating = !alternating;

        if (alternating) {
            return x + delta / 2;
        } else {
            return x;
        }
    }
};

class ConstantAlternating: public Functor{
private:
    UniqueList<double> visitedPlaces;
    double delta;
    bool alternating = false;
public:
    ConstantAlternating(){}
    inline double apply(double x){
        if(visitedPlaces.size()==1){
            delta = std::abs(visitedPlaces[0] - x);
        }

        int index = visitedPlaces.push_back(x);

        if(index<visitedPlaces.size()-1){
            alternating = !alternating;
            visitedPlaces.clear();
        }

        if(alternating){
            return x + delta/2;
        }else{
            return x;
        }
    }

};

