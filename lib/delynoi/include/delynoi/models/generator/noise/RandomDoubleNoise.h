#ifndef DELYNOI_RANDOMDOUBLENOISE_H
#define DELYNOI_RANDOMDOUBLENOISE_H

#include <random>
#include <climits>
#include <delynoi/models/generator/Functor.h>

/*
 * Generates random double noise and applies it to a given Function class.
 */
class RandomDoubleNoise: public Functor {
private:
    /*
   * Parameters for noise generation. Maximum and minimum possible noise value. Note that there is no constraint in
   * this values, so it is possible to generate noise that completely distorts the Function class.
   */
    double min;
    double max;

    /*
     * Function class over which the noise is applied.
     */
    Functor* f;

    /*
     * Parameters for random double number generation.
     */
    static std::default_random_engine rd;
    static std::mt19937 rng;
    std::uniform_real_distribution<double> uni;
    std::uniform_int_distribution<int> uni_int;
public:
    /*
    * Constructor.
    */
    RandomDoubleNoise(Functor*f, double min, double max);

    /*
    * Applies the inner Function class with the given value, and then adds to the result the noise.
    * @param x argument of the function
    * @return function result
    */
    double apply(double x);

};

#endif