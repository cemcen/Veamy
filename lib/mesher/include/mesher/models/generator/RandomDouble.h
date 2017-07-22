#ifndef MESHER_RANDOMDOUBLE_H
#define MESHER_RANDOMDOUBLE_H

#include <random>
#include "Functor.h"

class Random_Double : public Functor {
public:
    double min;
    double max;
    static std::default_random_engine rd;
    static std::mt19937 rng;
    std::uniform_real_distribution<double> uni;

    Random_Double(double min, double max);
    double apply(double x);
};


#endif