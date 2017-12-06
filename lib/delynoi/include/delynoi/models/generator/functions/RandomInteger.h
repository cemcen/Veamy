#ifndef DELYNOI_RANDOMINTEGER_H
#define DELYNOI_RANDOMINTEGER_H

#include <random>
#include "delynoi/models/generator/Functor.h"

class Random_Integer : public Functor {
private:
    double min;
    double max;
    static std::default_random_engine rd;
    static std::mt19937 rng;
    std::uniform_int_distribution<int> uni;
public:
    Random_Integer(double min, double max);

    double apply(double x);
};


#endif