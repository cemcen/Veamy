#ifndef DELYNOI_RANDOMDOUBLENOISE_H
#define DELYNOI_RANDOMDOUBLENOISE_H

#include <random>
#include <climits>
#include <delynoi/models/generator/Functor.h>

class RandomDoubleNoise: public Functor {
private:
    double min;
    double max;
    Functor* f;

    static std::default_random_engine rd;
    static std::mt19937 rng;
    std::uniform_real_distribution<double> uni;
    std::uniform_int_distribution<int> uni_int;
public:
    RandomDoubleNoise(Functor*f, double min, double max);
    double apply(double x);

};

#endif