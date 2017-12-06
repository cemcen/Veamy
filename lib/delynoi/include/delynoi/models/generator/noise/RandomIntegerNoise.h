#ifndef DELYNOI_RANDOMINTEGERNOISE_H
#define DELYNOI_RANDOMINTEGERNOISE_H

#include <random>
#include <delynoi/models/generator/Functor.h>

class RandomIntegerNoise: public Functor {
private:
    double min;
    double max;
    Functor* f;

    static std::default_random_engine rd;
    static std::mt19937 rng;
    std::uniform_int_distribution<int> uni;
public:
    RandomIntegerNoise(Functor*f, double min, double max);
    double apply(double x);
};

#endif


