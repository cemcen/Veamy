#ifndef DELYNOI_RANDOMDOUBLE_H
#define DELYNOI_RANDOMDOUBLE_H

#include <random>
#include "delynoi/models/generator/Functor.h"

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